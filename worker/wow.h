#pragma once

namespace WoW {
	typedef const char *(*_ConsolePrintf)(const char* format, ...); 
	typedef const char *(*_ConsoleCommandRegister)(const char *format, void *callback, int a1, int a2, int a3); 
	extern _ConsolePrintf ConsolePrintf;
	extern _ConsoleCommandRegister ConsoleCommandRegister;
}
