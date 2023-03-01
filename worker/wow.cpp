#include "wow.h"
#include "offsets.h"

namespace WoW {
	_ConsolePrintf ConsolePrintf = (_ConsolePrintf) CONSOLEPRINTF_FUN_PTR;
	_ConsoleCommandRegister ConsoleCommandRegister = (_ConsoleCommandRegister) CONSOLECOMMANDREGISTER_FUN_PTR;
}