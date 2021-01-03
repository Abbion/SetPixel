#include "spClippingAlgorithms.h"
#include "spCoreDefined.h"
#include "spVector.h"


//Face culling algorithm--------------------------------
bool sp::faceCulling(const sp::vector3f& a, const sp::vector3f& b, const sp::vector3f& c)
{
    SP_FLOAT shoelace = ((a.x * b.y) + (b.x * c.y) + (c.x * a.y)) - ((a.y * b.x) + (b.y * c.x) + (c.y * a.x));
    if(shoelace < 0)
        return false;
    return true;
}
//-----------------------------------------------------


//Clipps triangles to an array of planes---------------
bool sp::clipTriangleToPlanes(const std::vector<sp::vector3f>& input, int start, int offset, std::vector<sp::vector3f>& output, const std::vector<sp::vector3f>& planes)
{
    //Load trinagle
    int blockSize = 3 * offset;
    for (int i = start; i < start + blockSize; i++)
    {
        output.push_back(input[i]);
    }
    //--------------------------

    SP_FLOAT relative[3];
    int planesCount = planes.size();

    for (int i = 0; i < planesCount; i += 2)
    {  
        int s = output.size() / blockSize;
        for (int j = 0; j < s; j++)
        {
            int outCount = countPointsOut(output, offset, relative, planes[i], planes[i + 1]);
            //Discard triangle
            if (outCount == 3)
            {
                output.erase(output.begin(), output.begin() + blockSize);
            }
            //Leave triangle as it is
            else if(outCount == 0)
            {
                output.insert(output.end(), output.begin(), output.begin() + blockSize);
                output.erase(output.begin(), output.begin() + blockSize);
            }
            
            //All triangles rejected
            else if(output.empty())
            {
                return false;
            }
            
            //run the plane compare algorithm
            else
            {
                if (offset == 1)
                    compareToPlane(output, relative, planes[i], planes[i + 1]);
                else
                    compareToPlaneWithFragments(output, relative, planes[i], planes[i + 1]);
            }
        }
    }
    return true;
}
//-----------------------------------------------------


//Checks which vertex is on the other side of the plane
int sp::countPointsOut(std::vector<sp::vector3f>& vertex, int offset, SP_FLOAT* relative, const sp::vector3f& onPlane, const sp::vector3f& normalPlane)
{
    int countOut = 0;
    for (int i = 0; i < 3; i++)
    {
        sp::vector3f dff = vertex[i * offset] - onPlane;
        relative[i * offset] = sp::getDotProduct(normalPlane, dff);
        if(relative[i * offset] < 0)
            countOut++;
    }

    return countOut;
}
//-----------------------------------------------------


