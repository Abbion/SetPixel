#include "mouse.h"
#include <iostream>

//-----------------------------------------------------
sp::InputStateMap sp::Mouse::m_buttonMap;
int sp::Mouse::m_scroll;
int sp::Mouse::m_lastScroll;
int sp::Mouse::m_lastX;
int sp::Mouse::m_lastY;
bool sp::Mouse::m_firstEnter = false;
bool sp::Mouse::m_lock = false;

int sp::Mouse::m_screenCenterX;
int sp::Mouse::m_screenCenterY;

//Devices for linux
#if unix
Display* sp::Mouse::ptr_display = nullptr;
Window* sp::Mouse::ptr_window = nullptr;
//Devices for windows
#elif _WIN32 
HWND* sp::Mouse::ptr_window = nullptr;
#endif
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Mouse::init()
{
    InputStates clearState;
    clearState.hold = false;
    clearState.press = false;
    clearState.release = false;

    setNewButton(Left, clearState);
    setNewButton(Middle, clearState);
    setNewButton(Right, clearState);
    
    setCenterPoint();
}
//-----------------------------------------------------



//-----------------------------------------------------
bool sp::Mouse::getButtonPress(const ButtonCode& button)
{
    if(m_buttonMap[button].press)
    {
        m_buttonMap[button].press = false;
        return true;
    }
    return false;
}
//-----------------------------------------------------



//-----------------------------------------------------
bool sp::Mouse::getButtonRelease(const ButtonCode& button)
{
    if(m_buttonMap[button].release)
    {
        m_buttonMap[button].release = false;
        return true;
    }
    return false;
}
//-----------------------------------------------------



//-----------------------------------------------------
bool sp::Mouse::getButtonIsPressed(const ButtonCode& button)
{
    if(m_buttonMap[button].hold)
        return true;
    return false;
}
//-----------------------------------------------------



//-----------------------------------------------------
bool sp::Mouse::getButtonIsReleased(const ButtonCode& button)
{
    if(!m_buttonMap[button].hold)
        return true;
    return false;
}
//-----------------------------------------------------



//-----------------------------------------------------
int sp::Mouse::getScrolling()
{
    int scrollAmount = m_scroll - m_lastScroll;
    m_lastScroll = m_scroll; 
    return scrollAmount;
}
//-----------------------------------------------------



