#ifndef _SP_VECTOR_H_
#define _SP_VECTOR_H_

#include "spCoreDefined.h"
#include <iostream>
#include <cmath>

namespace sp {
    //Vector 2------------------
    template<typename T>
    struct vector2
    {
        vector2(T v_x, T v_y) { x = v_x; y = v_y; }
        vector2()             { x = 0; y = 0; }

        vector2 operator+(const vector2& vec_2)
        {
            vector2 sum;
            sum.x = this->x + vec_2.x;
            sum.y = this->y + vec_2.y;
            return sum;
        }

        vector2 operator-(const vector2& vec_2)
        {
            vector2 sub;
            sub.x = this->x - vec_2.x;
            sub.y = this->y - vec_2.y;
            return sub;
        }

        vector2& operator-=(const vector2& vec_2)
        {
            this->x -= vec_2.x;
            this->y -= vec_2.y;
            return *this;    
        }

        vector2& operator+=(const vector2& vec2)
        {
            this->x += vec2.x;
            this->y += vec2.y;
            return *this;
        }

        bool operator!=(const vector2& vec_2)
        {
            if(x != vec_2.x || y != vec_2.y)
                return true;
            return false;
        }

        bool operator==(const vector2& vec_2)
        {
            if(x == vec_2.x && y == vec_2.y)
                return true;
            return false;
        }

        vector2 operator*(SP_FLOAT scale)
        {
            vector2 scl;
            scl.x = this->x * scale;
            scl.y = this->y * scale;
            return scl;
        }

        vector2 operator/(SP_FLOAT scale)
        {
            vector2 scl;
            scl.x = this->x / scale;
            scl.y = this->y / scale;
            return scl;
        }

        vector2& operator*=(SP_FLOAT scale)
        {
            this->x *= scale;
            this->y *= scale;
            return *this;    
        }

        vector2& operator/=(SP_FLOAT scale)
        {
            this->x /= scale;
            this->y /= scale;
            return *this;
        }
        
        friend std::ostream& operator<<(std::ostream& os, const vector2& vec2)
        {
            os << vec2.x << ", " << vec2.y;
            return os;
        }

        SP_FLOAT length() { return std::sqrt(x * x + y * y); }

        T x, y;
    };

    typedef vector2<int> vector2i;
    typedef vector2<float> vector2f;

    template<typename T>
    sp::vector2f getNormal(const sp::vector2<T>& vec2)
    {
        SP_FLOAT len = vec2.length();
        if(len != 0)
        {
            sp::vector2f normalVec;
            normalVec.x = vec2.x / len;
            normalVec.y = vec2.y / len;
            return normalVec;
        }
        return sp::vector2f(0, 0);
    }

    template<typename T>
    SP_FLOAT getDistance(const sp::vector2<T>& vec2_1, const sp::vector2<T>& vec2_2)
    {
        SP_FLOAT x_diff = vec2_1.x - vec2_2.x;
        SP_FLOAT y_diff = vec2_1.y - vec2_2.y;
        return std::sqrt((x_diff * x_diff + y_diff * y_diff));
    }

    template<typename T>
    SP_FLOAT getDotProduct(const sp::vector2<T>& vec2_1, const sp::vector2<T>& vec2_2)
    {
        return (vec2_1.x * vec2_2.x) + (vec2_1.y * vec2_2.y);
    }

    template<typename T>
    SP_FLOAT getCrossProduct(const sp::vector2<T>& vec2_1, const sp::vector2<T>& vec2_2)
    {
        return (vec2_1.x * vec2_2.y) - (vec2_1.y * vec2_2.x);
    }
    //--------------------------



    //Vector 3------------------
    template<typename T>
    struct vector3
    {
        vector3(T v_x, T v_y, T v_z) { x = v_x; y = v_y; z = v_z; }
        vector3()             { x = 0; y = 0; z = 0; }

