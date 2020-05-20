#include "windowBase.h"

//-----------------------------------------------------
void sp::WindowBase::getSize(int *width, int *height) const
{
    *width = m_width;
    *height = m_height;
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::WindowBase::getPosition(int *x_pos, int *y_pos) const
{
    *x_pos = m_x_pos;
    *y_pos = m_y_pos;
}
//-----------------------------------------------------