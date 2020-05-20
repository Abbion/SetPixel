#include "spmath.h"
#include <cmath>
#include <iostream>

int sp::coordConverter::m_renderWidth = 0;
int sp::coordConverter::m_renderHeight = 0;

sp::vector2f sp::subtractVec2f(const vector2f& vec_1, const vector2f& vec_2)
{
    return vector2f(vec_1.x - vec_2.x, vec_1.y - vec_2.y);
}

sp::vector2i sp::subtractVec2i(const vector2i& vec_1, const vector2i& vec_2)
{
    return vector2i(vec_1.x - vec_2.x, vec_1.y - vec_2.y);
}

void sp::scaleVec2(vector2f& vec_1, float scale)
{
    vec_1.x *= scale;
    vec_1.y *= scale;
}

void sp::scaleVec2(vector2f& vec_1, float scale_x, float scale_y)
{
    vec_1.x *= scale_x;
    vec_1.y *= scale_y;
}

sp::vector2f sp::coordConverter::normalToView(const vector2f& normal)
{
    vector2f screenCoords((m_renderWidth / 2.0f) * (normal.x + 1), (m_renderHeight / 2.0f) * (1 - normal.y));
    return screenCoords;
}

void sp::changeValues(float* val_1, float* val_2)
{
    float temp = *val_1;
    *val_1 = *val_2;
    *val_2 = temp;
}

float sp::lengthVec2(const  vector2f& vec_1)
{
    return std::sqrt(vec_1.x * vec_1.x + vec_1.y * vec_1.y);
}

float sp::distanceVec2(const vector2f& vec_1, const vector2f& vec_2)
{
    vector2f diff = subtractVec2f(vec_1, vec_2);
    return lengthVec2(diff);
}

float sp::getLineSlope(const vector2f& vec_1, const vector2f& vec_2) 
{
    float denominator = (vec_1.x - vec_2.x);
    if(denominator == 0)
        return 0;

    return (vec_1.y - vec_2.y) / (vec_1.x - vec_2.x);
}