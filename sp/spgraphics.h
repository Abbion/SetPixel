#ifndef SP_GRAPHICS_H_
#define SP_GRAPHICS_H_
#include "spmath.h"
#include "pixel.h"


namespace sp
{
	void getDrawableAreaForLine(int* x, int* y, const vector2f& start, const vector2f& end);

	sp::BitMap lineLI(vector2f start, vector2f end); //Linear interpolation line drawing. My idea :)
	sp::BitMap line(vector2f start, vector2f end); //Bresenham's line algorithm 
	
	/*
	drawable triangle(float *points);
	drawable fill(drawable& object, float *points, int count);
	*/
	
	
}

#endif // !SP_GRAPHICS_H_
