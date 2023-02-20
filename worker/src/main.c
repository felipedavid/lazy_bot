#include <windows.h>

#include "bot.h"
#include "listen.h"
#include "logger.h"

Bot_State bot;

BOOL DllMain(HINSTANCE inst, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        setup_logger();
        LINFO("INJECTED!");
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)listen_to_master, NULL, 0, NULL);
    }

    return TRUE;
}