#include <windows.h>
#include <assert.h>

#include "types.cpp"
#include "wow/utils.cpp"

void start_routine(HMODULE module) {
	WoW::init();

	*WoW::s_consoleAccessEnabledPtr = true;
	*WoW::s_consoleActivePtr = true;
	WoW::ConsoleWriteA("Hello there %s%s :)", 5, "again", "yeah");

    FreeLibraryAndExitThread(module, 0);
}

b32 DllMain(HMODULE module, u32 reason, void *reserved) {
    switch (reason) {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)start_routine, module, 0, NULL);
        break;
    case DLL_PROCESS_DETACH:
        break;
    }

    return true;
}