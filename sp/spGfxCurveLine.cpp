#include "spGfxCurveLine.h"
#include "spGfxLine.h"
#include <cmath>

sp::QuadraticBezier::QuadraticBezier(sp::vector2f start, sp::vector2f end, sp::vector2f control, int precision) :
    m_p1(sp::coordConverter::normalToViewI(start)), m_p2(sp::coordConverter::normalToViewI(end)), 
    m_control(sp::coordConverter::normalToViewI(control)), m_precision(precision)
{
    calculateRect();
    calculateCurve();
}

sp::QuadraticBezier::~QuadraticBezier()
{
    m_QBcurve.clear();
}

const sp::BitMap& sp::QuadraticBezier::getDrawable()
{
    return m_QBcurve;
}

void sp::QuadraticBezier::calculateCurve()
{
    SP_FLOAT maxLength = m_p1.distance(m_control);
    maxLength += m_control.distance(m_p2);
    int lines = maxLength / m_precision;
    SP_FLOAT step = 1.0 / lines;
    sp::vector2i lastPoint = m_p1;

    for (SP_FLOAT i = 0.0; i <= 1.0; i += step)
    {
        SP_FLOAT interpolate = (1 - i);
        SP_FLOAT poly1 = interpolate * interpolate;
        SP_FLOAT poly2 = 2 * i * interpolate;
        SP_FLOAT poly3 = i * i;

        sp::vector2i newPoint((m_p1.x * poly1) + (m_control.x * poly2) + (m_p2.x * poly3), (m_p1.y * poly1) + (m_control.y * poly2) + (m_p2.y * poly3));
        sp::BitMap newLine = line(lastPoint, newPoint);
        lastPoint = newPoint;
        m_QBcurve.marge(newLine);
        newLine.clear();
    }

    if(lastPoint != m_p2)
    {
        sp::BitMap newLine = line(lastPoint, m_p2);
        m_QBcurve.marge(newLine);
        newLine.clear();
    }

}

void sp::QuadraticBezier::calculateRect()
{
    int x_min = sp::minOf(m_p1.x, m_p2.x, m_control.x);
    int x_max = sp::maxOf(m_p1.x, m_p2.x, m_control.x) - x_min;
    int y_min = sp::minOf(m_p1.y, m_p2.y, m_control.y);
    int y_max = sp::maxOf(m_p1.y, m_p2.y, m_control.y) - y_min;
    m_QBcurve = BitMap(sp::vector2i(x_min, y_min), sp::vector2i(x_max, y_max));
}

void sp::QuadraticBezier::drawControlPoints()
{
    sp::BitMap cp1(m_control, sp::vector2i(1, 1));
    cp1.m_pixelPosMap[0] = 1;
    m_QBcurve.marge(cp1);
    cp1.clear();
}



sp::CubicBezier::CubicBezier(sp::vector2f start, sp::vector2f end, sp::vector2f control_1, sp::vector2f control_2, int precision) :
    m_p1(sp::coordConverter::normalToViewI(start)), m_p2(sp::coordConverter::normalToViewI(end)),
    m_control_1(sp::coordConverter::normalToViewI(control_1)), m_control_2(sp::coordConverter::normalToViewI(control_2)),
    m_precision(precision)
{
    calculateRect();
    calculateCurve();
}

sp::CubicBezier::~CubicBezier()
{
    m_CBcurve.clear();
}

const sp::BitMap&  sp::CubicBezier::getDrawable()
{
    return m_CBcurve;
}

void sp::CubicBezier::calculateCurve()
{
    SP_FLOAT maxLength = m_p1.distance(m_control_1);
    maxLength += m_control_1.distance(m_control_2);
    maxLength += m_control_2.distance(m_p2);
    int lines = maxLength / m_precision;
    SP_FLOAT step = 1.0 / lines;
    sp::vector2i lastPoint = m_p1;

    for (SP_FLOAT i = 0.0; i <= 1.0; i += step)
    {
        SP_FLOAT interpolate = (1 - i);
        SP_FLOAT poly1 = std::pow(interpolate, 3);
        SP_FLOAT poly2 = 3 * i * interpolate * interpolate;
        SP_FLOAT poly3 = 3 * i * i * interpolate;
        SP_FLOAT poly4 = std::pow(i,3);

        sp::vector2i newPoint((m_p1.x * poly1) + (m_control_1.x * poly2) + (m_control_2.x * poly3) + (m_p2.x * poly4),
                              (m_p1.y * poly1) + (m_control_1.y * poly2) + (m_control_2.y * poly3) + (m_p2.y * poly4));
        sp::BitMap newLine = line(lastPoint, newPoint);
        lastPoint = newPoint;
        m_CBcurve.marge(newLine);
        newLine.clear();
    }

    if(lastPoint != m_p2)
    {
        sp::BitMap newLine = line(lastPoint, m_p2);
        m_CBcurve.marge(newLine);
        newLine.clear();
    }

}

void sp::CubicBezier::calculateRect()
{
    int x_min = sp::minOf(m_p1.x, m_p2.x, m_control_1.x, m_control_2.y);
    int x_max = sp::maxOf(m_p1.x, m_p2.x, m_control_1.x, m_control_2.y) - x_min;
    int y_min = sp::minOf(m_p1.y, m_p2.y, m_control_1.y, m_control_2.y);
    int y_max = sp::maxOf(m_p1.y, m_p2.y, m_control_1.y, m_control_2.y) - y_min;
    m_CBcurve = BitMap(sp::vector2i(x_min, y_min), sp::vector2i(x_max, y_max));
}

void sp::CubicBezier::drawControlPoints()
{
    sp::BitMap cp1(m_control_1, sp::vector2i(1, 1));
    cp1.m_pixelPosMap[0] = 1;
    sp::BitMap cp2(m_control_2, sp::vector2i(1, 1));
    cp2.m_pixelPosMap[0] = 1;
    m_CBcurve.marge(cp1);
    m_CBcurve.marge(cp2);
    cp1.clear();
    cp2.clear();
}