//Compares triangle to the plane and cuts it. Data includes fragment color information
void sp::compareToPlaneWithFragments(std::vector<sp::vector3f>& data, SP_FLOAT* relative, const sp::vector3f& onPlane, const sp::vector3f& normalPlane)
{
    int offset = 2;
    SP_FLOAT d0 = sp::getDotProduct(normalPlane, (data[0] - onPlane));
    SP_FLOAT d1 = sp::getDotProduct(normalPlane, (data[offset] - onPlane));
    SP_FLOAT d2 = sp::getDotProduct(normalPlane, (data[2 * offset] - onPlane));

    int countIn = 0;
    int countOut = 0;
    std::vector<sp::vector3f> pointsIn;
    std::vector<sp::vector3f> pointsOut;
    std::vector<sp::vector3f> fragmentsIn;
    std::vector<sp::vector3f> fragmentsOut;

    SP_FLOAT d[3];
    SP_FLOAT d_out[3];
    SP_FLOAT d_in[3];

    
    for (int i = 0; i < 3; i++)
    {
        int vecPos = i * offset;
        d[i] = sp::getDotProduct(normalPlane, (data[vecPos] - onPlane));
        if (d[i] < 0)
        {
            pointsOut.push_back(data[vecPos]);
            for (int j = 1; j < offset; j++)
                fragmentsOut.push_back(data[vecPos + j]);
            d_out[countOut++] = d[i];
            d[i] = vecPos;
        }
        else
        {
            pointsIn.push_back(data[vecPos]);
            for (int j = 1; j < offset; j++)
                fragmentsIn.push_back(data[vecPos + j]);
            d_in[countIn++] = d[i];
            d[i] = vecPos;
        }
    }
    
    if (countOut == 1)
    {
        SP_FLOAT t1 = d_in[0] / (d_in[0] - d_out[0]); //0 - 2
        SP_FLOAT t2 = d_in[1] / (d_in[1] - d_out[0]); //1 - 2

        sp::vector3f cut1 = pointsIn[0] + (pointsOut[0] - pointsIn[0]) * t1; //0 - 2
        sp::vector3f cut2 = pointsIn[1] + (pointsOut[0] - pointsIn[1]) * t2; //1 - 2

        if (pointsOut[0] != data[offset])   //Switch to wind correct
        {
            data.push_back(pointsIn[0]);
            data.push_back(fragmentsIn[0]);
            data.push_back(cut2);
            data.push_back(fragmentsIn[1] * (1 - t2) + fragmentsOut[0] * t2);
            data.push_back(cut1);
            data.push_back(fragmentsIn[0] * (1 - t1) + fragmentsOut[0] * t1);

            if (t2 != 0.0)  //Floating point precission check
            {
                data.push_back(pointsIn[0]);
                data.push_back(fragmentsIn[0]);
                data.push_back(pointsIn[1]);
                data.push_back(fragmentsIn[1]);
                data.push_back(cut2);
                data.push_back(fragmentsIn[1] * (1 - t2) + fragmentsOut[0] * t2);
            }
        }
        else
        {
            data.push_back(pointsIn[0]);
            data.push_back(fragmentsIn[0]);
            data.push_back(cut1);
            data.push_back(fragmentsIn[0] * (1 - t1) + fragmentsOut[0] * t1);
            data.push_back(cut2);
            data.push_back(fragmentsIn[1] * (1 - t2) + fragmentsOut[0] * t2);

            if (t2 != 0.0) //Floating point precission check
            {
                data.push_back(pointsIn[1]);
                data.push_back(fragmentsIn[1]);
                data.push_back(pointsIn[0]);
                data.push_back(fragmentsIn[0]);
                data.push_back(cut2);
                data.push_back(fragmentsIn[1] * (1 - t2) + fragmentsOut[0] * t2);
            }
        }


        data.erase(data.begin(), data.begin() + (3 * offset));
    }


    if (countOut == 2)
    {
        SP_FLOAT t1 = d_in[0] / (d_in[0] - d_out[0]); //0 - 2
        SP_FLOAT t2 = d_in[0] / (d_in[0] - d_out[1]); //1 - 2

        sp::vector3f cut1 = pointsIn[0] + (pointsOut[0] - pointsIn[0]) * t1; //0 - 2
        sp::vector3f cut2 = pointsIn[0] + (pointsOut[1] - pointsIn[0]) * t2; //1 - 2

        if (pointsIn[0] != data[offset])
        {
            data.push_back(pointsIn[0]);
            data.push_back(fragmentsIn[0]);
            data.push_back(cut1);
            data.push_back(fragmentsIn[0] * (1 - t1) + fragmentsOut[0] * t1);
            data.push_back(cut2);
            data.push_back(fragmentsIn[0] * (1 - t2) + fragmentsOut[1] * t2);
        }
        else
        {
            data.push_back(pointsIn[0]);
            data.push_back(fragmentsIn[0]);
            data.push_back(cut2);
            data.push_back(fragmentsIn[0] * (1 - t2) + fragmentsOut[1] * t2);
            data.push_back(cut1);
            data.push_back(fragmentsIn[0] * (1 - t1) + fragmentsOut[0] * t1);
        }

        data.erase(data.begin(), data.begin() + (3 * offset));
    }
}
//-----------------------------------------------------


