#include <windows.h>

#include "commands.h"
#include "wow.h"
#include "fun_wrappers.h"
#include "entity_manager.h"
#include "logger.h"
#include "utils.h"

extern HMODULE module;
extern Entity active_player;
extern Entity *entity_list;

void __fastcall player(char *cmd, char *args) {
	populate_entity_list();
	log_entity(active_player);
}

void __fastcall casting(char *cmd, char *args) {
	populate_entity_list();
	log_info("Is casting: %d", get_casting_spell(active_player));
}

void __fastcall unload(char *cmd, char *args) {
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FreeLibrary, module, 0, NULL);
}

void __fastcall entities(char *cmd, char *args) {
	populate_entity_list();
	log_entity_list();
}

void __fastcall test(char *cmd, char *args) {
	populate_entity_list();
	for (int i = 0; i < buf_len(entity_list); i++) {
		Entity ent = entity_list[i];
		if ((get_type(ent) == ET_GAMEOBJ) && 
		   (get_display_id(ent) == DISPLAY_ID_BOBBER) && 
		   (get_creator_guid(ent) == get_guid(active_player))) {
			log_info("Bobber found!");
			log_game_object(ent);
		}
	}
}

void register_commands() {
	ConsoleCommandRegister("unload", (void*)unload, CT_DEBUG, "Unloads the injected dll");
	ConsoleCommandRegister("entities", (void*)entities, CT_DEBUG, "Lists all visible entities");
	ConsoleCommandRegister("player", (void*)player, CT_DEBUG, "Shows active player info");
	ConsoleCommandRegister("casting", (void*)casting, CT_DEBUG, "Shows spell id the active player is casting");
	ConsoleCommandRegister("test", (void*)test, CT_DEBUG, "Do random stuff");
}

void unregister_commands() {
	ConsoleCommandUnregister("unload");
	ConsoleCommandUnregister("entities");
}

