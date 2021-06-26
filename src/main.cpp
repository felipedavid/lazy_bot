#include <windows.h>

#include "game/object_manager.hpp"

void bot(HMODULE module_handle) {
    while (true) {
        if (GetAsyncKeyState(VK_END)) {
            FreeLibraryAndExitThread(module_handle, 0);
        }

        if (GetAsyncKeyState(VK_CONTROL)) {
            if (get_player_guid() > 0) {
                ObjectManager obj_manager;
                obj_manager.populate_lists();
                obj_manager.log_objects();
            }
        }
        Sleep(100);
    }
}

BOOL DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot, instance, 0, NULL);
    }
}
