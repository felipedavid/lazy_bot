#include <windows.h>
#include <stdio.h>

#include "def.h"
#include "wow.h"
#include "patches.h"

// TODO @(felipe): There is some kinda of check that don't allow
// commands to execute functions outside of wow's .text section.
// Find this check and patch it
// Patch: 0x63CE70
void __fastcall saysomething(char *cmd, char *args) {
	ConsoleWrite("Please work!!!", C_RED);
}

void setup(HMODULE module) {
	ConsoleWrite("DLL Injected!", C_RED);
	ConsoleWrite("Remapping console key to End", C_YELLOW);
	ConsoleSetHotKey(KEY_END);

	ConsoleWrite("Registering commands", C_YELLOW);
	ConsoleCommandRegister("sayhi", (void*)saysomething, 4, 0);

	ConsoleWrite("Applying essential patches", C_YELLOW);
	apply_essential_patches();

	while (true) {
		if (GetAsyncKeyState(VK_HOME) & 1) {
			break;
		}
		Sleep(10);
	}

	ConsoleWrite("Unloding dll!", C_RED);

	FreeLibraryAndExitThread(module, 0);
}

b32 DllMain(HINSTANCE inst, u32 reason, void *reserved) {
	if (reason == DLL_PROCESS_ATTACH) {
		CreateThread(NULL, 4096, (LPTHREAD_START_ROUTINE)setup, inst, 0, NULL);
	}
	return true;
}
