#ifndef _SP_KEYBOARD_H_
#define _SP_KEYBOARD_H_

#if unix
#include <X11/Xlib.h>
#elif _WIN32
#include <Windows.h>
#endif

#include "spEvent.h"
#include "spInputBase.h"


namespace sp
{
    //Keyboard implementation.
    class Keyboard
    {
    public:
        //Keys for linux.
        //XK_[KEY] are not working for me. Don't know why.
        #if unix
        enum KeyCode
        {
            Num_1 = 10,
            Num_2 = 11,
            Num_3 = 12,
            Num_4 = 13,
            Num_5 = 14,
            Num_6 = 15,
            Num_7 = 16,
            Num_8 = 17,
            Num_9 = 18,
            Num_0 = 19,
            Numpad_1 = 87,
            Numpad_2 = 88,
            Numpad_3 = 89,
            Numpad_4 = 83,
            Numpad_5 = 84,
            Numpad_6 = 85,
            Numpad_7 = 79,
            Numpad_8 = 80,
            Numpad_9 = 81,
            Numpad_0 = 90,
            F_1 = 67,
            F_2 = 68,
            F_3 = 69,
            F_4 = 70,
            F_5 = 71,
            F_6 = 72,
            F_7 = 73,
            F_8 = 74,
            F_9 = 75,
            F_10 = 76,
            F_11 = 95,
            F_12 = 96,
            Q = 24,
            W = 25,
            E = 26,
            R = 27,
            T = 28,
            Y = 29,
            U = 30,
            I = 31,
            O = 32,
            P = 33,
            A = 38,
            S = 39,
            D = 40,
            F = 41,
            G = 42,
            H = 43,
            J = 44,
            K = 45,
            L = 46,
            Z = 52,
            X = 53,
            C = 54,
            V = 55,
            B = 56,
            N = 57,
            M = 58,
            Minus = 20,
            Equal = 21,
            Backspace = 22,
            Enter = 36,
            Left = 113,
            Right = 114,
            Up = 111,
            Down = 116,
            Delete = 119,
            Capslock = 66,
            Tab = 23,
            Esc = 9,
            Space = 65,
            R_shift = 62,
            R_ctrl = 105,
            R_alt = 108,
            L_alt = 64,
            L_ctrl = 37,
            L_shift = 50
        };
        #endif

        //Keys for windows.
        #if _WIN32 
	    enum KeyCode
	    {
            Num_1 = '1',
            Num_2 = '2',
            Num_3 = '3',
            Num_4 = '4',
            Num_5 = '5',
            Num_6 = '6',
            Num_7 = '7',
            Num_8 = '8',
            Num_9 = '9',
            Num_0 = '0',
            Numpad_1 = VK_NUMPAD1,
            Numpad_2 = VK_NUMPAD2,
            Numpad_3 = VK_NUMPAD3,
            Numpad_4 = VK_NUMPAD4,
            Numpad_5 = VK_NUMPAD5,
            Numpad_6 = VK_NUMPAD6,
            Numpad_7 = VK_NUMPAD7,
            Numpad_8 = VK_NUMPAD8,
            Numpad_9 = VK_NUMPAD9,
            Numpad_0 = VK_NUMPAD0,
            F_1 = VK_F1,
            F_2 = VK_F2,
            F_3 = VK_F3,
            F_4 = VK_F4,
            F_5 = VK_F5,
            F_6 = VK_F6,
            F_7 = VK_F7,
            F_8 = VK_F8,
            F_9 = VK_F9,
            F_10 = VK_F10,
            F_11 = VK_F11,
            F_12 = VK_F12,
            Q = 'Q',
            W = 'W',
            E = 'E',
            R = 'R',
            T = 'T',
            Y = 'Y',
            U = 'U',
            I = 'I',
            O = 'O',
            P = 'P',
            A = 'A',
            S = 'S',
            D = 'D',
            F = 'F',
            G = 'G',
            H = 'H',
            J = 'J',
            K = 'K',
            L = 'L',
            Z = 'Z',
            X = 'X',
            C = 'C',
            V = 'V',
            B = 'B',
            N = 'N',
            M = 'M',
            Minus = VK_OEM_MINUS,
            Equal = VK_OEM_PLUS,
            Backspace = VK_BACK,
            Enter = VK_RETURN,
            Left = VK_LEFT,
            Right = VK_RIGHT,
            Up = VK_UP,
            Down = VK_DOWN,
            Delete = VK_DELETE,
            Capslock = VK_CAPITAL,
            Tab = VK_TAB,
            Esc = VK_ESCAPE,
            Space = VK_SPACE,
            R_shift = VK_RSHIFT,
            R_ctrl = VK_RCONTROL,
            R_alt = VK_RMENU,
            L_alt = VK_LMENU,
            L_ctrl = VK_LCONTROL,
            L_shift = VK_LSHIFT
	    };
        #endif

    public:
        static bool getKeyPress(const KeyCode& key);        //Check if the key was pressed.
        static bool getKeyRelease(const KeyCode& key);      //Check if the key was released.
        static bool getKeyIsPressed(const KeyCode& key);    //Check if the key is pressed.
        static bool getKeyIsReleased(const KeyCode& key);   //Check if the key is released.

        static void updateKeyMap(Event& event);             //Updates the key map changing their key states.
        static void init();                                 //Initializes the keyboard.

        static void setNewKey(unsigned int key, InputStates setState); //Assigns (key number) to a key in the key map.
    private:
        static InputStateMap m_keyMap;
    
    };
}
#endif