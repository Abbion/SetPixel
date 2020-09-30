#include "spRendererBase.h"
#include "spmath.h"
#include <stdio.h>

//-----------------------------------------------------
sp::RendererBase::RendererBase()
{
    m_clearColor.red = 33;
    m_clearColor.green = 29;
    m_clearColor.blue = 37;
    
    m_defaultDraw.red = 243;
    m_defaultDraw.green = 243;
    m_defaultDraw.blue = 243;
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::RendererBase::setPixelSize(unsigned int size)
{
    if(size <= 0)
    {
        fprintf(stderr, "sp::renderer::setPixelSize() Pixel size can't be 0 or less.\n");
        m_pixelSize = 1;
    }
    else
        m_pixelSize = size;

    coordConverter::m_renderWidth = m_windowSpaceWidth / m_pixelSize;
    coordConverter::m_renderHeight = m_windowSpaceHeight / m_pixelSize;
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::RendererBase::showFps(bool show)
{
    m_showFps = show;
}
//-----------------------------------------------------



//-----------------------------------------------------
int sp::RendererBase::getFps() const
{
    return m_fps;
}
//-----------------------------------------------------



//-----------------------------------------------------
bool sp::RendererBase::pixelInRenderSpace(int x, int y)
{
    if(x >= 0 && x < m_windowSpaceWidth && y >= 0 && y < m_windowSpaceHeight)
        return true;
    return false;    
}
//-----------------------------------------------------