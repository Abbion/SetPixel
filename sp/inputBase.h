#ifndef _SP_INPUT_BASE_
#define _SP_INPUT_BASE_
#include <map>

//Base class for input devices.
namespace sp
{
struct InputStates
{
    bool hold;
    bool press;
    bool release;
};

typedef std::map<unsigned int, InputStates> InputStateMap;
}

#endif