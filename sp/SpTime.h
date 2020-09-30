#ifndef _SP_TIME_H_
#define _SP_TIME_H_
#include <chrono>

//Time implementation.
namespace sp
{
	#if unix
	typedef std::chrono::_V2::system_clock::time_point time;
	#elif _WIN32
	typedef std::chrono::time_point<std::chrono::steady_clock> time;
	#endif
}
#endif
