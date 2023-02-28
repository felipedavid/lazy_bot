#pragma once

typedef void(* _ConsolePrintf)(const char *msg, ...);
typedef int(__cdecl* _ConsoleCommandRegister)(const char *cmd, void *callback, int type, const char *help_msg, int a1);

extern _ConsolePrintf ConsolePrintf;
extern _ConsoleCommandRegister ConsoleCommandRegister;
