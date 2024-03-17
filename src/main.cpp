#include <windows.h>

#define true  1
#define false 0

#include "types.cpp"
#include "wow/wow.cpp"

void start_routine(HMODULE module) {
    *WoW::s_ConsoleAcivePtr = true;
    WoW::ConsolePrintf("Hello there %s!", "gamey");
}

b32 DllMain(HINSTANCE inst, u32 reason, void *reserved) {
    switch (reason) {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)start_routine, inst, 0, NULL);
        break;
    }
    return true;
}