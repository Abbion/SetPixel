#ifndef _SP_COLOR_
#define _SP_COLOR_

//Color implementation.
namespace sp {
    typedef unsigned char uint8;

    class Color
    {
    public:
        Color(uint8 r, uint8 g, uint8 b, uint8 a = 255);
        Color();

        unsigned long getHexRGB() const;    //Returns the color in HexRGB format
        unsigned long getHexBGR() const;    //Returns the color in HexBGR format. A windows thing.

        bool operator!=(const Color& col) const;
    
    public:
        uint8 red, green, blue, alpha;
    };
};
#endif