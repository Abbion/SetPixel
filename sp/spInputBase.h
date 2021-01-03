#ifndef _SP_INPUT_BASE_H_
#define _SP_INPUT_BASE_H_
#include <map>

namespace sp
{
    //Base class for input devices.
    struct InputStates
    {
        bool hold;
        bool press;
        bool release;
    };

    typedef std::map<unsigned int, InputStates> InputStateMap;
}

#endif