        vector3 operator+(const vector3& vec_3) const
        {
            vector3 sum;
            sum.x = this->x + vec_3.x;
            sum.y = this->y + vec_3.y;
            sum.z = this->z + vec_3.z;
            return sum;
        }

        vector3 operator-(const vector3& vec_3) const
        {
            vector3 sub;
            sub.x = this->x - vec_3.x;
            sub.y = this->y - vec_3.y;
            sub.z = this->z - vec_3.z;
            return sub;
        }

        vector3& operator-=(const vector3& vec_3)
        {
            this->x -= vec_3.x;
            this->y -= vec_3.y;
            this->z -= vec_3.z;
            return *this;
        }

        vector3& operator+=(const vector3& vec3)
        {
            this->x += vec3.x;
            this->y += vec3.y;
            this->z += vec3.z;
            return *this;
        }

        bool operator!=(const vector3& vec_3)
        {
            if(x != vec_3.x || y != vec_3.y || z != vec_3.z)
                return true;
            return false;
        }

        bool operator==(const vector3& vec_3)
        {
            if(x == vec_3.x && y == vec_3.y && z == vec_3.z)
                return true;
            return false;
        }

        vector3 operator*(SP_FLOAT scale) const
        {
            vector3 scl;
            scl.x = this->x * scale;
            scl.y = this->y * scale;
            scl.z = this->z * scale;
            return scl;
        }

        vector3 operator/(SP_FLOAT scale) const
        {
            vector3 scl;
            scl.x = this->x / scale;
            scl.y = this->y / scale;
            scl.z = this->z / scale;
            return scl;
        }

        vector3& operator*=(SP_FLOAT scale)
        {
            this->x *= scale;
            this->y *= scale;
            this->z *= scale;
            return *this;    
        }

        vector3& operator/=(SP_FLOAT scale)
        {
            this->x /= scale;
            this->y /= scale;
            this->z /= scale;
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& os, const vector3& vec3)
        {
            os << vec3.x << ", " << vec3.y << ", " << vec3.z;
            return os;
        }

        SP_FLOAT length() { return std::sqrt(x * x + y * y + z * z); }

        T x, y, z;
    };

    typedef vector3<int> vector3i;
    typedef vector3<float> vector3f;


    template<typename T>
    sp::vector3f getNormal(sp::vector3<T> vec3)
    {
        SP_FLOAT len = vec3.length();
        if(len != 0)
        {
            sp::vector3f normalVec;
            normalVec.x = vec3.x / len;
            normalVec.y = vec3.y / len;
            normalVec.z = vec3.z / len;
            return normalVec;
        }
        return sp::vector3f(0, 0, 0);
    }

    template<typename T>
    SP_FLOAT getDistance(const sp::vector3<T>& vec3_1, const sp::vector3<T>& vec3_2)
    {
        SP_FLOAT x_diff = vec3_1.x - vec3_2.x;
        SP_FLOAT y_diff = vec3_1.y - vec3_2.y;
        SP_FLOAT z_diff = vec3_1.z - vec3_2.z;
        return std::sqrt((x_diff * x_diff + y_diff * y_diff + z_diff * z_diff));
    }

    template<typename T>
    SP_FLOAT getDotProduct(const sp::vector3<T>& vec3_1, const sp::vector3<T>& vec3_2)
    {
        return (vec3_1.x * vec3_2.x) + (vec3_1.y * vec3_2.y) + (vec3_1.z * vec3_2.z);
    }

    template<typename T>
    sp::vector3f getCrossProduct(const sp::vector3<T>& vec3_1, const sp::vector3<T>& vec3_2)
    {
        sp::vector3f corssProduct;
        corssProduct.x = (vec3_1.y * vec3_2.z) - (vec3_1.z * vec3_2.y);
        corssProduct.y = (vec3_1.z * vec3_2.x) - (vec3_1.x * vec3_2.z);
        corssProduct.z = (vec3_1.x * vec3_2.y) - (vec3_1.y * vec3_2.x);
        return corssProduct;
    }
    //--------------------------
}

#endif //SP_VECTOR_H_