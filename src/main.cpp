#include <windows.h>
#include <cstdio>

#include "bot.h"

void entry_point(HMODULE instance) {
    FILE *dummy_file;
    AllocConsole();
    freopen_s(&dummy_file, "CONOUT$", "w", stdout);

    Bot bot;

    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE)) break;

        if (GetAsyncKeyState(VK_NUMPAD1)) {
            bot.entity_manager.populate_lists();
            bot.print_entity_list();
        }
    }

    fclose(dummy_file);
    FreeConsole();
    FreeLibraryAndExitThread(instance, 0);
}

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved )
{
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) entry_point, instance, 0, NULL);
    }
    return TRUE;
}
