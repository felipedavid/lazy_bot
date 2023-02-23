#include <windows.h>
#include <stdio.h>

#include "def.h"
#include "wow.h"
#include "patches.h"

HMODULE module;

void __fastcall unload(char *cmd, char *args) {
	ConsoleWrite("Unloding dll!", C_RED);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FreeLibrary, module, 0, NULL);
}

b32 DllMain(HINSTANCE inst, u32 reason, void *reserved) {
	module = inst;

	switch (reason) {
	case DLL_PROCESS_ATTACH: {
		ConsoleWrite("DLL loaded!", C_RED);
		ConsoleWrite("Remapping console key to End", C_YELLOW);
		ConsoleSetHotKey(KEY_END);

		ConsoleWrite("Registering new commands", C_YELLOW);
		ConsoleCommandRegister("unload", (void*)unload, 4, 0);

		ConsoleWrite("Applying essential patches", C_YELLOW);
		apply_essential_patches();
	} break;
	case DLL_PROCESS_DETACH: {
		ConsoleWrite("Removing patches", C_YELLOW);
		remove_essential_patches();
	} break;
	}
	return true;
}
