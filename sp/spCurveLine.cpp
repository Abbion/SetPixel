#include "spCurveLine.h"
#include "spLine.h"
#include <algorithm>

//Bezier-----------------------------------------------
sp::BitMap sp::QuadraticBezier(const sp::vector2f& start, const sp::vector2f& end, const sp::vector2f& control, int precision, bool showControlPoints)
{
    //Convert to view-----------
    sp::vector2i p1 = sp::coordConverter::normalToViewPosI(start);
    sp::vector2i p2 = sp::coordConverter::normalToViewPosI(end);
    sp::vector2i ctrl = sp::coordConverter::normalToViewPosI(control);
    sp::BitMap QBcurve;
    //--------------------------

    //Calculate the step--------
    SP_FLOAT maxLength = sp::getDistance(p1, ctrl);
    maxLength += sp::getDistance(ctrl, p2);

    int lines = maxLength / precision;
    SP_FLOAT step = 1.0 / lines;
    //--------------------------

    //Draw Bezier---------------
    sp::vector2i lastPoint = p1;

    for (SP_FLOAT i = 0.0; i <= 1.0; i += step)
    {
        SP_FLOAT interpolate = (1 - i);
        SP_FLOAT poly1 = interpolate * interpolate;
        SP_FLOAT poly2 = 2 * i * interpolate;
        SP_FLOAT poly3 = i * i;

        sp::vector2i newPoint((p1.x * poly1) + (ctrl.x * poly2) + (p2.x * poly3), (p1.y * poly1) + (ctrl.y * poly2) + (p2.y * poly3));
        sp::BitMap newLine = sp::line(lastPoint, newPoint);
        lastPoint = newPoint;
        QBcurve.marge(newLine);
    }
    //--------------------------

    //If the last point wasn't drawn
    if(lastPoint != p2)
    {
        sp::BitMap newLine = sp::line(lastPoint, p2);
        QBcurve.marge(newLine);
    }
    //--------------------------

    //Draw control points-------
    if(showControlPoints)
    {
        sp::BitMap cp1(ctrl, sp::vector2i(1, 1));
        cp1.m_bitMapData[0] = 1;
        QBcurve.marge(cp1);
    }
    //--------------------------

    return QBcurve;
}


sp::BitMap sp::CubicBezier(const sp::vector2f& start, const sp::vector2f& end, const sp::vector2f& control_1, const sp::vector2f& control_2, int precision, bool showControlPoints)
{
    //Convert to view-----------
    sp::vector2i p1 = sp::coordConverter::normalToViewPosI(start);
    sp::vector2i p2 = sp::coordConverter::normalToViewPosI(end);
    sp::vector2i ctrl1 = sp::coordConverter::normalToViewPosI(control_1);
    sp::vector2i ctrl2 = sp::coordConverter::normalToViewPosI(control_2);
    sp::BitMap CBcurve;
    //--------------------------
    
    //Calculate the step--------
    SP_FLOAT maxLength = sp::getDistance(p1, ctrl1);
    maxLength += sp::getDistance(ctrl1, ctrl2);
    maxLength += sp::getDistance(ctrl2, p2);

    int lines = maxLength / precision;
    SP_FLOAT step = 1.0 / lines;
    //--------------------------

    //Draw Bezier---------------
    sp::vector2i lastPoint = p1;

    for (SP_FLOAT i = 0.0; i <= 1.0; i += step)
    {
        SP_FLOAT interpolate = (1 - i);
        SP_FLOAT poly1 = std::pow(interpolate, 3);
        SP_FLOAT poly2 = 3 * i * interpolate * interpolate;
        SP_FLOAT poly3 = 3 * i * i * interpolate;
        SP_FLOAT poly4 = std::pow(i,3);

        sp::vector2i newPoint((p1.x * poly1) + (ctrl1.x * poly2) + (ctrl2.x * poly3) + (p2.x * poly4),
                              (p1.y * poly1) + (ctrl1.y * poly2) + (ctrl2.y * poly3) + (p2.y * poly4));
        sp::BitMap newLine = sp::line(lastPoint, newPoint);
        lastPoint = newPoint;
        CBcurve.marge(newLine);
    }
    //--------------------------

    //Draw control points-------
    if(lastPoint != p2)
    {
        sp::BitMap newLine = sp::line(lastPoint, p2);
        CBcurve.marge(newLine);
    }
    //--------------------------

    //Draw control points-------
    if(showControlPoints)
    {
        sp::BitMap cp1(ctrl1, sp::vector2i(1, 1));
        sp::BitMap cp2(ctrl2, sp::vector2i(1, 1));
        cp1.m_bitMapData[0] = 1;
        cp2.m_bitMapData[0] = 1;
        CBcurve.marge(cp1);
        CBcurve.marge(cp2);
    }
    //--------------------------

    return CBcurve;
}
//-----------------------------------------------------



//Splines----------------------------------------------
sp::BitMap sp::Spline(sp::vector2f* points, int count, bool loop)
{
    //Check if we can draw the spline
    if((!loop && count < 4) || (loop && count < 2))
        return sp::BitMap(sp::vector2i(0, 0), sp::vector2i(0, 0));
    //--------------------------
    std::vector<sp::vector2i> viewPoints;
    sp::BitMap spline;
    
    //Convert to view coordinates and loop if it is set to true
    if(loop)
        viewPoints.push_back(sp::coordConverter::normalToViewPosI(points[count - 2]));

    for (int i = 0; i < count; i++)
        viewPoints.push_back(sp::coordConverter::normalToViewPosI(points[i]));

    if(loop)
    {
        viewPoints.push_back(sp::coordConverter::normalToViewPosI(points[0]));
        viewPoints.push_back(sp::coordConverter::normalToViewPosI(points[1]));
    }
    //--------------------------
    

    //Creates the spline with lines
    sp::vector2i lastPoint = viewPoints.at(1);
    for(SP_FLOAT i = 0.0f; i < viewPoints.size() - 3; i += 0.1)
    {
        sp::vector2i newPoint = getPointOnSpline(viewPoints, i);
        sp::BitMap lineSeg = line(lastPoint, newPoint);
        spline.marge(lineSeg);
        lastPoint = newPoint;
    }
    sp::BitMap lineSeg = line(lastPoint, viewPoints.at(viewPoints.size() - 2));
    spline.marge(lineSeg);
    //--------------------------

    return spline;
}

static sp::vector2i sp::getPointOnSpline(const std::vector<sp::vector2i>& points, SP_FLOAT t)
{
    int p1 = (int)t + 1;
    int p2 = p1 + 1;
    int p3 = p1 + 2;
    int p0 = p1 - 1;

    //Convert to value between 0 - 1
    t = t -(int)t;
    //--------------------------

    SP_FLOAT t2 = t * t;
    SP_FLOAT t3 = t2 * t;

    SP_FLOAT q1 = -t3 + 2 * t2 - t;
    SP_FLOAT q2 = 3 * t3 - 5 * t2 + 2;
    SP_FLOAT q3 = -3 * t3 + 4 * t2+ t;
    SP_FLOAT q4 = t3 - t2;

    int posX = points.at(p0).x * q1 + points.at(p1).x * q2 + points.at(p2).x * q3 + points.at(p3).x * q4;
    int posY = points.at(p0).y * q1 + points.at(p1).y * q2 + points.at(p2).y * q3 + points.at(p3).y * q4;

    return sp::vector2i(posX / 2, posY / 2);
}
//-----------------------------------------------------