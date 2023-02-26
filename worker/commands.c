#include <windows.h>

#include "commands.h"
#include "wow.h"
#include "entity_manager.h"
#include "fun_wrappers.h"

extern HMODULE module;

void __fastcall unload(char *cmd, char *args) {
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FreeLibrary, module, 0, NULL);
}

void __fastcall entities(char *cmd, char *args) {
	populate_entity_list();
	log_entity_list();
}

void __fastcall test(char *cmd, char *args) {
	wow_cast_spell(FISHING, 0);
}

void register_commands() {
	ConsoleCommandRegister("unload", (void*)unload, CT_DEBUG, "Unloads the injected dll");
	ConsoleCommandRegister("entities", (void*)entities, CT_DEBUG, "Lists all visible entities");
	ConsoleCommandRegister("test", (void*)test, CT_DEBUG, "Do random stuff");
}

void unregister_commands() {
	ConsoleCommandUnregister("unload");
	ConsoleCommandUnregister("entities");
}

