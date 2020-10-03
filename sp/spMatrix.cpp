#include "spMatrix.h"
#include "spMath.h"

//-----------------------------------------------
sp::Matrix3::Matrix3()
{
    value[0][0] = 1.0f; value[0][1] = 0.0f; value[0][2] = 0.0f;
    value[1][0] = 0.0f; value[1][1] = 1.0f; value[1][2] = 0.0f;
    value[2][0] = 0.0f; value[2][1] = 0.0f; value[2][2] = 1.0f;
}
//-----------------------------------------------



//-----------------------------------------------
sp::Matrix3 sp::Matrix3::operator*(Matrix3& mat_3)
{
    Matrix3 resultMatrix;

    resultMatrix.value[0][0] = (this->value[0][0] * mat_3.value[0][0]) + (this->value[0][1] * mat_3.value[1][0]) + (this->value[0][2] * mat_3.value[2][0]);
    resultMatrix.value[0][1] = (this->value[0][0] * mat_3.value[0][1]) + (this->value[0][1] * mat_3.value[1][1]) + (this->value[0][2] * mat_3.value[2][1]);
    resultMatrix.value[0][2] = (this->value[0][0] * mat_3.value[0][2]) + (this->value[0][1] * mat_3.value[1][2]) + (this->value[0][2] * mat_3.value[2][2]);

    resultMatrix.value[1][0] = (this->value[1][0] * mat_3.value[0][0]) + (this->value[1][1] * mat_3.value[1][0]) + (this->value[1][2] * mat_3.value[2][0]);
    resultMatrix.value[1][1] = (this->value[1][0] * mat_3.value[0][1]) + (this->value[1][1] * mat_3.value[1][1]) + (this->value[1][2] * mat_3.value[2][1]);
    resultMatrix.value[1][2] = (this->value[1][0] * mat_3.value[0][2]) + (this->value[1][1] * mat_3.value[1][2]) + (this->value[1][2] * mat_3.value[2][2]);

    resultMatrix.value[2][0] = (this->value[2][0] * mat_3.value[0][0]) + (this->value[2][1] * mat_3.value[1][0]) + (this->value[2][2] * mat_3.value[2][0]);
    resultMatrix.value[2][1] = (this->value[2][0] * mat_3.value[0][1]) + (this->value[2][1] * mat_3.value[1][1]) + (this->value[2][2] * mat_3.value[2][1]);
    resultMatrix.value[2][2] = (this->value[2][0] * mat_3.value[0][2]) + (this->value[2][1] * mat_3.value[1][2]) + (this->value[2][2] * mat_3.value[2][2]);

    return resultMatrix;
}
//-----------------------------------------------



//-----------------------------------------------
sp::Matrix4::Matrix4()
{
    value[0][0] = 1.0; value[0][1] = 0.0; value[0][2] = 0.0; value[0][3] = 0.0;
    value[1][0] = 0.0; value[1][1] = 1.0; value[1][2] = 0.0; value[1][3] = 0.0;
    value[2][0] = 0.0; value[2][1] = 0.0; value[2][2] = 1.0; value[2][3] = 0.0;
    value[3][0] = 0.0; value[3][1] = 0.0; value[3][2] = 0.0; value[3][3] = 1.0;
}
//-----------------------------------------------



