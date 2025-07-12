
typedef int (__fastcall *FnConsoleWrite)(char *str, COLOR_T color);
typedef int (__cdecl *FnConsoleWriteA)(char *str, COLOR_T color, ...);
typedef unsigned long long (__fastcall *FnClntObjMgrGetActivePlayer)();
typedef unsigned int (__stdcall *FnClntObjMgrObjectPtr)(unsigned long long);

#define ConsoleWrite ((FnConsoleWrite)OFFSET_CONSOLEWRITE)
#define ConsoleWriteA ((FnConsoleWriteA)OFFSET_CONSOLEWRITEA)
#define ClntObjMgrGetActivePlayer ((FnClntObjMgrGetActivePlayer)OFFSET_CLNTOBJMGRGETACTIVEPLAYER)
#define ClntObjMgrObjectPtr ((FnClntObjMgrObjectPtr)OFFSET_CLNTOBJMGROBJECTPTR)