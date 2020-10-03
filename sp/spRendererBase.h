#ifndef _SP_RENDERER_BASE_H_
#define _SP_RENDERER_BASE_H_
#include "spColor.h"
#include "spPixel.h"
#include "spMath.h"

//Base class for os specific renderer classes.
namespace sp
{
class RendererBase
{
public:
    RendererBase();
    virtual ~RendererBase() {}

    virtual void setClearColor(Color& col) = 0;     //To set the background color of the window.
    void setPixelSize(unsigned int size);        

    void showFps(bool show);                        //Determines if the fps value will be rendered on screen.
    int getFps() const;                             //Returns fps value.

    virtual void clear() = 0;                                          //Clears the window with clear color.
    virtual void draw(const Pixel& drawablePixel) = 0;                 //Draws one pixel.
    virtual void drawSet(Pixel* drawablePixelSet, int pixCount) = 0;   //Draws a set of pixels.
    virtual void draw(const BitMap& bitMap) = 0;
    virtual void display() = 0;                                        //Displays everything.

protected:
    virtual void calculateFps() = 0;                                    //Calculates the fps value.
    bool pixelInRenderSpace(int x, int y);                              //Checks is the pixel is in the render space.

protected:
    int m_windowSpaceWidth, m_windowSpaceHeight;
    unsigned int m_pixelSize = 1;

    Color m_clearColor;
    Color m_defaultDraw;

    bool m_showFps = false;
    bool m_resetTitle = false;
    int m_fps = 0;
};
}
#endif