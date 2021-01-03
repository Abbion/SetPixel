#ifndef _SP_LINE_H_
#define _SP_LINE_H_
#include "spMath.h"
#include "spBitMap.h"
#include "spCoreDefined.h"
#include <vector>

namespace sp
{
	//Set of functions to draw lines
	sp::BitMap lineLI(vector2f start, vector2f end); //Linear interpolation line drawing.
	sp::BitMap line(vector2f start, vector2f end);
	sp::BitMap line(vector2i start, vector2i end);
	
}

#endif