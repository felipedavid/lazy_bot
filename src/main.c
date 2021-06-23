#include <windows.h>

#include "gui.h"

void bot(HMODULE dll_handle) {
     AllocConsole(); 

     while (TRUE) {
         if (GetAsyncKeyState(VK_END)) {
             FreeConsole();
             FreeLibraryAndExitThread(dll_handle, 0);
         }
     }
}

BOOL DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)gui, instance, 0, NULL);
    }
    return TRUE;
}
