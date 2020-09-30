#include "spAlgorithms.h"
#include "spCoreDefined.h"
#include "spVector.h"

bool sp::faceCulling(const sp::vector3f& a, const sp::vector3f& b, const sp::vector3f& c)
{
    SP_FLOAT shoelace = ((a.x * b.y) + (b.x * c.y) + (c.x * a.y)) - ((a.y * b.x) + (b.y * c.x) + (c.y * a.x));
    if(shoelace < 0)
        return false;
    return true;
}

void sp::clipToCamera(std::vector<sp::vector3f>& vertexVec, const sp::Camera& cam)
{
    std::vector<sp::vector3f> clipPlanes = cam.getCameraClipPlanes();

    for (int i = 0; i < vertexVec.size(); i+= 3)
    {
        std::vector<sp::vector3f> clipped;
        bool success = clipTriangleToPlanes(vertexVec[i], vertexVec[i + 1], vertexVec[i + 2], clipped, clipPlanes);
        if(success)
        {
            vertexVec.erase(vertexVec.begin() + i, vertexVec.begin() + i + 3);
            vertexVec.insert(vertexVec.begin() + i, clipped.begin(), clipped.end());
            i = i + clipped.size() - 3;
        }
        else
        {
            vertexVec.erase(vertexVec.begin() + i, vertexVec.begin() + i + 3);
            i -= 3;
        }
        
    }
    
}

bool sp::clipTriangleToPlanes(const sp::vector3f& a, const sp::vector3f& b, const sp::vector3f& c, std::vector<sp::vector3f>& output, const std::vector<sp::vector3f>& planes)
{
    output.push_back(a);
    output.push_back(b);
    output.push_back(c);
    SP_FLOAT relative[3];
    
    int planesCount = planes.size();

    for (int i = 0; i < planesCount; i += 2)
    {  
        int s = output.size() / 3;
        for (int j = 0; j < s; j++)
        {
            int outCount = countPointsOut(output, relative, planes[i], planes[i + 1]);
            if(outCount == 3)
                output.erase(output.begin(), output.begin() + 3);
            if(outCount == 0)
            {
                output.push_back(output[0]);
                output.push_back(output[1]);
                output.push_back(output[2]);
                output.erase(output.begin(), output.begin() + 3);
            }
            
            if(output.empty())
                return false;

            compareToPlane(output, outCount, relative, planes[i], planes[i + 1]);
        }
    }
    return true;
}

int sp::countPointsOut(std::vector<sp::vector3f>& vertex, SP_FLOAT* relative, const sp::vector3f& onPlane, const sp::vector3f& normalPlane)
{
    int countOut = 0;

    for (int i = 0; i < 3; i++)
    {
        sp::vector3f dff = vertex[i] - onPlane;
        relative[i] = sp::getDotProduct(normalPlane, dff);
        if(relative[i] < 0)
            countOut++;
    }

    return countOut;
}

