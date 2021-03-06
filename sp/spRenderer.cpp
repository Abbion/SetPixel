#include "spRenderer.h"
#include "spMath.h"
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <limits>

#if unix
#include <unistd.h>
#include <X11/Xutil.h>
#elif _WIN32
#include <clusapi.h>
#endif


//==========LINUX IMPLEMENTATION==========
#if unix

//-----------------------------------------------------
sp::Renderer::~Renderer() 
{
    delete[] m_charMap; 
    delete[] m_depthMap; 
}
//-----------------------------------------------------


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
    sp::coordConverter::m_invAspectRatio = (SP_FLOAT)sp::coordConverter::m_renderHeight / (SP_FLOAT)sp::coordConverter::m_renderWidth;

    if(m_charMap)
    {
        delete[] m_depthMap;
        delete[] m_charMap;
    }
    
    m_charMap = new char[m_windowSpaceWidth*m_windowSpaceHeight*4];
    m_depthMap = new SP_FLOAT[m_windowSpaceWidth * m_windowSpaceWidth];
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
        int y_posD = i * m_windowSpaceHeight;
        for (int j = 0; j < m_windowSpaceWidth; j++)
        {
            XPutPixel(m_imageMap,j,i, m_clearColor.getHexRGB());
            m_depthMap[y_posD + j] = -999999999.9;
        }   
    }
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
            if(bitMap.m_bitMapData[bitPixel])
            {
                for (int i = 0; i < m_pixelSize; i++)
                {
                    int Ypos = ((bitMap.m_startPos.y + p_y) * m_pixelSize) + i;
                    
                    for (int j = 0; j < m_pixelSize; j++)
                    {
                        int Xpos = ((bitMap.m_startPos.x + p_x) * m_pixelSize) + j;
                        if(pixelInRenderSpace(Xpos, Ypos))
                        {
                            XPutPixel(m_imageMap, Xpos, Ypos, m_defaultDraw.getHexRGB());
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
void sp::Renderer::draw(const sp::PixelList& pixelList)
{
    int limitX = (m_windowSpaceWidth / m_pixelSize) - 1;
    int limitY = (m_windowSpaceHeight / m_pixelSize) - 1;

    for (sp::PixelList::const_iterator itr = pixelList.begin(); itr != pixelList.end(); itr++)
    {
        if (itr->getPosition().x > limitX || itr->getPosition().y > limitY)
            continue;
            
       int Ypos = itr->getPosition().y * m_pixelSize;
       int Xpos = itr->getPosition().x * m_pixelSize;

       int dpos = itr->getPosition().y * m_windowSpaceHeight + itr->getPosition().x;
       if (m_depthMap[dpos] < itr->getDepth())
       {
           m_depthMap[dpos] = itr->getDepth();

           for (int i = 0; i < m_pixelSize; i++)
           {
               for (int j = 0; j < m_pixelSize; j++)
               {
                   XPutPixel(m_imageMap, Xpos + j, Ypos + i, itr->getColor().getHexRGB());
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
        m_resetTitle = true;
    }
    else if(m_resetTitle)
    {
        char* k_str;
        XGetIconName(ptr_display, *ptr_window, &k_str);
        XStoreName(ptr_display, *ptr_window, k_str);
        m_resetTitle = false;
    }
    
    XPutImage(ptr_display, *ptr_window, DefaultGC(ptr_display,screen_num), m_imageMap, 0, 0, 0, 0, m_windowSpaceWidth, m_windowSpaceHeight);
}
//-----------------------------------------------------


//-----------------------------------------------------x
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
    std::ostringstream os;
    char* k_str;
    XGetIconName(ptr_display, *ptr_window, &k_str);
    os << k_str << " FPS: " << m_fps;
    XStoreName(ptr_display, *ptr_window, os.str().c_str());
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
    delete[] m_depthMap;
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
        int y_posD = i * m_windowSpaceHeight;
        for (int j = 0; j < m_windowSpaceWidth; j++)
        {
            int pixelLine = y_pos + (j * 3);
            m_pixelMap[pixelLine] = m_clearColor.blue;
            m_pixelMap[pixelLine + 1] = m_clearColor.green;
            m_pixelMap[pixelLine + 2] = m_clearColor.red;

            m_depthMap[y_posD + j] = -999999999.9;
        }
    }
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
            if(bitMap.m_bitMapData[bitPixel])
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
void sp::Renderer::draw(const sp::PixelList& pixelList)
{
    int limitX = (m_windowSpaceWidth / m_pixelSize) - 1;
    int limitY = (m_windowSpaceHeight / m_pixelSize) - 1;

    for (sp::PixelList::const_iterator itr = pixelList.begin(); itr != pixelList.end(); itr++)
    {
        if (itr->getPosition().x > limitX || itr->getPosition().y > limitY)
            continue;
            
       int Ypos = itr->getPosition().y * m_pixelSize;
       int Xpos = itr->getPosition().x * m_pixelSize;

       int dpos = itr->getPosition().y * m_windowSpaceHeight + itr->getPosition().x;
       if (m_depthMap[dpos] < itr->getDepth())
       {
           m_depthMap[dpos] = itr->getDepth();

           for (int i = 0; i < m_pixelSize; i++)
           {
               int verticalPixelPosition = m_horizontalScanLine * (Ypos + i);
               for (int j = 0; j < m_pixelSize; j++)
               {
                   int pixelPos = verticalPixelPosition + (Xpos + j) * 3;
                   m_pixelMap[pixelPos] = itr->getColor().blue;
                   m_pixelMap[pixelPos + 1] = itr->getColor().green;
                   m_pixelMap[pixelPos + 2] = itr->getColor().red;
               }
           }
       }
        
    }
}
//-----------------------------------------------------


//-----------------------------------------------------
void sp::Renderer::display()
{
    Gdiplus::Graphics graphics(m_windowContext);
    m_backRenderer->DrawImage(m_bitmap, 0, 0, 24, 0);      //Wierd memeory usage picks
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
    sp::coordConverter::m_renderWidth = m_windowSpaceWidth / m_pixelSize;
    sp::coordConverter::m_renderHeight = m_windowSpaceHeight / m_pixelSize; 
    sp::coordConverter::m_invAspectRatio = (SP_FLOAT)sp::coordConverter::m_renderHeight/ (SP_FLOAT)sp::coordConverter::m_renderWidth;

     if(m_pixelMap != nullptr)
     {
        delete[] m_pixelMap;
        delete[] m_depthMap;
        delete m_bitmap;
        //delete m_backBitmap;
        delete m_backRenderer;
     }
    
    m_stride =  ALIGN_CLUSPROP(3 * m_windowSpaceWidth);
    m_padding = m_stride - (m_windowSpaceWidth * 3);
    m_horizontalScanLine = (m_windowSpaceWidth * 3) + m_padding;

    m_pixelMap = new BYTE[m_stride * m_windowSpaceHeight];
    m_depthMap = new SP_FLOAT[m_windowSpaceWidth * m_windowSpaceWidth];
    m_bitmap = new Gdiplus::Bitmap(m_windowSpaceWidth, m_windowSpaceHeight, m_stride, PixelFormat24bppRGB, m_pixelMap);

    //m_backBitmap = new Gdiplus::Bitmap(m_windowSpaceWidth, m_windowSpaceHeight);
    //m_backRenderer = Gdiplus::Graphics::FromImage(m_backBitmap);    //Wier memory usage picks
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
    delete[] string1;
}
//-----------------------------------------------------
#endif