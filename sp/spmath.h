#ifndef SP_MATH_H_
#define SP_MATH_H_
#include "coreDefines.h"
#include <cstdarg>
#include <iostream>

namespace sp {

    template<typename T>
    struct vector2
    {
        vector2(T v_x, T v_y) { x = v_x; y = v_y; }
        vector2()             { x = 0; y = 0; }

        vector2 operator+(vector2& vec_2)
        {
            vector2 sum;
            sum.x = this->x + vec_2.x;
            sum.y = this->y + vec_2.y;
            return sum;
        }

        vector2 operator-(vector2& vec_2)
        {
            vector2 sub;
            sub.x = this->x - vec_2.x;
            sub.y = this->y - vec_2.y;
            return sub;
        }

        bool operator!=(vector2& vec_2)
        {
            if(x != vec_2.x || y != vec_2.y)
                return true;
            return false;
        }

        void scale(SP_FLOAT scale) { x *= scale; y *= scale; }
        
        SP_FLOAT length() { return std::sqrt(x * x + y * y); }

        SP_FLOAT distance(vector2 vec_2) 
        {
            vector2 sub(x - vec_2.x, y - vec_2.y);
            return sub.length();
        }

        vector2<float> getNormal()
        {
            float len = length();
            vector2<float> normalVec;
            normalVec.x = x / len;
            normalVec.y = y / len;
            return normalVec;
        }

        T x, y;
    };

    typedef vector2<int> vector2i;
    typedef vector2<float> vector2f;

    template<typename T>
    struct vector3
    {
        vector3(T v_x, T v_y, T v_z) { x = v_x; y = v_y; z = v_z; }
        vector3()             { x = 0; y = 0; z = 0; }

        vector3 operator+(vector3& vec_3)
        {
            vector3 sum;
            sum.x = this->x + vec_3.x;
            sum.y = this->y + vec_3.y;
            sum.z = this->z + vec_3.z;
            return sum;
        }

        vector3 operator-(vector3& vec_3)
        {
            vector3 sub;
            sub.x = this->x - vec_3.x;
            sub.y = this->y - vec_3.y;
            sub.z = this->z - vec_3.z;
            return sub;
        }

        void scale(SP_FLOAT scale) { x *= scale; y *= scale; z *= scale; }
        
        SP_FLOAT length() { return std::sqrt(x * x + y * y + z * z); }

        SP_FLOAT distance(vector3 vec_3) 
        {
            vector3 sub(x - vec_3.x, y - vec_3.y, z - vec_3.z);
            return sub.length();
        }

        vector3<float> getNormal()
        {
            float len = length();
            vector3<float> normalVec;
            normalVec.x = x / len;
            normalVec.y = y / len;
            normalVec.z = z / len;
            return normalVec;
        }
        T x, y, z;
    };

    typedef vector3<int> vector3i;
    typedef vector3<float> vector3f;
    

    //Coordinate converter
    struct coordConverter
    {
        static vector2f normalToViewF(const vector2f& normal);
        static vector2i normalToViewI(const vector2f& normal);

        static int m_renderWidth, m_renderHeight;
    };
    //----------------
    
    template<typename T, typename ...Args>
    auto minOf(T next, Args... args)
    {
        if constexpr(sizeof...(Args) > 0)
            return next < minOf(args...) ? next : minOf(args...);

        return next;
    }

    template<typename T, typename ...Args>
    auto maxOf(T next, Args... args)
    {
        if constexpr (sizeof...(Args) > 0)
            return next > maxOf(args...) ? next : maxOf(args...);

        return next;
    }
};

#endif // !SP_MATH_H_
