#include "spgraphics.h"
#include <iostream>
#include <algorithm>

//vc_s -> view coordinates for start
//vc_e -> view coordinates for end

void sp::getDrawableAreaForLine(int* x, int* y, const vector2f& start, const vector2f& end)
{
	*x = std::abs(start.x - end.x);
	*y = std::abs(start.y - end.y);
}
