#include <windows.h>

void bot(HMODULE module_handle) {
    while (true) {
        if (GetAsyncKeyState(VK_END)) {
            FreeLibraryAndExitThread(module_handle, 0);
        }
        Sleep(100);
    }
}

BOOL DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bot, instance, 0, NULL);
    }
}
