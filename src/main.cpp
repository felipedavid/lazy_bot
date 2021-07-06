#include <windows.h>
#include <cstdio>

#include "game/object_manager.h"
#include "bot.h"

void entrypoint(HMODULE instance) {
    FILE *dummy_file;
    AllocConsole();
    freopen_s(&dummy_file, "CONOUT$", "w", stdout);

    while (true) {
        if (GetAsyncKeyState(VK_TAB)) {
            start();
        }
        if (GetAsyncKeyState(VK_SHIFT)) {
            stop();
        }

        if (GetAsyncKeyState(VK_END)) {
            fclose(dummy_file);
            FreeConsole();
            FreeLibraryAndExitThread(instance, 0);
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
