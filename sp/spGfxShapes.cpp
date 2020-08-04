#include "spGfxShapes.h"
#include "spGfxLine.h"
#include <iostream>

sp::BitMap sp::Rectangle(sp::vector2f pos, sp::vector2f size)
{
    sp::BitMap rectangleBitMap;

    sp::vector2f c2 = sp::vector2f(pos.x + size.x, pos.y);
    sp::vector2f c3 = vector2f(pos.x + size.x, pos.y - size.y);
    sp::vector2f c4 = sp::vector2f(pos.x, pos.y - size.y);
    rectangleBitMap = line(pos, c2);
    
    sp::BitMap rect[3] = {  line(c2, c3), 
                            line(c3, c4),
                            line(c4, pos)
                            };
    
    rectangleBitMap.marge(rect, 3);

    for (int i = 0; i < 3; i++)
        rect[i].clear();

    return rectangleBitMap;
}

sp::BitMap sp::Circle(sp::vector2f pos, SP_FLOAT radius)
{
    sp::vector2i Normal_pos = sp::coordConverter::normalToViewI(pos);
    vector2i Normal_size = sp:: coordConverter::normalToViewI(sp::vector2f(radius, radius));
    int Normal_radius = Normal_size.x;
    int Normal_radius_pow = Normal_radius * Normal_radius; 
    Normal_size.scale(2.0);

    sp::BitMap bm(Normal_pos, Normal_size);

    for (int i = Normal_radius; i >= 0; i--)
    {   
        int y_1 = Normal_radius_pow - (i * i);
        y_1 = std::sqrt(y_1);
        std::cout << "X: " << i << " Y: " << y_1 << std::endl;

        sp::vector2i PixelPos(i, y_1);
        int bmPos = PixelPos.y * Normal_radius + PixelPos.x;
        bm.m_pixelPosMap[bmPos] = 1;
    }

    return bm;
}