//Compares triangle to the plane and cuts it
void sp::compareToPlane(std::vector<sp::vector3f>& data, SP_FLOAT* relative, const sp::vector3f& onPlane, const sp::vector3f& normalPlane)
{
    SP_FLOAT d0 = sp::getDotProduct(normalPlane, (data[0] - onPlane));
    SP_FLOAT d1 = sp::getDotProduct(normalPlane, (data[1] - onPlane));
    SP_FLOAT d2 = sp::getDotProduct(normalPlane, (data[2] - onPlane));

    int countIn = 0;
    int countOut = 0;
    std::vector<sp::vector3f> pointsIn;
    std::vector<sp::vector3f> pointsOut;
    std::vector<sp::vector3f> fragmentsIn;
    std::vector<sp::vector3f> fragmentsOut;

    SP_FLOAT d[3];
    SP_FLOAT d_out[3];
    SP_FLOAT d_in[3];

    for (int i = 0; i < 3; i++)
    {
        d[i] = sp::getDotProduct(normalPlane, (data[i] - onPlane));
        if (d[i] < 0)
        {
            pointsOut.push_back(data[i]);
            d_out[countOut++] = d[i];
            d[i] = i;
        }
        else
        {
            pointsIn.push_back(data[i]);
            d_in[countIn++] = d[i];
            d[i] = i;
        }
    }

    if (countOut == 1)
    {
        SP_FLOAT t1 = d_in[0] / (d_in[0] - d_out[0]); //0 - 2
        SP_FLOAT t2 = d_in[1] / (d_in[1] - d_out[0]); //1 - 2

        sp::vector3f cut1 = pointsIn[0] + (pointsOut[0] - pointsIn[0]) * t1; //0 - 2
        sp::vector3f cut2 = pointsIn[1] + (pointsOut[0] - pointsIn[1]) * t2; //1 - 2

        if (pointsOut[0] != data[1])   //Switch to wind correct
        {
            data.push_back(pointsIn[0]);
            data.push_back(cut2);
            data.push_back(cut1);

            if (t2 != 0.0)  //Floating point precission check
            {
                data.push_back(pointsIn[0]);
                data.push_back(pointsIn[1]);
                data.push_back(cut2);
            }
        }
        else
        {
            data.push_back(pointsIn[0]);
            data.push_back(cut1);
            data.push_back(cut2);

            if (t2 != 0.0) //Floating point precission check
            {
                data.push_back(pointsIn[1]);
                data.push_back(pointsIn[0]);
                data.push_back(cut2);
            }
        }


        data.erase(data.begin(), data.begin() + 3);
        return;
    }


    if (countOut == 2)
    {
        SP_FLOAT t1 = d_in[0] / (d_in[0] - d_out[0]); //0 - 2
        SP_FLOAT t2 = d_in[0] / (d_in[0] - d_out[1]); //1 - 2

        sp::vector3f cut1 = pointsIn[0] + (pointsOut[0] - pointsIn[0]) * t1; //0 - 2
        sp::vector3f cut2 = pointsIn[0] + (pointsOut[1] - pointsIn[0]) * t2; //1 - 2

        if (pointsIn[0] != data[1])
        {
            data.push_back(pointsIn[0]);
            data.push_back(cut1);
            data.push_back(cut2);
        }
        else
        {
            data.push_back(pointsIn[0]);
            data.push_back(cut2);
            data.push_back(cut1);
        }

        data.erase(data.begin(), data.begin() + 3);
        return;
    }
}
//-----------------------------------------------------


//Calculates the intersection point--------------------
sp::vector3f sp::getIntersectionPoint(const sp::vector3f& pointOnPlane, const sp::vector3f& normalToPlane, const sp::vector3f& lineStart, const sp::vector3f& lineEnd)
{
    SP_FLOAT plane_d = -sp::getDotProduct(pointOnPlane, normalToPlane);
    SP_FLOAT ad = sp::getDotProduct(lineStart, normalToPlane);
    SP_FLOAT bd = sp::getDotProduct(lineEnd, normalToPlane);
    SP_FLOAT t = (-plane_d, - ad) / (bd - ad);
    sp::vector3f lineToIntersect = (lineEnd - lineStart) * t;
    return lineStart - lineToIntersect;
}
//-----------------------------------------------------