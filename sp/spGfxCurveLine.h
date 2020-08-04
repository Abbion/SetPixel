#ifndef SP_GFX_CURVE_LINE_H_
#define SP_GFX_CURVE_LINE_H_
#include "spmath.h"
#include "pixel.h"
#include "coreDefines.h"

namespace sp
{    
	class QuadraticBezier
	{
	public:
		QuadraticBezier(sp::vector2f start, sp::vector2f end, sp::vector2f control, int precision = 16);
		~QuadraticBezier();
		void drawControlPoints();
		const sp::BitMap& getDrawable();

	private:
		void calculateCurve();
		void calculateRect();

	private:
        sp::vector2i m_p1, m_p2, m_control;
        sp::BitMap m_QBcurve;
		unsigned int m_precision;
		bool m_drawControl = false;
	};

	class CubicBezier
	{
	public:
		CubicBezier(sp::vector2f start, sp::vector2f end, sp::vector2f control_1, sp::vector2f control_2, int precision = 16);
		~CubicBezier();

		void drawControlPoints();
		const sp::BitMap& getDrawable();
	
	private:
		void calculateCurve();
		void calculateRect();

	private:
        sp::vector2i m_p1, m_p2, m_control_1, m_control_2;
        sp::BitMap m_CBcurve;
		unsigned int m_precision;
		bool m_drawControl = false;
	};

	sp::BitMap QuadraticBezier2(sp::vector2f start, sp::vector2f end, sp::vector2f control, int precision = 16);
	static sp::BitMap QBCalculateRect(const sp::vector2f& p1, const sp::vector2f& p2, const sp::vector2f& control);
	static void QBcalculateCurve(sp::vector2f& p1, sp::vector2f& p2, sp::vector2f& control, sp::BitMap& bm);
}

#endif 