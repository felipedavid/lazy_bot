#include <windows.h>
#include <cstdio>

#include "game/object_manager.h"

void entrypoint(HMODULE instance) {
    FILE *dummy_file;
    AllocConsole();
    freopen_s(&dummy_file, "CONOUT$", "w", stdout);
    while (true) {
        if (GetAsyncKeyState(VK_SHIFT)) {
            ObjectManager obj_manager;
            obj_manager.populate_lists();
            obj_manager.log_info();
        }

        if (GetAsyncKeyState(VK_END)) {
            FreeLibraryAndExitThread(instance, 0);
            fclose(dummy_file);
            FreeConsole();
        }
        Sleep(100);
    }
}

BOOL DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)entrypoint, instance, 0, NULL);
    }
    return TRUE;
}
