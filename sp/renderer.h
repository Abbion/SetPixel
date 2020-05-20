#ifndef _SP_RENDERER_
#define _SP_RENDERER_
#include <cstdlib>

#if unix
#include <X11/Xlib.h>
#elif _WIN32
#include <windows.h>
#include <gdiplus.h>
#include "pixel.h"
#endif

#include "rendererBase.h"
#include "time.h"

//Renderer implementation.
namespace sp
{

//==========LINUX IMPLEMENTATION==========
#if unix 
class Renderer : public RendererBase
{
public:
    Renderer() {}
    ~Renderer() { delete[] m_charMap; }
    virtual void setClearColor(Color& col);

    virtual void clear();
    virtual void draw(const Pixel& drawablePixel);
    virtual void drawSet(Pixel* drawablePixelSet, int pixCount);
    virtual void display();

protected:
    bool initRenderer(Display* dis, Window* win);       //Initializes the renderer.
    void setRenderSpaceSize(int width, int height);     //Sets the render space dimentions.

private:
    void calculateFps();
    void displayFps();      //Displays fps

private:
    Display* ptr_display = nullptr;
    Window* ptr_window = nullptr;

    XImage* m_imageMap = nullptr;
    char* m_charMap = nullptr;
    
    time m_timeStart;
    time m_timeStop;
};
//-----------------------------------------------------



//==========WINDOWS IMPLEMENTATION==========
#elif _WIN32
class Renderer : public RendererBase
{
public:
    Renderer();
    ~Renderer();
    virtual void setClearColor(Color& col);

    virtual void clear();
    virtual void draw(const Pixel& drawablePixel);
    virtual void drawSet(Pixel* drawablePixelSet, int pixCount);
    virtual void draw(const BitMap& bitMap);

    virtual void display();

    int getFps() { return m_fps; }

protected:
    bool initRenderer(HWND* win);
    void setRenderSpaceSize(int width, int height);

private:
    void calculateFps();
    void displayFps(Gdiplus::Graphics& graphics);      //Displays fps

private:
    HWND* ptr_window;
    HDC m_windowContext;
    HDC m_windowContextBACK;
    bool changeBuffer;


    Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_gdiplusToken;

    BYTE* m_pixelMap = nullptr;
    Gdiplus::Bitmap* m_bitmap;
    //Gdiplus::Bitmap* m_backBitmap;
    Gdiplus::Graphics* m_backRenderer;
    unsigned int m_stride;
    unsigned int m_padding;
    unsigned int m_horizontalScanLine;
    
    time m_timeStart;
    time m_timeStop;
};
#endif
//-----------------------------------------------------
}
#endif
