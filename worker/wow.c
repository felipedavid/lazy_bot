#include "wow.h"
#include "offsets.h"

_ConsoleWrite ConsoleWrite = (_ConsoleWrite) CONSOLEWRITE_FUN_PTR;
_ConsoleSetHotKey ConsoleSetHotKey = (_ConsoleSetHotKey) CONSOLESETHOTKEY_FUN_PTR;
_ConsoleCommandRegister ConsoleCommandRegister = (_ConsoleCommandRegister) CONSOLECOMMANDREGISTER_FUN_PTR;
