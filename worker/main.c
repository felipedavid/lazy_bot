#include <windows.h>
#include <stdio.h>

#include "def.h"
#include "wow.h"
#include "patches.h"
#include "commands.h"

HMODULE module;

void setup_console() {
	ConsoleWrite("Remapping console key to End", C_YELLOW);
	ConsoleSetHotKey(KEY_END);
	ConsoleWrite("Registering new commands", C_YELLOW);
	register_commands();

	enable_console();
	toggle_console();
	set_console_size(1.0f);
}

b32 DllMain(HINSTANCE inst, u32 reason, void *reserved) {
	module = inst;

	switch (reason) {
	case DLL_PROCESS_ATTACH: {
		ConsoleWrite("DLL loaded!", C_RED);
		ConsoleWrite("Applying essential patches", C_YELLOW);
		apply_essential_patches();
		setup_console();
	} break;
	case DLL_PROCESS_DETACH: {
		ConsoleWrite("Unloding dll!", C_RED);

		ConsoleWrite("Removing patches", C_YELLOW);
		remove_essential_patches();

		ConsoleWrite("Unregistering commands", C_YELLOW);
		unregister_commands();
	} break;
	}
	return true;
}