//==========LINUX IMPLEMENTATION==========
//-----------------------------------------------------
#if unix
void sp::Mouse::getMousePosition(int *pos_X, int *pos_Y, bool relativeToWindow)
{
    int x, y, x_w, y_w = 0;
    unsigned int mask = 0;
    Window child, root;
    XQueryPointer(ptr_display, *ptr_window, &child, &root, &x, &y, &x_w ,&y_w, &mask);
    
    if(!relativeToWindow)
    {
        *pos_X = x;
        *pos_Y = y;
    }
    else
    {
        *pos_X = x_w;
        *pos_Y = y_w;
    }
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Mouse::updateButtonMap(Event& event)
{
    if(event.getSystemEventPointer()->type == ButtonPress)
    {
        int button = event.getSystemEventPointer()->xbutton.button;

        if(button < ScrollUp)
        {
            m_buttonMap[button].hold = true;
            m_buttonMap[button].press = true;
            m_buttonMap[button].release = false;
        }

        else if(event.getSystemEventPointer()->xbutton.button == ScrollUp)
        {
            m_scroll++;
        }

        else if(event.getSystemEventPointer()->xbutton.button == ScrollDown)
        {
            m_scroll--;
        }   
    }

    else if(event.getSystemEventPointer()->type == ButtonRelease)
    {
        int button = event.getSystemEventPointer()->xbutton.button;
        m_buttonMap[button].hold = false;
        m_buttonMap[button].press = false;
        m_buttonMap[button].release = true;
    }
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Mouse::setMouseSource(Display* display, Window* window)
{
    ptr_display = display;
    ptr_window = window;
}
#endif
//-----------------------------------------------------



//==========WINDOWS IMPLEMENTATION==========
//-----------------------------------------------------
#if _WIN32
void sp::Mouse::getMousePosition(int *pos_X, int *pos_Y, bool relativeToWindow)
{
    POINT position;

    GetCursorPos(&position);
    if (relativeToWindow)
    {
        RECT windowRect;
        GetWindowRect(*ptr_window, &windowRect);

        position.x -= windowRect.left;
        position.y -= windowRect.top;
    }

    *pos_X = position.x;
    *pos_Y = position.y;
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Mouse::updateButtonMap(Event& event)
    {
        if (event.getSystemEventPointer() == WM_LBUTTONDOWN)
        {
            m_buttonMap[VK_LBUTTON].hold = true;
            m_buttonMap[VK_LBUTTON].press = true;
            m_buttonMap[VK_LBUTTON].release = false;
        }

        else if (event.getSystemEventPointer() == WM_LBUTTONUP)
        {
            m_buttonMap[VK_LBUTTON].hold = false;
            m_buttonMap[VK_LBUTTON].press = false;
            m_buttonMap[VK_LBUTTON].release = true;
        }

        else if (event.getSystemEventPointer() == WM_RBUTTONDOWN)
        {
            m_buttonMap[VK_RBUTTON].hold = true;
            m_buttonMap[VK_RBUTTON].press = true;
            m_buttonMap[VK_RBUTTON].release = false;
        }

        else if (event.getSystemEventPointer() == WM_RBUTTONUP)
        {
            m_buttonMap[VK_RBUTTON].hold = false;
            m_buttonMap[VK_RBUTTON].press = false;
            m_buttonMap[VK_RBUTTON].release = true;
        }

        else if (event.getSystemEventPointer() == WM_MBUTTONDOWN)
        {
            m_buttonMap[VK_MBUTTON].hold = true;
            m_buttonMap[VK_MBUTTON].press = true;
            m_buttonMap[VK_MBUTTON].release = false;
        }

        else if (event.getSystemEventPointer() == WM_MBUTTONUP)
        {
            m_buttonMap[VK_MBUTTON].hold = false;
            m_buttonMap[VK_MBUTTON].press = false;
            m_buttonMap[VK_MBUTTON].release = true;
        }

        else if (event.getSystemEventPointer() == WM_MOUSEWHEEL)
        {
            int scroll = event.getSystemButton();
            if (scroll == SP_SCROLLDOWN)
                m_scroll--;
            else if(scroll == SP_SCROLLUP)
                m_scroll++;
        }
    }
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Mouse::getDeltaMousePosition(int *pos_X, int *pos_Y)
{   
    if(!m_firstEnter)
    {
        getMousePosition(&m_lastX, &m_lastY);
        m_firstEnter = true;
    }

    int tempX, tempY;
    getMousePosition(&tempX, &tempY);
    *pos_X = tempX - m_lastX;
    *pos_Y = tempY - m_lastY;

    
    if(m_lock)
    {
        SetCursorPos(m_screenCenterX, m_screenCenterY);
        m_lastX = m_screenCenterX;
        m_lastY = m_screenCenterY;
    }
    else
    {
        m_lastX = tempX;
        m_lastY = tempY;   
    }
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Mouse::setMouseSource(HWND* window)
{
    ptr_window = window;
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Mouse::hideMouse(bool hide)
{
    ShowCursor(!hide);
}
//-----------------------------------------------------
#endif



//-----------------------------------------------------
void sp::Mouse::lockMouse(bool lock)
{
    m_lock = lock;
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Mouse::setNewButton(unsigned int button, sp::InputStates setState)
{
    m_buttonMap.insert(std::pair<unsigned int, InputStates>(button, setState));
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Mouse::setCenterPoint()
{
    m_screenCenterX = GetSystemMetrics(SM_CXSCREEN) / 2;
    m_screenCenterY = GetSystemMetrics(SM_CYSCREEN) / 2;
}
//-----------------------------------------------------