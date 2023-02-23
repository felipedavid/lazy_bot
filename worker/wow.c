#include "wow.h"
#include "offsets.h"

_ConsoleWrite ConsoleWrite = (_ConsoleWrite) CONSOLEWRITE_FUN_PTR;
_ConsoleWriteA ConsoleWriteA = (_ConsoleWriteA) CONSOLEWRITEA_FUN_PTR;
_ConsolePrintf ConsolePrintf = (_ConsolePrintf) CONSOLEPRINTF_FUN_PTR;
_ConsoleSetHotKey ConsoleSetHotKey = (_ConsoleSetHotKey) CONSOLESETHOTKEY_FUN_PTR;
_ConsoleCommandRegister ConsoleCommandRegister = (_ConsoleCommandRegister) CONSOLECOMMANDREGISTER_FUN_PTR;
_ConsoleCommandUnregister ConsoleCommandUnregister = (_ConsoleCommandUnregister) CONSOLECOMMANDUNREGISTER_FUN_PTR;