//-----------------------------------------------
sp::Matrix4 sp::Matrix4::operator*(Matrix4& mat_4)
{
    Matrix4 resultMatrix;

    resultMatrix.value[0][0] = (this->value[0][0] * mat_4.value[0][0]) + (this->value[0][1] * mat_4.value[1][0]) + (this->value[0][2] * mat_4.value[2][0]) + (this->value[0][3] * mat_4.value[3][0]);
    resultMatrix.value[0][1] = (this->value[0][0] * mat_4.value[0][1]) + (this->value[0][1] * mat_4.value[1][1]) + (this->value[0][2] * mat_4.value[2][1]) + (this->value[0][3] * mat_4.value[3][1]);
    resultMatrix.value[0][2] = (this->value[0][0] * mat_4.value[0][2]) + (this->value[0][1] * mat_4.value[1][2]) + (this->value[0][2] * mat_4.value[2][2]) + (this->value[0][3] * mat_4.value[3][2]);
    resultMatrix.value[0][3] = (this->value[0][0] * mat_4.value[0][3]) + (this->value[0][1] * mat_4.value[1][3]) + (this->value[0][2] * mat_4.value[2][3]) + (this->value[0][3] * mat_4.value[3][3]);

    resultMatrix.value[1][0] = (this->value[1][0] * mat_4.value[0][0]) + (this->value[1][1] * mat_4.value[1][0]) + (this->value[1][2] * mat_4.value[2][0]) + (this->value[1][3] * mat_4.value[3][0]);
    resultMatrix.value[1][1] = (this->value[1][0] * mat_4.value[0][1]) + (this->value[1][1] * mat_4.value[1][1]) + (this->value[1][2] * mat_4.value[2][1]) + (this->value[1][3] * mat_4.value[3][1]);
    resultMatrix.value[1][2] = (this->value[1][0] * mat_4.value[0][2]) + (this->value[1][1] * mat_4.value[1][2]) + (this->value[1][2] * mat_4.value[2][2]) + (this->value[1][3] * mat_4.value[3][2]);
    resultMatrix.value[1][3] = (this->value[1][0] * mat_4.value[0][3]) + (this->value[1][1] * mat_4.value[1][3]) + (this->value[1][2] * mat_4.value[2][3]) + (this->value[1][3] * mat_4.value[3][3]);

    resultMatrix.value[2][0] = (this->value[2][0] * mat_4.value[0][0]) + (this->value[2][1] * mat_4.value[1][0]) + (this->value[2][2] * mat_4.value[2][0]) + (this->value[2][3] * mat_4.value[3][0]);
    resultMatrix.value[2][1] = (this->value[2][0] * mat_4.value[0][1]) + (this->value[2][1] * mat_4.value[1][1]) + (this->value[2][2] * mat_4.value[2][1]) + (this->value[2][3] * mat_4.value[3][1]);
    resultMatrix.value[2][2] = (this->value[2][0] * mat_4.value[0][2]) + (this->value[2][1] * mat_4.value[1][2]) + (this->value[2][2] * mat_4.value[2][2]) + (this->value[2][3] * mat_4.value[3][2]);
    resultMatrix.value[2][3] = (this->value[2][0] * mat_4.value[0][3]) + (this->value[2][1] * mat_4.value[1][3]) + (this->value[2][2] * mat_4.value[2][3]) + (this->value[2][3] * mat_4.value[3][3]);

    resultMatrix.value[3][0] = (this->value[3][0] * mat_4.value[0][0]) + (this->value[3][1] * mat_4.value[1][0]) + (this->value[3][2] * mat_4.value[2][0]) + (this->value[3][3] * mat_4.value[3][0]);
    resultMatrix.value[3][1] = (this->value[3][0] * mat_4.value[0][1]) + (this->value[3][1] * mat_4.value[1][1]) + (this->value[3][2] * mat_4.value[2][1]) + (this->value[3][3] * mat_4.value[3][1]);
    resultMatrix.value[3][2] = (this->value[3][0] * mat_4.value[0][2]) + (this->value[3][1] * mat_4.value[1][2]) + (this->value[3][2] * mat_4.value[2][2]) + (this->value[3][3] * mat_4.value[3][2]);
    resultMatrix.value[3][3] = (this->value[3][0] * mat_4.value[0][3]) + (this->value[3][1] * mat_4.value[1][3]) + (this->value[3][2] * mat_4.value[2][3]) + (this->value[3][3] * mat_4.value[3][3]);

    return resultMatrix;
}
//-----------------------------------------------



