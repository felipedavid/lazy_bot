#include <windows.h>

#include "game/object_manager.hpp"
#include "game/functions.hpp"

void entrypoint(HMODULE module_handle) {
    FILE *dummy_file;
    AllocConsole();
    freopen_s(&dummy_file, "CONOUT$", "w", stdout);

    while (true) {
        if (GetAsyncKeyState(VK_END)) {
            FreeLibraryAndExitThread(module_handle, 0);
        }

        if (GetAsyncKeyState(VK_CONTROL)) {
            if (get_player_guid() > 0) {
                ObjectManager obj_manager;
                obj_manager.populate_list();
                obj_manager.log_objects();
            }
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
