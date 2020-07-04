#ifndef _SP_EVENT_
#define _SP_EVENT_

#if unix
#include <X11/Xlib.h>
#elif _WIN32
#include <Windows.h>
#include <vector>
#endif

//Event implementation.
namespace sp
{
//Event types used.
enum EventType{
    Close,
    LostFocus,
    GainedFocus,
    Resized,
    Moved,  //Add to linux
    Null
};
//-----------------------------------------------------



//==========LINUX IMPLEMENTATION==========
#if unix
class Event
{
public:
    EventType type = EventType::Null;

public:
    Event() {}
    ~Event() {}

    void updateEventType();
    XEvent* getSystemEventPointer(); //Returns the native event to the os.

private:
    XEvent m_event;
};
//-----------------------------------------------------



//==========WINDOWS IMPLEMENTATION==========
#elif _WIN32

class PixelWindow;

class Event
{
public:
    EventType type = sp::EventType::Null;
    friend class PixelWindow;

public:
    Event() {}
    ~Event() {
        m_messageQueue.clear();
        m_keyQueue.clear();
        m_buttonQueue.clear();
    }

    void updateEventType();
    unsigned int getSystemEventPointer();
    int getSystemKey() const;       //Warning: only WIN32 implementation
    int getSystemButton() const;    //Warning: only WIN32 implementation

private:
    static LRESULT CALLBACK WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp);
    static void clearRepeated();

private:
    static std::vector<unsigned int> m_messageQueue;    //Change to queue
    static std::vector<int> m_keyQueue;
    static std::vector<int> m_buttonQueue;
};
#endif
//-----------------------------------------------------
};
#endif