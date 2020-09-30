#ifndef _SP_GFX_LINE_H_
#define _SP_GFX_LINE_H_
#include "spmath.h"
#include "spPixel.h"
#include "spCoreDefined.h"
#include <vector>

namespace sp
{
	sp::BitMap lineLI(vector2f start, vector2f end); //Linear interpolation line drawing.
	sp::BitMap line(vector2f start, vector2f end);
	sp::BitMap line(vector2i start, vector2i end);
	
}

#endif