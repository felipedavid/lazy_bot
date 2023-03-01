#pragma once

namespace WoW {
	typedef const char *(*_ConsolePrintf)(const char* format, ...); 
	extern _ConsolePrintf ConsolePrintf;
}
