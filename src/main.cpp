#include <windows.h>

#include "gui.h"

HINSTANCE instance_handle;

BOOL DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
    instance_handle = instance;
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)gui, NULL, 0, NULL);
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
