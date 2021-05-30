#include <windows.h>

#include "gui.h"
#include "bot.h"

HINSTANCE instance_handle;

BOOL WINAPI DllMain(HINSTANCE instance_handle_dll, DWORD reason, LPVOID reserved) {
    instance_handle = instance_handle_dll;
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)start_gui, NULL, 0, NULL);
            break;
    }
    return TRUE;
}
