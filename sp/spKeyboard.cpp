#include "spKeyboard.h"
#include <iostream>

//-----------------------------------------------------
sp::InputStateMap sp::Keyboard::m_keyMap;
//-----------------------------------------------------



//-----------------------------------------------------
bool sp::Keyboard::getKeyPress(const KeyCode& key)
{
    if(m_keyMap[key].press)
    {
        m_keyMap[key].press = false;
        return true;
    }
    return false;
}
//-----------------------------------------------------



//-----------------------------------------------------
bool sp::Keyboard::getKeyRelease(const KeyCode& key)
{
    if(m_keyMap[key].release)
    {
        m_keyMap[key].release = false;
        return true;
    }
    return false;  
}
//-----------------------------------------------------



//-----------------------------------------------------
bool sp::Keyboard::getKeyIsPressed(const KeyCode& key)
{
    if(m_keyMap[key].hold)
        return true;
    return false;
}
//-----------------------------------------------------



//-----------------------------------------------------
bool sp::Keyboard::getKeyIsReleased(const KeyCode& key)
{
    if(!m_keyMap[key].hold)
        return true;
    return false;
}
//-----------------------------------------------------



//==========LINUX IMPLEMENTATION==========
//-----------------------------------------------------
#if unix
void sp::Keyboard::updateKeyMap(Event& event)
{    
    if (event.getSystemEventPointer()->type == KeyPress)
    {
        m_keyMap[event.getSystemEventPointer()->xkey.keycode].hold = true;
        m_keyMap[event.getSystemEventPointer()->xkey.keycode].press = true;
        m_keyMap[event.getSystemEventPointer()->xkey.keycode].release = false;
    }
    
    else if (event.getSystemEventPointer()->type == KeyRelease)
    {
        m_keyMap[event.getSystemEventPointer()->xkey.keycode].hold = false;
        m_keyMap[event.getSystemEventPointer()->xkey.keycode].press = false;
        m_keyMap[event.getSystemEventPointer()->xkey.keycode].release = true;
    }
}
#endif
//-----------------------------------------------------



//==========WINDOWS IMPLEMENTATION==========
//-----------------------------------------------------
#if _WIN32
void sp::Keyboard::updateKeyMap(Event& event)
{
    int keyFromSystem = event.getSystemKey();
    if (keyFromSystem != 0)
    {
        if (event.getSystemEventPointer() == WM_KEYDOWN)
        {
            m_keyMap[keyFromSystem].hold = true;
            m_keyMap[keyFromSystem].press = true;
            m_keyMap[keyFromSystem].release = false;
        }

        else if (event.getSystemEventPointer() == WM_KEYUP)
        {
            m_keyMap[keyFromSystem].hold = false;
            m_keyMap[keyFromSystem].press = false;
            m_keyMap[keyFromSystem].release = true;
        }
    }
}
#endif
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Keyboard::init()
{
    InputStates clearState;
    clearState.hold = false;
    clearState.press = false;
    clearState.release = false;

    //Number row
        setNewKey(Num_1, clearState);
        setNewKey(Num_2, clearState);
        setNewKey(Num_3, clearState);
        setNewKey(Num_4, clearState);
        setNewKey(Num_5, clearState);
        setNewKey(Num_6, clearState);
        setNewKey(Num_7, clearState);
        setNewKey(Num_8, clearState);
        setNewKey(Num_9, clearState);
        setNewKey(Num_0, clearState);

    //Numpad
        setNewKey(Numpad_1, clearState);
        setNewKey(Numpad_2, clearState);
        setNewKey(Numpad_3, clearState);
        setNewKey(Numpad_4, clearState);
        setNewKey(Numpad_5, clearState);
        setNewKey(Numpad_6, clearState);
        setNewKey(Numpad_7, clearState);
        setNewKey(Numpad_8, clearState);
        setNewKey(Numpad_9, clearState);
        setNewKey(Numpad_0, clearState);

    //Function key row
        setNewKey(F_1, clearState);
        setNewKey(F_2, clearState);
        setNewKey(F_3, clearState);
        setNewKey(F_4, clearState);
        setNewKey(F_5, clearState);
        setNewKey(F_6, clearState);
        setNewKey(F_7, clearState);
        setNewKey(F_8, clearState);
        setNewKey(F_9, clearState);
        setNewKey(F_10, clearState);
        setNewKey(F_11, clearState);
        setNewKey(F_12, clearState);

    //qwerty
        setNewKey(Q, clearState);
        setNewKey(W, clearState);
        setNewKey(E, clearState);
        setNewKey(R, clearState);
        setNewKey(T, clearState);
        setNewKey(Y, clearState);
        setNewKey(U, clearState);
        setNewKey(I, clearState);
        setNewKey(O, clearState);
        setNewKey(P, clearState);
        setNewKey(A, clearState);
        setNewKey(S, clearState);
        setNewKey(D, clearState);
        setNewKey(F, clearState);
        setNewKey(G, clearState);
        setNewKey(H, clearState);
        setNewKey(J, clearState);
        setNewKey(K, clearState);
        setNewKey(L, clearState);
        setNewKey(Z, clearState);
        setNewKey(X, clearState);
        setNewKey(C, clearState);
        setNewKey(V, clearState);
        setNewKey(B, clearState);
        setNewKey(N, clearState);
        setNewKey(M, clearState);
    
    //Special keys
        setNewKey(Minus, clearState);
        setNewKey(Equal, clearState);
        setNewKey(Backspace, clearState);
        setNewKey(Enter, clearState);
        setNewKey(Left, clearState);
        setNewKey(Right, clearState);
        setNewKey(Up, clearState);
        setNewKey(Down, clearState);
        setNewKey(Delete, clearState);
        setNewKey(Capslock, clearState);
        setNewKey(Tab, clearState);
        setNewKey(Esc, clearState);
        setNewKey(Space, clearState);
        setNewKey(R_shift, clearState);
        setNewKey(R_ctrl, clearState);
        setNewKey(R_alt, clearState);
        setNewKey(L_alt, clearState);
        setNewKey(L_ctrl, clearState);
        setNewKey(L_shift, clearState);
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Keyboard::setNewKey(unsigned int key, sp::InputStates setState)
{
    m_keyMap.insert(std::pair<unsigned int, InputStates>(key, setState));
}
//-----------------------------------------------------