#include "spmath.h"
#include <cmath>
#include <iostream>
#include <limits>

int sp::coordConverter::m_renderWidth = 0;
int sp::coordConverter::m_renderHeight = 0;
SP_FLOAT sp::coordConverter::m_invAspectRatio = 0.0;


sp::vector2f sp::coordConverter::normalToViewPosF(const vector2f& normal)
{
    vector2f ViewCoordsPos((m_renderWidth / 2.0f) * (normal.x + 1), (m_renderHeight / 2.0f) * (1 - normal.y));
    return ViewCoordsPos;
}

sp::vector2i sp::coordConverter::normalToViewPosI(const vector2f& normal)
{
    vector2i ViewCoordsPos((m_renderWidth / 2.0f) * (normal.x + 1), (m_renderHeight / 2.0f) * (1 - normal.y));
    return ViewCoordsPos;
}

sp::vector2i sp::coordConverter::nromalToViewSizeI(const vector2f& normal)
{
    vector2i ViewCoordsSize(normal.x * m_renderWidth / 2, normal.y * m_renderHeight / 2);
    return ViewCoordsSize;
}

bool sp::coordConverter::pointInView(const vector2f& point)
{
    if(point.x < -1.0 || point.x > 1.0 || point.y < -1.0 || point.y > 1.0)
        return false;
    return true;
}