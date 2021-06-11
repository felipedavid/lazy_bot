#include <windows.h>

#include "gui.h"

HINSTANCE instance_handle;

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
    instance_handle = instance;
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)gui, instance, 0, NULL);
    }
    return TRUE;
}
