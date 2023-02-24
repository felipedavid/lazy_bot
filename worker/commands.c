#include <windows.h>

#include "commands.h"
#include "wow.h"
#include "entity_manager.h"

extern HMODULE module;

void __fastcall unload(char *cmd, char *args) {
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FreeLibrary, module, 0, NULL);
}

void __fastcall entities(char *cmd, char *args) {
	populate_entity_list();
	log_entity_list();
}

void register_commands() {
	ConsoleCommandRegister("unload", (void*)unload, CT_DEBUG, "Unloads the injected dll");
	ConsoleCommandRegister("entities", (void*)entities, CT_DEBUG, "Lists all visible entities");
}

void unregister_commands() {
	ConsoleCommandUnregister("unload");
	ConsoleCommandUnregister("entities");
}

