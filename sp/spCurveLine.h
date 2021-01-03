#ifndef _SP_CURVE_LINE_H_
#define _SP_CURVE_LINE_H_
#include "spMath.h"
#include "spBitMap.h"
#include "spCoreDefined.h"

namespace sp
{    
	//Set of functions to generate curved lines.
	sp::BitMap QuadraticBezier(const sp::vector2f& start, const sp::vector2f& end, const sp::vector2f& control, int precision = 16, bool showControlPoints = false);
	sp::BitMap CubicBezier(const sp::vector2f& start, const sp::vector2f& end, const sp::vector2f& control_1, const sp::vector2f& control_2, int precision = 16, bool showControlPoints = false);

	sp::BitMap Spline(sp::vector2f* points, int count, bool loop = false);
	static sp::vector2i getPointOnSpline(const std::vector<sp::vector2i>& points, SP_FLOAT t);
}

#endif 