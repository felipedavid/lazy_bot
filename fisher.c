#include "wow_fun.h"
#include "fisher.h"
#include "stb_ds.h"

#include <windows.h>

#define BOBBER_DISPLAY_ID 668

void fisher_init(Fisher *fisher, Object_Manager *object_manager) {
	fisher->object_manager = object_manager;
	fisher->state = FS_LURE;
	fisher->is_fishing = false;
	fisher->fishing_spell_id = wow_wrapper_get_spell_id_by_name("Fishing");
	ZeroMemory(&fisher->bobber, sizeof(Bobber));
}

void fisher_tick(Fisher *fisher) {
	object_manager_refresh(fisher->object_manager);

	fisher->is_fishing = fisher_is_casting_fishing(fisher);
	fisher->next_sleep_duration = 100;

	Bobber *bobber = &fisher->bobber;

	if (arrlen(fisher->object_manager->players)) {
		exit(-1);
	}

	switch (fisher->state) {
	case FS_LURE:
		// TODO: If the player has lures, use them
		fisher->state = FS_CAST;
		break;
	case FS_CAST:
		wow_wrapper_cast_spell(fisher->fishing_spell_id);
		fisher->next_sleep_duration = 500;
		fisher->state = FS_FISHING;
		break;
	case FS_FISHING:
		if (fisher->is_fishing) {
			fisher_bobber_find(fisher);
			fisher_bobber_refresh(fisher);
			if (bobber->is_splashing) {
				fisher->state = FS_LOOT;
			}
		} else {
			fisher->state = FS_CAST;
		}
		break;
	case FS_LOOT:
		wow_wrapper_gameobject_interact(bobber->pointer);
		fisher->state = FS_CAST;
		fisher->next_sleep_duration = 500;
		break;
	case FS_LOOTING:
		break;
	}
}

void fisher_bobber_find(Fisher *fisher) {
	Bobber *bobber = &fisher->bobber;
	WoW_GameObject ** objs = fisher->object_manager->game_objects;
	WoW_Guid lplayer_guid = fisher->object_manager->local_player->guid;

	for (int i = 0; i < arrlen(objs); i++) {
		WoW_GameObject_Descriptors *desc = objs[i]->descriptors;
		if (desc->GAMEOBJECT_DISPLAYID == BOBBER_DISPLAY_ID) { 
			// TODO: Check if it's the player's bobber  
			bobber->pointer = objs[i];
			return;
		}
	}
}

void fisher_bobber_refresh(Fisher *fisher) {
	Bobber *bobber = &fisher->bobber;

	if (bobber->pointer) {
		WoW_GameObject_Descriptors *bobber_descriptors = bobber->pointer->descriptors;
		bobber->is_splashing = (bobber_descriptors->GAMEOBJECT_FLAGS == 0x20);
	}
}

b32 fisher_is_casting_fishing(Fisher *fisher) {
	WoW_Player *player = fisher->object_manager->local_player;
	WoW_Player_Descriptors *descriptors = object_manager_player_get_descriptors(player);
	return descriptors->UNIT_CHANNEL_SPELL == fisher->fishing_spell_id;
}
