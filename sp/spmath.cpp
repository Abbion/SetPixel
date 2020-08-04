#include "spmath.h"
#include <cmath>
#include <iostream>

int sp::coordConverter::m_renderWidth = 0;
int sp::coordConverter::m_renderHeight = 0;


sp::vector2f sp::coordConverter::normalToViewF(const vector2f& normal)
{
    vector2f screenCoords((m_renderWidth / 2.0f) * (normal.x + 1), (m_renderHeight / 2.0f) * (1 - normal.y));
    return screenCoords;
}

sp::vector2i sp::coordConverter::normalToViewI(const vector2f& normal)
{
    vector2i screenCoords((m_renderWidth / 2.0f) * (normal.x + 1), (m_renderHeight / 2.0f) * (1 - normal.y));
    return screenCoords;
}
