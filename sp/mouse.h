#ifndef _SP_MOUSE_
#define _SP_MOUSE_

#if unix
#include <X11/Xlib.h>
#elif _WIN32
#include <windows.h>
#endif

#include "event.h"
#include "inputBase.h"

//Mouse implementation.
namespace sp
{
class Mouse
{
public:
    //Buttons for linux.
    #if unix
    enum ButtonCode
    {
        Left = Button1, 
        Middle = Button2,
        Right = Button3,
        ScrollUp  = Button4,
        ScrollDown = Button5
    };
    #endif


    //Buttons for windows.
    #if _WIN32
    #define SP_SCROLLUP 5 
    #define SP_SCROLLDOWN 6

    enum ButtonCode
    {
        Left = VK_LBUTTON,
        Middle = VK_MBUTTON,
        Right = VK_RBUTTON,
        ScrollUp  = SP_SCROLLUP,
        ScrollDown = SP_SCROLLDOWN
    };
    #endif

public:
    static bool getButtonPress(const ButtonCode& button);       //Check if the button was pressed.
    static bool getButtonRelease(const ButtonCode& button);     //Check if the button was released.
    static bool getButtonIsPressed(const ButtonCode& button);   //Check if the button is pressed.
    static bool getButtonIsReleased(const ButtonCode& button);  //Check if the button is released.
    static int getScrolling();                                  //Returns the scrolling value
    static void getMousePosition(int *pos_X, int *pos_Y, bool relativeToWindow = false);    //Returns the mouse position.

    static void updateButtonMap(Event& event);                  //Updates the button map changing their button states.

    //==========LINUX IMPLEMENTATION==========
    #if unix
    static void setMouseSource(Display* display, Window* window);   //Sets the source window for the mouse pointer.
    #endif
    //-----------------------------------------------------


    //==========WINDOWS IMPLEMENTATION==========
    #if _WIN32
    static void setMouseSource(HWND* ptr_window);
    #endif
    //-----------------------------------------------------

    static void init();     //Initializes the keyboard.

    static void setNewButton(unsigned int button, InputStates setState); //Assigns (key number) to a key in the key map.

private:
    static InputStateMap m_buttonMap;
    static int m_scroll;
    static int m_lastScroll;


    //Devices for linux
    #if unix
    static Display* ptr_display;
    static Window* ptr_window;
    #endif
    //-----------------------------------------------------


    //Devices for windwos
    #if _WIN32
    static HWND* ptr_window;
    #endif
    //-----------------------------------------------------
};
};
#endif