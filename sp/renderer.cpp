#include "renderer.h"
#include "spmath.h"
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#if unix
#include <unistd.h>
#include <X11/Xutil.h>
#elif _WIN32
#include <clusapi.h>
#endif


//==========LINUX IMPLEMENTATION==========
#if unix
//-----------------------------------------------------
void sp::Renderer::setClearColor(Color& col)
{
    m_clearColor = col;

    XSetWindowBackground(ptr_display, *ptr_window, m_clearColor.getHexRGB());
    XClearWindow(ptr_display, *ptr_window);
    XFlush(ptr_display);
}
//-----------------------------------------------------



//-----------------------------------------------------
bool sp::Renderer::initRenderer(Display* dis, Window* win)
{
    if(ptr_display != nullptr || ptr_window != nullptr)
    {
        fprintf(stderr, "sp::renderer::initRenderer() Faild to initiate the renderer.\n");
        return false;
    }
    
    ptr_display = dis;
    ptr_window = win;
    return true;
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Renderer::setRenderSpaceSize(int width, int height)
{
    m_windowSpaceWidth = width;
    m_windowSpaceHeight = height;
    coordConverter::m_renderWidth = m_windowSpaceWidth / m_pixelSize;
    coordConverter::m_renderHeight = m_windowSpaceHeight / m_pixelSize;

    if(m_charMap)
        delete[] m_charMap;
    
    m_charMap = new char[m_windowSpaceWidth*m_windowSpaceHeight*4];
    int screen_num = DefaultScreen(ptr_display);
	Visual *visual = DefaultVisual(ptr_display, screen_num);
    m_imageMap = XCreateImage(ptr_display, visual ,DefaultDepth(ptr_display, screen_num), ZPixmap, 0, m_charMap, width, height, 32, 0);
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Renderer::clear()
{
    for (int i = 0; i < m_windowSpaceHeight; i++)
    {
        for (int j = 0; j < m_windowSpaceWidth; j++)
        {
            XPutPixel(m_imageMap,j,i, m_clearColor.getHexRGB());
        }   
    }
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Renderer::draw(const Pixel& drawablePixel)
{
    for (int i = 0; i < m_pixelSize; i++)
    {
        for (int j = 0; j < m_pixelSize; j++)
        {
            int Xpos = (drawablePixel.getPosition().x * m_pixelSize) + j;
            int Ypos = (drawablePixel.getPosition().y * m_pixelSize) + i;
            if(pixelInRenderSpace(Xpos, Ypos))
            {
                XPutPixel(m_imageMap, Xpos, Ypos, drawablePixel.getColor().getHexRGB());
            }
        }    
    }
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Renderer::drawSet(Pixel* drawablePixelSet, int pixCount)
{
    for (int k = 0; k < pixCount; k++)
    {
        for (int i = 0; i < m_pixelSize; i++)
        {
            for (int j = 0; j < m_pixelSize; j++)
            {
                int Xpos = (drawablePixelSet[k].getPosition().x * m_pixelSize) + j;
                int Ypos = (drawablePixelSet[k].getPosition().y * m_pixelSize) + i;
                if(pixelInRenderSpace(Xpos, Ypos))
                {
                    XPutPixel(m_imageMap, Xpos, Ypos, drawablePixelSet[k].getColor().getHexRGB());
                }
            }    
        }
    }
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Renderer::display()
{
    int screen_num = DefaultScreen(ptr_display);

    if(m_showFps)
    {
        displayFps();
        calculateFps();
    }
    XPutImage(ptr_display, *ptr_window, DefaultGC(ptr_display,screen_num), m_imageMap, 0, 0, 0, 0, m_windowSpaceWidth, m_windowSpaceHeight);
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Renderer::calculateFps()
{
    m_timeStop = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(m_timeStop - m_timeStart);
    int miliseconds = diff.count();

    if(miliseconds != 0)
        m_fps = 1000.0f / diff.count();
    else
        m_fps = 1000.0f;
    
    m_timeStart = std::chrono::high_resolution_clock::now();
}
//-----------------------------------------------------



//-----------------------------------------------------
//The fps value may flicker due to the way the X11 implements drawing (event based).
void sp::Renderer::displayFps()
{
    XFontStruct *font;
    Color fontColor(255, 0, 0);

    font = XLoadQueryFont(ptr_display,"10x20");
    
    XGCValues gc_values;
    gc_values.foreground = fontColor.getHexRGB();
    gc_values.font = font->fid;
    GC gc_context = XCreateGC(ptr_display , *ptr_window, GCForeground + GCFont, &gc_values);

    std::ostringstream os;
    os << "FPS: " << m_fps;
    XDrawImageString(ptr_display, *ptr_window, gc_context, 0 , 16, os.str().c_str(), os.str().length());
}
//-----------------------------------------------------
#endif



//==========WINDOWS IMPLEMENTATION==========
#if _WIN32
//-----------------------------------------------------
sp::Renderer::Renderer()
{
    Gdiplus::GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, nullptr);
}
//-----------------------------------------------------



//-----------------------------------------------------
sp::Renderer::~Renderer()
{
    delete m_bitmap;
    delete[] m_pixelMap;
    Gdiplus::GdiplusShutdown(m_gdiplusToken);
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Renderer::setClearColor(Color& col)
{
    m_clearColor = col;
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Renderer::clear()
{
    m_windowContext = GetDC(*ptr_window);
    m_windowContextBACK = CreateCompatibleDC(m_windowContext);

    for(int i = 0; i < m_windowSpaceHeight; i++)
    {
        int y_pos = i * m_horizontalScanLine;
        for (int j = 0; j < m_windowSpaceWidth; j++)
        {
            int pixelLine = y_pos + (j * 3);
            m_pixelMap[pixelLine] = m_clearColor.blue;
            m_pixelMap[pixelLine + 1] = m_clearColor.green;
            m_pixelMap[pixelLine + 2] = m_clearColor.red;
        }
    }
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Renderer::draw(const Pixel& drawablePixel)
{
    /*
    sp::Color color = drawablePixel.getColor();

    for (int i = 0; i < m_pixelSize; i++)
    {
        int Ypos = (drawablePixel.getPosition().y * m_pixelSize) + i;
        unsigned int verticalPixelPosition = (Ypos * m_horizontalScanLine);

        for (int j = 0; j < m_pixelSize; j++)
        {
            int Xpos = (drawablePixel.getPosition().x * m_pixelSize) + j;

            if(pixelInRenderSpace(Xpos, Ypos))
            {
                unsigned int pixelPosition = verticalPixelPosition + (Xpos * 3);

                m_pixelMap[pixelPosition] = color.blue;
                m_pixelMap[pixelPosition + 1] = color.green;
                m_pixelMap[pixelPosition + 2] = color.red;
            }
        }    
    }
    */ 
}
//-----------------------------------------------------



//-----------------------------------------------------

void sp::Renderer::drawSet(Pixel* drawablePixelSet, int pixCount)
{
    /*
    for (int k = 0; k < pixCount; k++)
    {
        for (int i = 0; i < m_pixelSize; i++)
        {
            int Ypos = (drawablePixelSet[k].getPosition().y * m_pixelSize) + i;
            unsigned int verticalPixelPosition = (Ypos * m_horizontalScanLine);

            for (int j = 0; j < m_pixelSize; j++)
            {
                int Xpos = (drawablePixelSet[k].getPosition().x * m_pixelSize) + j;

                if(pixelInRenderSpace(Xpos, Ypos))
                {
                    unsigned int pixelPosition = verticalPixelPosition + (Xpos * 3);

                    sp::Color color = drawablePixelSet[k].getColor();
                    m_pixelMap[pixelPosition] = color.blue;
                    m_pixelMap[pixelPosition + 1] = color.green;
                    m_pixelMap[pixelPosition + 2] = color.red;
                }
            }    
        }
    }
    */
}

//-----------------------------------------------------



//-----------------------------------------------------
void sp::Renderer::draw(const BitMap& bitMap)
{
    int fullSize = bitMap.m_size.x * bitMap.m_size.y;

    int bitPixel = 0;
    for (int p_y = 0; p_y < bitMap.m_size.y; p_y++)
    {
        for (int p_x = 0; p_x < bitMap.m_size.x; p_x++)
        {
            if(bitMap.m_pixelMap[bitPixel])
            {
                for (int i = 0; i < m_pixelSize; i++)
                {
                    int Ypos = ((bitMap.m_startPos.y + p_y) * m_pixelSize) + i;
                    
                    for (int j = 0; j < m_pixelSize; j++)
                    {
                        int Xpos = ((bitMap.m_startPos.x + p_x) * m_pixelSize) + j;
                        unsigned int verticalPixelPosition = (Ypos * m_horizontalScanLine);

                        if(pixelInRenderSpace(Xpos, Ypos))
                        {
                            unsigned int pixelPosition = verticalPixelPosition + (Xpos * 3);
                            m_pixelMap[pixelPosition] = m_defaultDraw.blue;
                            m_pixelMap[pixelPosition + 1] = m_defaultDraw.green;
                            m_pixelMap[pixelPosition + 2] = m_defaultDraw.red;
                        }
                    }    
                }
            }

            //X_pixel loop
            bitPixel++;
        }
    }
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Renderer::display()
{
    Gdiplus::Graphics graphics(m_windowContext);
    //m_backRenderer->DrawImage(m_bitmap, 0, 0);      //Wierd memeory usage picks 🤔
    if(m_showFps)
    {
        displayFps(graphics);
        calculateFps();
    }

    //graphics.DrawImage(m_backBitmap, 0, 0);
    graphics.DrawImage(m_bitmap, 0, 0);

    ReleaseDC(*ptr_window, m_windowContext);
    DeleteDC(m_windowContextBACK);
}
//-----------------------------------------------------



//-----------------------------------------------------
bool sp::Renderer::initRenderer(HWND* win)
{
    ptr_window = win;
    return true;
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Renderer::setRenderSpaceSize(int width, int height)
{
    m_windowSpaceWidth = width;
    m_windowSpaceHeight = height;
    coordConverter::m_renderWidth = m_windowSpaceWidth / m_pixelSize;
    coordConverter::m_renderHeight = m_windowSpaceHeight / m_pixelSize; 

     if(m_pixelMap)
     {
        delete[] m_pixelMap;
        delete m_bitmap;
        //delete m_backBitmap;
        delete m_backRenderer;
     }
    
    m_stride =  ALIGN_CLUSPROP(3 * m_windowSpaceWidth);
    m_padding = m_stride - (m_windowSpaceWidth * 3);
    m_horizontalScanLine = (m_windowSpaceWidth * 3) + m_padding;

    m_pixelMap = new BYTE[m_stride * m_windowSpaceHeight];
    m_bitmap = new Gdiplus::Bitmap(m_windowSpaceWidth, m_windowSpaceHeight, m_stride, PixelFormat24bppRGB, m_pixelMap);

    //m_backBitmap = new Gdiplus::Bitmap(m_windowSpaceWidth, m_windowSpaceHeight);
    //m_backRenderer = Gdiplus::Graphics::FromImage(m_backBitmap);    //It's a fucking secred memory allocation 🤬
    m_backRenderer = Gdiplus::Graphics::FromImage(m_bitmap);
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Renderer::calculateFps()
{
    m_timeStop = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(m_timeStop - m_timeStart);
    int miliseconds = diff.count();

    if(miliseconds != 0)
        m_fps = 1000.0f / diff.count();
    else
        m_fps = 1000.0f;
    
    m_timeStart = std::chrono::high_resolution_clock::now();
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Renderer::displayFps(Gdiplus::Graphics& graphics)
{
    int fontSize = 16;
    Gdiplus::FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, fontSize, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
    Gdiplus::SolidBrush fontColor(Gdiplus::Color(255, 0, 0));
    Gdiplus::SolidBrush background(Gdiplus::Color(0, 0, 0));

    std::ostringstream os;
    os << "FPS: " << m_fps;

    int size = os.str().size() + 1;
    size_t len;
    WCHAR* string1 = new WCHAR[size];
    mbstowcs_s(&len, string1, size, os.str().c_str(), size - 1);

    m_backRenderer->FillRectangle(&background, 0, 0, (fontSize / 2) * (size), fontSize + 8);
    m_backRenderer->DrawString(string1, -1, &font, Gdiplus::PointF(1.0f, 4.0f), &fontColor);
}
//-----------------------------------------------------
#endif