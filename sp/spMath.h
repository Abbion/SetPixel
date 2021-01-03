#ifndef _SP_MATH_H_
#define _SP_MATH_H_
#include <cstdarg>
#include <iostream>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

#include "spCoreDefined.h"
#include "spVector.h"
#include "spMatrix.h"

#define SP_DEGTORAD (M_PI/180.0)


namespace sp {

    //Coordinate converter------
    struct coordConverter
    {
        static vector2f normalToViewPosF(const vector2f& normal);
        static vector2i normalToViewPosI(const vector2f& normal);
        static vector2i nromalToViewSizeI(const vector2f& normal);
        static bool pointInView(const vector2f& point);

        static int m_renderWidth, m_renderHeight;
        static SP_FLOAT m_invAspectRatio;
    };
    //--------------------------
    

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
