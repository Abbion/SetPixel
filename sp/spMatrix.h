#ifndef _SP_MATRIX_H_
#define _SP_MATRIX_H_

#include "spVector.h"
#include <iostream>
#include <vector>

namespace sp {
    //Matrices------------------
    struct Matrix3
    {
        SP_FLOAT value[3][3];

        Matrix3();
        Matrix3 operator*(Matrix3& mat_3);
        friend std::ostream& operator<<(std::ostream& os, const Matrix3& mat3)
        {
            os  << mat3.value[0][0] << ", " << mat3.value[0][1] << ", " << mat3.value[0][2] << "\n"
                << mat3.value[1][0] << ", " << mat3.value[1][1] << ", " << mat3.value[1][2] << "\n"
                << mat3.value[2][0] << ", " << mat3.value[2][1] << ", " << mat3.value[2][2] << "\n";
            return os;
        }
    };

    struct Matrix4
    {
        SP_FLOAT value[4][4];

        Matrix4();
        Matrix4 operator*(Matrix4& mat_4);
        friend std::ostream& operator<<(std::ostream& os, const Matrix4& mat4)
        {
            os << mat4.value[0][0] << " " << mat4.value[0][1] << " " << mat4.value[0][2] << " " << mat4.value[0][3] << "\n"
               << mat4.value[1][0] << " " << mat4.value[1][1] << " " << mat4.value[1][2] << " " << mat4.value[1][3] << "\n"
               << mat4.value[2][0] << " " << mat4.value[2][1] << " " << mat4.value[2][2] << " " << mat4.value[2][3] << "\n"
               << mat4.value[3][0] << " " << mat4.value[3][1] << " " << mat4.value[3][2] << " " << mat4.value[3][3] << "\n";
            return os;
        }
    };
    //--------------------------

    struct Transform
    {
        static sp::Matrix3 translate(sp::vector2f pos);
        static sp::Matrix4 translate(sp::vector3f pos);
        
        static sp::Matrix3 scale(sp::vector2f scale);
        static sp::Matrix4 scale(sp::vector3f scale);

        static sp::Matrix3 rotate(SP_FLOAT angle);
        static sp::Matrix4 rotate(SP_FLOAT angle, sp::vector3f dir);
        static sp::Matrix4 rotate(sp::vector3f angle);

        static sp::Matrix4 rotateByX(SP_FLOAT angle, bool degrees = true);
        static sp::Matrix4 rotateByY(SP_FLOAT angle, bool degrees = true);
        static sp::Matrix4 rotateByZ(SP_FLOAT angle, bool degrees = true);

        static sp::Matrix4 lookAt(sp::vector3f pos, sp::vector3f target, sp::vector3f up);

        static sp::vector3f perspectiveSpaceProjection(const sp::vector3f& vertex, SP_FLOAT w);
        static sp::Matrix4 cameraProjectionMatrix(SP_FLOAT near, SP_FLOAT Far, SP_FLOAT angle);

        static void applyTransform(sp::vector2f* vertexArr, int count, const Matrix3& transform);
        static void applyTransform(sp::vector3f* vertexArr, int count, const Matrix4& transform);
        static void applyTransform(std::vector<sp::vector3f>& vertexVec, const Matrix4& transform, bool hasTexture = false);
    };

    //--------------------------
}

#endif //SP_MATRIX_H_