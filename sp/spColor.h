#ifndef _SP_COLOR_H_
#define _SP_COLOR_H_
#include "spCoreDefined.h"

namespace sp {

    //Color structure implementation
    class Color
    {
    public:
        Color(SP_UINT8 r, SP_UINT8 g, SP_UINT8 b, SP_UINT8 a = 255);
        Color();

        unsigned long getHexRGB() const;    //Returns the color in HexRGB format
        unsigned long getHexBGR() const;    //Returns the color in HexBGR format. A windows thing.

        bool operator!=(const Color& col) const;
        Color operator+(const Color& col);
        Color operator*(const float& scalar);
    
    public:
        SP_UINT8 red, green, blue, alpha;
    };
};
#endif