//======================TRANSFORMS====================
//-----------------------------------------------
sp::Matrix3 sp::Transform::translate(sp::vector2f pos)
{
    Matrix3 translateMatrix;
    translateMatrix.value[2][0] = pos.x;
    translateMatrix.value[2][1] = pos.y;
    return translateMatrix;
}
//-----------------------------------------------



//-----------------------------------------------
sp::Matrix4 sp::Transform::translate(sp::vector3f pos)
{
    Matrix4 translateMatrix;
    translateMatrix.value[3][0] = pos.x;
    translateMatrix.value[3][1] = pos.y;
    translateMatrix.value[3][2] = pos.z;
    return translateMatrix;
}
//-----------------------------------------------



//-----------------------------------------------
sp::Matrix3 sp::Transform::scale(sp::vector2f scale)
{
    Matrix3 scaleMatrix;
    scaleMatrix.value[0][0] = scale.x;
    scaleMatrix.value[1][1] = scale.y;
    return scaleMatrix;
}
//-----------------------------------------------



//-----------------------------------------------
sp::Matrix4 sp::Transform::scale(sp::vector3f scale)
{
    Matrix4 scaleMatrix;
    scaleMatrix.value[0][0] = scale.x;
    scaleMatrix.value[1][1] = scale.y;
    scaleMatrix.value[2][2] = scale.y;
    return scaleMatrix;
}
//-----------------------------------------------



//-----------------------------------------------
sp::Matrix3 sp::Transform::rotate(SP_FLOAT angle)
{
    Matrix3 rotationMatrix;

    if(angle != 0)
    {
        SP_FLOAT radians = SP_DEGTORAD * angle;
        SP_FLOAT cos = std::cos(radians);
        SP_FLOAT sin = std::sin(radians);
        
        rotationMatrix.value[0][0] = cos;
        rotationMatrix.value[0][1] = sin;
        rotationMatrix.value[1][0] = -sin;
        rotationMatrix.value[1][1] = cos;
    }
    return rotationMatrix;
}
//-----------------------------------------------



//-----------------------------------------------
sp::Matrix4 sp::Transform::rotate(SP_FLOAT angle, sp::vector3f dir)
{
    //Y axis--------------------
    SP_FLOAT Yrot = atan(std::numeric_limits<float>::max());
    if(dir.z != 0)
        Yrot = atan(dir.x / dir.z);
    else if (dir.x == 0)
        Yrot = atan(0);
    //--------------------------

    //X axis--------------------
    SP_FLOAT projZ = sqrt((dir.x * dir.x) + (dir.z * dir.z));
    SP_FLOAT Xrot = atan(std::numeric_limits<float>::max());
    if(projZ > 0)
        Xrot = atan(dir.y / projZ);
    else if (dir.y == 0)
        Xrot = atan(0);
    //--------------------------


    sp::Matrix4 XRotMat = sp::Transform::rotateByY(Yrot, false);
    sp::Matrix4 YRotMat = sp::Transform::rotateByX(Xrot, false);
    sp::Matrix4 ZRotMat = sp::Transform::rotateByZ(angle);

    sp::Matrix4 rotationMatirx = ZRotMat * XRotMat * YRotMat;
    return rotationMatirx;
}
//-----------------------------------------------



//-----------------------------------------------
sp::Matrix4 sp::Transform::rotate(sp::vector3f angle)
{
    sp::Matrix4 XRotMat = sp::Transform::rotateByX(angle.x);
    sp::Matrix4 YRotMat = sp::Transform::rotateByY(angle.y);
    sp::Matrix4 ZRotMat = sp::Transform::rotateByZ(angle.z);

    sp::Matrix4 rotationMatirx = ZRotMat * XRotMat * YRotMat;
    return rotationMatirx;
}
//-----------------------------------------------



