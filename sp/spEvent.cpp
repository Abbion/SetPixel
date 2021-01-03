#include "spEvent.h"
#include <iostream>
#include <bitset>


//==========LINUX IMPLEMENTATION==========
#if unix
//-----------------------------------------------------
//Warning: the system pointer works different for every os. Use only if really needed.
void sp::Event::updateEventType()
{
    switch (m_event.type)
    {
    case ClientMessage:
        type = EventType::Close;
        break;
    
    case FocusOut:
        type = EventType::LostFocus;
    break;

    case FocusIn:
        type = EventType::GainedFocus;
    break;

    //The Move and Resize event is called by the same event so we decide with one it is in the getNextEvent in window class
    case ConfigureNotify:
        type = EventType::Resized;
    break;

    case Expose:
        std::cout << "Exp\n";
    break;

    default:
        type = EventType::Null;
        break;
    }
}
//-----------------------------------------------------



//-----------------------------------------------------
XEvent* sp::Event::getSystemEventPointer()
{
    return &m_event;
}
//-----------------------------------------------------



//==========WINDOWS IMPLEMENTATION==========
#elif _WIN32

//static variables
std::vector<unsigned int> sp::Event::m_messageQueue;
std::vector<int> sp::Event::m_keyQueue;
std::vector<int> sp::Event::m_buttonQueue;
//-----------------------------------------------------


//-----------------------------------------------------
void sp::Event::updateEventType()
{
    switch (m_messageQueue.at(m_messageQueue.size() - 1))
    {
    case WM_CLOSE:
    case WM_DESTROY:
        type = EventType::Close;
        break;

    case WM_KILLFOCUS:
        type = EventType::LostFocus;
        break;

    case WM_SETFOCUS:
        type = EventType::GainedFocus;
        break;

    case WM_SIZE:
        type = EventType::Resized;
        break;

    case WM_MOVE:
        type = EventType::Moved;
        break;

    default:
        type = EventType::Null;
        break;
    }
}
//-----------------------------------------------------


//-----------------------------------------------------
//Warning: the system pointer works different for every os. Use only if really needed.
unsigned int sp::Event::getSystemEventPointer()
{
    if(!m_messageQueue.empty())
        return m_messageQueue.at(m_messageQueue.size() - 1);
    return 0;
}
//-----------------------------------------------------


//-----------------------------------------------------
//Warning: only WIN32 implementation. Use only if really needed.
int sp::Event::getSystemKey() const
{
    if (!m_keyQueue.empty())
    {
        int key = m_keyQueue.at(m_keyQueue.size() - 1);
        m_keyQueue.pop_back();
        return key;
    }
    return 0;
}
//-----------------------------------------------------


//-----------------------------------------------------
//Warning: only WIN32 implementation. Use only if really needed.
int sp::Event::getSystemButton() const
{
    if (!m_buttonQueue.empty())
    {
        int button = m_buttonQueue.at(m_messageQueue.size() - 1);
        m_buttonQueue.pop_back();
        return button;
    }
    return 0;
}
//-----------------------------------------------------


//-----------------------------------------------------
void sp::Event::clearRepeated()
{
    bool first = false;
    for(int i = 0; i < m_messageQueue.size(); i++)
    {
        if(m_messageQueue.at(i) == WM_SIZE && first)
            m_messageQueue.erase(m_messageQueue.begin() + i);
        else
            first = true;
    }
}
//-----------------------------------------------------

//-----------------------------------------------------
long __stdcall sp::Event::WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_CLOSE:
    case WM_DESTROY:
        DestroyWindow(window);
        m_messageQueue.clear();
        m_messageQueue.push_back(msg);
        break;

    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_SETFOCUS:
    case WM_KILLFOCUS:
    case WM_SIZE:
    case WM_MOVE:
        m_messageQueue.push_back(msg);
        break;
    
    
    case WM_KEYDOWN:
    case WM_KEYUP:
    {
        m_messageQueue.push_back(msg);
        int repeatTest = (lp >> 30);        //Testing if the key repeats press message.
        bool posDetector = (lp >> 24) & 0x1;       //Test if the (control, alt) is the left or the rght one
        int shiftPosDetector = (lp & 0x00ff0000) >> 16;    //Test if the right or left shift is pressed 

        if (wp == VK_CONTROL)       wp = posDetector ? VK_RCONTROL : VK_LCONTROL;
        else if (wp == VK_MENU)     wp = posDetector ? VK_RMENU : VK_LMENU;
        else if (wp == VK_SHIFT)    wp = MapVirtualKey(shiftPosDetector, MAPVK_VSC_TO_VK_EX);

        if(repeatTest != 1){
            m_keyQueue.push_back(wp);
        }
    }
        break;

    case WM_MOUSEWHEEL:
    {
        m_messageQueue.push_back(msg);
        if ((SHORT)HIWORD(wp) > 0)
            m_buttonQueue.push_back(5);     //Scroll up. DEF in mouse.h
        else
            m_buttonQueue.push_back(6);     //Scroll down. DEF in mouse.h
    }
        break;

    case WM_ERASEBKGND:
        return true;
    
    default:
        return DefWindowProc(window, msg, wp, lp);
    }
    
    return 0;
}
//-----------------------------------------------------

#endif