#ifndef SP_GRAPHICS_H_
#define SP_GRAPHICS_H_
#include "spmath.h"
#include "pixel.h"
#include "coreDefines.h"

namespace sp
{
	void getDrawableAreaForLine(int* x, int* y, const vector2f& start, const vector2f& end);	
	/*
	drawable triangle(float *points);
	drawable fill(drawable& object, float *points, int count);
	*/
	
	
}

#endif // !SP_GRAPHICS_H_
