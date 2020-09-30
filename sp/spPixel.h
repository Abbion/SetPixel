#ifndef _SP_PIXEL_H_
#define _SP_PIXEL_H_
#include "spColor.h"
#include "spmath.h"
#include <vector>

namespace sp
{   
    //Bitmap: saves pixel position in the image
    class BitMap
	{
    public:
        BitMap();
        BitMap(const vector2i& pos, const vector2i& size);
        BitMap(const BitMap& bm);
        ~BitMap();

        BitMap& operator=(const BitMap& bm);
        void clear();

        void marge(BitMap& bm);
        void marge(BitMap* bm, int obj_count);
        void calculateNewRect(const BitMap& bm, sp::vector2i* pos, sp::vector2i* size);
        void calculateNewRect(const BitMap* bm, int obj_count, sp::vector2i* pos, sp::vector2i* size);
        void margeToBitMap(BitMap& target, BitMap& bm); //Const for bm?

        void fill();
        void fillLine(int start, int end);

    public:
        bool* m_pixelPosMap;
        vector2i m_startPos;
		vector2i m_size;
	};
    //--------------------------



    class Pixel
    {
    public:
        Pixel(int pos_x, int pos_y, const Color& col);
        Pixel(int pos_x, int pos_y);
        Pixel() {};
        ~Pixel() {};

        void setPosition(int pos_x, int pos_y);
        void setColor(const Color& col);


        const vector2i& getPosition() const { return m_position; }
        const Color& getColor() const { return m_color; }

    private:
        vector2i m_position;
        Color m_color;
    };
}

#endif