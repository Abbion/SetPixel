#ifndef _SP_BITMAP_H_
#define _SP_BITMAP_H_
#include <vector>
#include "spMath.h"


namespace sp
{
    //Creates a small portion of the screen rendering space to render to.
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
        void margeToBitMap(BitMap& target, BitMap& bm);

        void fill();
        void fillLine(int start, int end);

    public:
        bool* m_bitMapData;
        vector2i m_startPos;
		vector2i m_size;
	};
 }
 #endif //BITMAP