//-----------------------------------------------
sp::Matrix4 sp::Transform::rotateByX(SP_FLOAT angle, bool degrees)
{
    Matrix4 rotationMatrix;

    if(angle != 0)
    {
        SP_FLOAT radians = angle;
        if(degrees)
             radians = SP_DEGTORAD * angle;
    
        SP_FLOAT cos = std::cos(radians);
        SP_FLOAT sin = std::sin(radians);
        
        rotationMatrix.value[1][1] = cos;
        rotationMatrix.value[1][2] = -sin;
        rotationMatrix.value[2][1] = sin;
        rotationMatrix.value[2][2] = cos;
    }
    return rotationMatrix;
}
//-----------------------------------------------



//-----------------------------------------------
sp::Matrix4 sp::Transform::rotateByY(SP_FLOAT angle, bool degrees)
{
    Matrix4 rotationMatrix;

    if(angle != 0)
    {
        SP_FLOAT radians = angle;
        if(degrees)
             radians = SP_DEGTORAD * angle;

        SP_FLOAT cos = std::cos(radians);
        SP_FLOAT sin = std::sin(radians);
        
        rotationMatrix.value[0][0] = cos;
        rotationMatrix.value[0][2] = -sin;
        rotationMatrix.value[2][0] = sin;
        rotationMatrix.value[2][2] = cos;
    }
    return rotationMatrix;
}
//-----------------------------------------------



//-----------------------------------------------
sp::Matrix4 sp::Transform::rotateByZ(SP_FLOAT angle, bool degrees)
{
    Matrix4 rotationMatrix;

    if(angle != 0)
    {
        SP_FLOAT radians = angle;
        if(degrees)
             radians = SP_DEGTORAD * angle;

        SP_FLOAT cos = std::cos(radians);
        SP_FLOAT sin = std::sin(radians);
        
        rotationMatrix.value[0][0] = cos;
        rotationMatrix.value[0][1] = sin;
        rotationMatrix.value[1][0] = -sin;
        rotationMatrix.value[1][1] = cos;
    }
    return rotationMatrix;
}
//-----------------------------------------------



//-----------------------------------------------
sp::Matrix4 sp::Transform::lookAt(sp::vector3f pos, sp::vector3f target, sp::vector3f up)
{
    sp::vector3f camDir = sp::getNormal(pos - target);
    sp::vector3f camRight = sp::getNormal(sp::getCrossProduct(up, camDir));
    sp::vector3f camUp = sp::getNormal(sp::getCrossProduct(camDir, camRight));


    sp::Matrix4 lookAtMatrix;
    lookAtMatrix.value[0][0] = camRight.x;
    lookAtMatrix.value[1][0] = camRight.y;
    lookAtMatrix.value[2][0] = camRight.z;
    lookAtMatrix.value[3][0] = - sp::getDotProduct(camRight, pos);

    lookAtMatrix.value[0][1] = camUp.x;
    lookAtMatrix.value[1][1] = camUp.y;
    lookAtMatrix.value[2][1] = camUp.z;
    lookAtMatrix.value[3][1] = - sp::getDotProduct(camUp, pos);

    lookAtMatrix.value[0][2] = camDir.x;
    lookAtMatrix.value[1][2] = camDir.y;
    lookAtMatrix.value[2][2] = camDir.z;
    lookAtMatrix.value[3][2] = - sp::getDotProduct(camDir, pos);


    return lookAtMatrix;
}
//-----------------------------------------------



//-----------------------------------------------
sp::vector3f sp::Transform::perspectiveSpaceProjection(const sp::vector3f& vertex, SP_FLOAT w)
{
    return sp::vector3f(vertex.x / w, vertex.y / w, vertex.z / w);
}
//-----------------------------------------------



