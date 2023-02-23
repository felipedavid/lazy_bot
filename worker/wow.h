#pragma once
#include "def.h"

typedef enum {
	C_WHITE  = 1,
	C_GREY   = 2,
	C_RED    = 3,
	C_YELLOW = 4,
} Console_Text_Color;
typedef void(__fastcall* _ConsoleWrite)(const char *msg, Console_Text_Color color);

typedef enum {
	KEY_END = 523,
} Console_Key_Code; 
typedef void(__fastcall* _ConsoleSetHotKey)(Console_Key_Code key);
typedef int(__fastcall* _ConsoleCommandRegister)(char *cmd, void *callback, int type, const char *help_msg);

_ConsoleWrite ConsoleWrite;
_ConsoleSetHotKey ConsoleSetHotKey;
_ConsoleCommandRegister ConsoleCommandRegister;
