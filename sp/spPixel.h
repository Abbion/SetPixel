#ifndef _SP_PIXEL_H_
#define _SP_PIXEL_H_
#include "spColor.h"
#include "spMath.h"
#include <forward_list>

namespace sp
{   
    class Pixel
    {
    public:
        Pixel(const sp::vector2i& pos, const Color& col, SP_FLOAT depth = 0);
        Pixel(const sp::vector2i& pos);
        Pixel() {};
        ~Pixel() {};

        void setPosition(const sp::vector2i& pos);
        void setColor(const Color& col);
        void setDepth(SP_FLOAT depth);


        const vector2i& getPosition() const { return m_position; }
        const Color& getColor() const { return m_color; }
        const SP_FLOAT getDepth() const { return m_depth; }

    private:
        vector2i m_position;
        Color m_color;
        SP_FLOAT m_depth;
    };

    typedef std::forward_list<sp::Pixel> PixelList;
}

#endif