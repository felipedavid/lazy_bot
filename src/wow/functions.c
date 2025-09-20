typedef int (__fastcall *FnConsoleWrite)(char *str, COLOR_T color);
typedef int (__cdecl *FnConsoleWriteA)(char *str, COLOR_T color, ...);
typedef unsigned long long (__fastcall *FnClntObjMgrGetActivePlayer)();
typedef void *(__fastcall *FnClntObjMgrObjectPtr)(unsigned int typeMask, char * fileName, unsigned long long guid);
typedef void *(__stdcall *FnGetObjectPtr)(unsigned long long guid);

#define ConsoleWrite ((FnConsoleWrite)OFFSET_CONSOLEWRITE)
#define ConsoleWriteA ((FnConsoleWriteA)OFFSET_CONSOLEWRITEA)
#define ClntObjMgrGetActivePlayer ((FnClntObjMgrGetActivePlayer)OFFSET_CLNTOBJMGRGETACTIVEPLAYER)
#define ClntObjMgrObjectPtr ((FnClntObjMgrObjectPtr)OFFSET_CLNTOBJMGROBJECTPTR)
#define GetObjectPtr ((FnGetObjectPtr)OFFSET_GETOBJECTPTR)