void sp::compareToPlane(std::vector<sp::vector3f>& vertex ,int out, SP_FLOAT* relative, const sp::vector3f& onPlane, const sp::vector3f& normalPlane)
{
    SP_FLOAT d0 = sp::getDotProduct(normalPlane, (vertex[0] - onPlane));
    SP_FLOAT d1 = sp::getDotProduct(normalPlane, (vertex[1] - onPlane));
    SP_FLOAT d2 = sp::getDotProduct(normalPlane, (vertex[2] - onPlane));

    int countIn = 0;
    int countOut = 0;
    std::vector<sp::vector3f> pointsIn;
    std::vector<sp::vector3f> pointsOut;


    SP_FLOAT d[3];
    SP_FLOAT d_out[3];
    SP_FLOAT d_in[3];

    for (int i = 0; i < 3; i++)
    {
        d[i] = sp::getDotProduct(normalPlane, (vertex[i] - onPlane));
        if(d[i] < 0)
        {
            pointsOut.push_back(vertex[i]);
            d_out[countOut++] = d[i];
        }
        else
        {
            pointsIn.push_back(vertex[i]);
            d_in[countIn++] = d[i];
        }
    }
    
    if(countOut == 1)
    {
        SP_FLOAT t1 = d_in[0]/(d_in[0] - d_out[0]); //0 - 2
        SP_FLOAT t2 = d_in[1]/(d_in[1] - d_out[0]); //1 - 2

        sp::vector3f cut1 = pointsIn[0] + (pointsOut[0] - pointsIn[0]) * t1; //0 - 2
        sp:;vector3f cut2 = pointsIn[1] + (pointsOut[0] - pointsIn[1]) * t2; //1 - 2

        if(pointsOut[0] != vertex[1])   //Switch to wind correct
        {
            vertex.push_back(pointsIn[0]);
            vertex.push_back(cut2);
            vertex.push_back(cut1);

            vertex.push_back(pointsIn[0]);
            vertex.push_back(pointsIn[1]);
            vertex.push_back(cut2);
        }
        else
        {
            vertex.push_back(pointsIn[0]);
            vertex.push_back(cut1);
            vertex.push_back(cut2);

            vertex.push_back(pointsIn[1]);
            vertex.push_back(pointsIn[0]);
            vertex.push_back(cut2);
        }
        

        vertex.erase(vertex.begin(), vertex.begin() + 3);
        return;
    }

    if(countOut == 2)
    {
        SP_FLOAT t1 = d_in[0]/(d_in[0] - d_out[0]); //0 - 2
        SP_FLOAT t2 = d_in[0]/(d_in[0] - d_out[1]); //1 - 2

        sp::vector3f cut1 = pointsIn[0] + (pointsOut[0] - pointsIn[0]) * t1; //0 - 2
        sp::vector3f cut2 = pointsIn[0] + (pointsOut[1] - pointsIn[0]) * t2; //1 - 2

        if (pointsIn[0] != vertex[1])
        {
            vertex.push_back(pointsIn[0]);
            vertex.push_back(cut1);
            vertex.push_back(cut2);
        }
        else
        {
            vertex.push_back(pointsIn[0]);
            vertex.push_back(cut2);
            vertex.push_back(cut1);
        }

        vertex.erase(vertex.begin(), vertex.begin() + 3);
        return;
    }
}



sp::vector3f sp::getIntersectionPoint(const sp::vector3f& pointOnPlane, const sp::vector3f& normalToPlane, const sp::vector3f& lineStart, const sp::vector3f& lineEnd)
{
    SP_FLOAT plane_d = -sp::getDotProduct(pointOnPlane, normalToPlane);
    SP_FLOAT ad = sp::getDotProduct(lineStart, normalToPlane);
    SP_FLOAT bd = sp::getDotProduct(lineEnd, normalToPlane);
    SP_FLOAT t = (-plane_d, - ad) / (bd - ad);
    sp::vector3f lineToIntersect = (lineEnd - lineStart) * t;
    return lineStart - lineToIntersect;
}

int sp::clipTriangleToPlane(const sp::vector3f& pointOnPlane, const sp::vector3f& normalToPlane, std::vector<sp::vector3f>& vertexVec)
{
    int countOut = 0;
    int countIn = 0;

    sp::vector3f* vertexOut[3];
    sp::vector3f* vertexIn[3];

    for (int i = 0; i < 3; i++)
    {
        sp::vector3f dff = vertexVec[i] - pointOnPlane;
        SP_FLOAT side = sp::getDotProduct(normalToPlane, dff);
        std::cout << side << " ";
        if(side < 0)
           vertexOut[countOut++] = &vertexVec[i];
        else
            vertexIn[countIn++] = &vertexVec[i];
    }

    std::cout << std::endl;

    if(countOut == 0)
        return 0;
    else if(countOut == 3)
        return 3;
        
}