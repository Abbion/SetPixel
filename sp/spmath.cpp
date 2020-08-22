#include "spmath.h"
#include <cmath>
#include <iostream>

int sp::coordConverter::m_renderWidth = 0;
int sp::coordConverter::m_renderHeight = 0;


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
