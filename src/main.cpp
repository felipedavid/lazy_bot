#include <windows.h>

#include "gui/gui.h"

BOOL DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)start_gui, instance, 0, NULL);
    }
    return TRUE;
}
