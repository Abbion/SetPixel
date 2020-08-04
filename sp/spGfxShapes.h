#ifndef _SP_GFX_SHPAES_
#define _SP_GFX_SHAPES_
#include "coreDefines.h"
#include "spmath.h"
#include "pixel.h"

namespace sp{    
    sp::BitMap Rectangle(sp::vector2f pos, sp::vector2f size);
    sp::BitMap Circle(sp::vector2f pos, SP_FLOAT radius);
};

#endif