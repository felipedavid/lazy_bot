#include <windows.h>
#include <stdio.h>
#include "fishing.h"
#include "common.h"

void start(HMODULE h) {
    buf_test();
    AllocConsole();
    FILE *f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    while (TRUE) {
        if (GetAsyncKeyState(VK_END) & 1) {
            break;
        }
        if (GetAsyncKeyState(VK_HOME) & 1) {
            pulse();
        }
        Sleep(100);
    }

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(h, 0);
}

BOOL DllMain(HINSTANCE inst, u32 reason, void *reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)start, inst, 0, NULL);
    }
    return TRUE;
}
