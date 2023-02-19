#include <windows.h>

#include "bot.h"
#include "listen.h"
#include "logger.h"

Bot_State bot;

 //BOOL DllMain(HINSTANCE inst, DWORD reason, LPVOID reserved) {
 //    if (reason == DLL_PROCESS_ATTACH) {
 //        CreateThread(NULL, 0, listen_to_master, NULL, 0, NULL);
 //    }
 //}

int main() {
    setup_logger();
    LINFO("Hi there Go, how it's going? I'm called C, I'm probably your grand-grandfather :P\n");
}