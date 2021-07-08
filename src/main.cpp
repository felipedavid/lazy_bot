#include <windows.h>
#include <cstdio>

#include "game/object_manager.h"
#include "utils/sync_thread.h"
#include "game/functions.h"
#include "bot/bot.h"
#include "utils/hacks.h"
#include "gui/gui.h"

void entrypoint(HMODULE instance) {
    FILE *dummy_file;
    AllocConsole();
    freopen_s(&dummy_file, "CONOUT$", "w", stdout);

    unlock_lua();
    hook_window_proc();
    start_gui(instance);

    unhook_window_proc();
    FreeConsole();
    fclose(dummy_file);
    FreeLibraryAndExitThread(instance, 0);
}

BOOL DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)entrypoint, instance, 0, NULL);
    }
    return TRUE;
}
