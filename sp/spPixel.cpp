#include "spPixel.h"
#include <iostream>
#include <string.h>


//-----------------------------------------------------
sp::Pixel::Pixel(const sp::vector2i& pos, const Color& col, SP_FLOAT depth) :
    m_position(pos), m_color(col), m_depth(depth)
{

}

sp::Pixel::Pixel(const sp::vector2i& pos) :
    m_position(pos), m_color(Color(255, 255, 255))
{

}
//-----------------------------------------------------


//-----------------------------------------------------
void sp::Pixel::setPosition(const sp::vector2i& pos)
{
    m_position = pos;
}
//-----------------------------------------------------


//-----------------------------------------------------
void sp::Pixel::setColor(const Color& col)
{
    m_color = col;
}
//-----------------------------------------------------


//-----------------------------------------------------
void sp::Pixel::setDepth(SP_FLOAT depth)
{
    m_depth = depth;
}
//-----------------------------------------------------