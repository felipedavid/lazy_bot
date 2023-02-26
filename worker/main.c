#include <windows.h>
#include <stdio.h>

#include "def.h"
#include "wow.h"
#include "patches.h"
#include "commands.h"
#include "logger.h"

HMODULE module;

void setup_console() {
	log_warning("Remapping console key to END");
	ConsoleSetHotKey(KEY_END);
	log_warning("Registering new commands");
	register_commands();

	enable_console();
	toggle_console();
	set_console_size(1.0f);
}

b32 DllMain(HINSTANCE inst, u32 reason, void *reserved) {
	module = inst;

	switch (reason) {
	case DLL_PROCESS_ATTACH: {
		log_warning("DLL loaded!");
		log_warning("Applying essential patches");
		apply_essential_patches();
		setup_console();
	} break;
	case DLL_PROCESS_DETACH: {
		log_warning("Unloding dll!");

		log_warning("Removing patches");
		remove_essential_patches();

		log_warning("Unregistering commands");
		unregister_commands();
	} break;
	}
	return true;
}
