#ifndef _SP_WINDOW_
#define _SP_WINDOW_

#if unix
#include <X11/Xlib.h>
#elif _WIN32
#include <windows.h>
#endif

#include "spCoreDefined.h"
#include "spEvent.h"
#include "spRenderer.h"
#include "spWindowBase.h"

//Window implementation.
namespace sp
{
class PixelWindow : public WindowBase, public Renderer
{
public:
    PixelWindow(unsigned int width, unsigned int height, const char* title);
    ~PixelWindow();

    virtual void setSize(unsigned int width, unsigned int height);
    virtual void setPosition(int x_pos, int y_pos);
    virtual void setTitle(const char* title);
    virtual void close();

    bool isOpen() const;                //Returns true if the window is open.
    void getNextEvent(Event& event);    //Gets the nest event and assign it to the send event.
    int peekEvents();                   //Returns the number of events in queue.

    #if unix
    Display* getDisplayHandle() const { return m_display; }     //Warning: only unix implementation. Returns the display pointer. 
    Window* getWindowHandle() { return &m_window; }             //Returns the window pointer.
    #endif

    #if _WIN32
    HWND* getWindowHandle() { return &m_window; }   //Returns the window pointer.
    #endif

    friend class Event;

private:
    void setIcon();
    #if _WIN32
    void getCorrectWindowSize(int* pos_x, int* pos_y, int* width, int* height);
    #endif

private:
    static bool m_windowExists;
    static bool m_panicClose;

    //Devices for linux
    #if unix
    Display *m_display;
    Window m_window;
    #endif

    //Devices for windows
    #if _WIN32
    HWND m_window;
    const char* m_className;
    WNDCLASSEX m_windowClass;
    MSG m_messageWin;
    bool m_firstMessage;
    HICON m_windowIcon;
    #endif
};
}
#endif