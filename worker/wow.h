#pragma once
#include "def.h"

typedef enum {
	C_WHITE  = 1,
	C_GREY   = 2,
	C_RED    = 3,
	C_YELLOW = 4,
} Console_Text_Color;
typedef void(__fastcall* _ConsoleWrite)(char *msg, Console_Text_Color color);
typedef void(* _ConsoleWriteA)(char *msg, Console_Text_Color color, ...);
typedef void(* _ConsolePrintf)(char *msg, ...);

typedef enum {
	KEY_END = 523,
} Console_Key_Code; 
typedef void(__fastcall* _ConsoleSetHotKey)(Console_Key_Code key);

typedef enum {
	CT_DEBUG = 0,
	CT_GRAPHICS = 1,
	CT_CONSOLE = 2,
	CT_COMBAT = 3,
	CT_GAME = 4,
	CT_DEFAULT = 5,
	CT_NET = 6,
	CT_SOUND = 7,
	CT_GM = 8,
} Command_Type;
typedef int(__fastcall* _ConsoleCommandRegister)(char *cmd, void *callback, Command_Type type, char *help_msg);
typedef int(__fastcall* _ConsoleCommandUnregister)(char *cmd);

_ConsoleWrite ConsoleWrite;
_ConsoleWriteA ConsoleWriteA;
_ConsolePrintf ConsolePrintf;
_ConsoleSetHotKey ConsoleSetHotKey;
_ConsoleCommandRegister ConsoleCommandRegister;
_ConsoleCommandUnregister ConsoleCommandUnregister;