//-----------------------------------------------
sp::Matrix4 sp::Transform::cameraProjectionMatrix(SP_FLOAT near, SP_FLOAT far, SP_FLOAT angle)
{
    sp::Matrix4 projectionMatrix;

    if (far != near && angle != 0.0)
    {
        SP_FLOAT a = (far + near)/(far-near);
        SP_FLOAT b = (2*near*far)/(far-near);
        SP_FLOAT cot = 1.0 / std::tan(angle / 2.0 * SP_DEGTORAD);
        
        projectionMatrix.value[0][0] = sp::coordConverter::m_invAspectRatio * cot;
        projectionMatrix.value[1][1] = cot;
        projectionMatrix.value[2][2] = a;
        projectionMatrix.value[2][3] = -1;
        projectionMatrix.value[3][2] = b;
    }

    return projectionMatrix;
}
//-----------------------------------------------



//-----------------------------------------------
void sp::Transform::applyTransform(sp::vector2f* vertexArr, int count, const Matrix3& transform)
{
    for (int i = 0; i < count; i++)
    {
        sp::vector2f temp;
        temp.x = (vertexArr[i].x * transform.value[0][0]) + (vertexArr[i].y * transform.value[1][0]) + (1 * transform.value[2][0]);
        temp.y = (vertexArr[i].x * transform.value[0][1]) + (vertexArr[i].y * transform.value[1][1]) + (1 * transform.value[2][1]);
        vertexArr[i] = temp;
    }
}
//-----------------------------------------------



//-----------------------------------------------
void sp::Transform::applyTransform(sp::vector3f* vertexArr, int count, const Matrix4& transform)
{
    for (int i = 0; i < count; i++)
    {
        sp::vector3f temp;
        temp.x = (vertexArr[i].x * transform.value[0][0]) + (vertexArr[i].y * transform.value[1][0]) + (vertexArr[i].z * transform.value[2][0]) + (1 * transform.value[3][0]);
        temp.y = (vertexArr[i].x * transform.value[0][1]) + (vertexArr[i].y * transform.value[1][1]) + (vertexArr[i].z * transform.value[2][1]) + (1 * transform.value[3][1]);
        temp.z = (vertexArr[i].x * transform.value[0][2]) + (vertexArr[i].y * transform.value[1][2]) + (vertexArr[i].z * transform.value[2][2]) + (1 * transform.value[3][2]);

        SP_FLOAT w = (vertexArr[i].x * transform.value[0][3]) + (vertexArr[i].y * transform.value[1][3]) + (vertexArr[i].z * transform.value[2][3]) + (1 * transform.value[3][3]);
        temp.x /= w;
        temp.y /= w;
        temp.z /= w;
        vertexArr[i] = temp;
    }
}
//-----------------------------------------------



//-----------------------------------------------
void sp::Transform::applyTransform(std::vector<sp::vector3f>& vertexVec, const Matrix4& transform)
{
    for(int i = 0; i < vertexVec.size(); i++)
    {
        sp::vector3f temp;
        temp.x = (vertexVec[i].x * transform.value[0][0]) + (vertexVec[i].y * transform.value[1][0]) + (vertexVec[i].z * transform.value[2][0]) + (1 * transform.value[3][0]);
        temp.y = (vertexVec[i].x * transform.value[0][1]) + (vertexVec[i].y * transform.value[1][1]) + (vertexVec[i].z * transform.value[2][1]) + (1 * transform.value[3][1]);
        temp.z = (vertexVec[i].x * transform.value[0][2]) + (vertexVec[i].y * transform.value[1][2]) + (vertexVec[i].z * transform.value[2][2]) + (1 * transform.value[3][2]);

        SP_FLOAT w = (vertexVec[i].x * transform.value[0][3]) + (vertexVec[i].y * transform.value[1][3]) + (vertexVec[i].z * transform.value[2][3]) + (1 * transform.value[3][3]);
        temp.x /= w;
        temp.y /= w;
        temp.z /= w;
        vertexVec[i] = temp;
    }
}
//-----------------------------------------------