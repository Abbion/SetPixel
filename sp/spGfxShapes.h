#ifndef _SP_GFX_SHPAES_
#define _SP_GFX_SHAPES_
#include "coreDefines.h"
#include "spmath.h"
#include "pixel.h"

namespace sp{    
    sp::BitMap Triangle(sp::vector2f p1, sp::vector2f p2, sp::vector2f p3);
    sp::BitMap Rectangle(sp::vector2f pos, sp::vector2f size);
    sp::BitMap Circle(sp::vector2f pos, SP_FLOAT radius, bool scaleX = false);
    sp::BitMap Elipse(sp::vector2f pos, SP_FLOAT radiusX, SP_FLOAT radiusY);
    
    static inline void PlotPointToBitmap(const sp::vector2i& plot, sp::BitMap& bm);
};

#endif