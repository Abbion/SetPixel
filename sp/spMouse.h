#ifndef _SP_MOUSE_H_
#define _SP_MOUSE_H_

#if unix
#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#elif _WIN32
#include <windows.h>
#endif

#include "spEvent.h"
#include "spInputBase.h"

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
        static void init();     //Initializes the mouse.

        static bool getButtonPress(const ButtonCode& button);       //Check if the button was pressed.
        static bool getButtonRelease(const ButtonCode& button);     //Check if the button was released.
        static bool getButtonIsPressed(const ButtonCode& button);   //Check if the button is pressed.
        static bool getButtonIsReleased(const ButtonCode& button);  //Check if the button is released.
        static int getScrolling();                                  //Returns the scrolling value
        static void getMousePosition(int *pos_X, int *pos_Y, bool relativeToWindow = false);    //Returns the mouse position.
        static void getDeltaMousePosition(int *pos_X, int *pos_Y);  //Returns the difference between last mouse position and the new one
    
        static void lockMouse(bool lock);                           //Locks the mouse
        static void hideMouse(bool hide);                           //Hides the mouse coursor

        static void updateButtonMap(Event& event);                  //Updates the button map changing their button states.
         static void setNewButton(unsigned int button, InputStates setState); //Assigns (key number) to a key in the key map.

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

    protected:
        static void setCenterPoint();   //Centers the mouse position so that delta position is correct

    private:
        static InputStateMap m_buttonMap;
        static int m_scroll;
        static int m_lastScroll;
        static int m_lastX, m_lastY;
        static bool m_firstEnter;
        static bool m_lock;

        static int m_screenCenterX;
        static int m_screenCenterY;


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