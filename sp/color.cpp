#include "color.h"

//-----------------------------------------------------
sp::Color::Color(uint8 r, uint8 g, uint8 b, uint8 a) : 
    red(r), green(g), blue(b), alpha(a)
{

}

sp::Color::Color()
{
    red = 255;
    green = 255; 
    blue = 255; 
    alpha = 255;
}
//-----------------------------------------------------



//-----------------------------------------------------
unsigned long sp::Color::getHexRGB() const
{    
    return ((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff);
}
//-----------------------------------------------------


unsigned long sp::Color::getHexBGR() const
{
    return ((blue & 0xff) << 16) + ((green & 0xff) << 8) + (red & 0xff);
}


//-----------------------------------------------------
bool sp::Color::operator!=(const Color& col) const
{
    if(red != col.red && green != col.green && blue != col.blue)
        return true;
    return false;
}
//-----------------------------------------------------