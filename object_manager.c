#include "object_manager.h"
#include "offsets.h"
#include "stb_ds.h"

#pragma comment (lib, "user32.lib")

#include <stdlib.h>

void object_manager_init(Object_Manager *object_manager) {
	object_manager->local_player = NULL;
	object_manager->items = NULL;
	object_manager->containers = NULL;
	object_manager->units = NULL;
	object_manager->players = NULL;
	object_manager->game_objects = NULL;
	object_manager->dynamic_objects = NULL;
	object_manager->corpses = NULL;
}

void object_manager_release(Object_Manager *object_manager) {
	arrfree(object_manager->items);
	arrfree(object_manager->containers);
	arrfree(object_manager->units);
	arrfree(object_manager->players);
	arrfree(object_manager->game_objects);
	arrfree(object_manager->corpses);
	free(object_manager);
}

void object_manager_refresh(Object_Manager *object_manager) {
	arrsetlen(object_manager->items, 0);
	arrsetlen(object_manager->containers, 0);
	arrsetlen(object_manager->units, 0);
	arrsetlen(object_manager->players, 0);
	arrsetlen(object_manager->game_objects, 0);
	arrsetlen(object_manager->corpses, 0);

	u8 *client_connection = *(u8 **)(CLIENT_CONNECTION_PTR_ADDR);
	u8 *wow_object_manager = *(u8 **)(client_connection + OBJECT_MANAGER_OFFSET);

	WoW_Guid local_player_guid = *(WoW_Guid *)(wow_object_manager + LOCAL_PLAYER_GUID_OFFSET);
	WoW_Object *object = *(WoW_Object **)(wow_object_manager + FIRST_OBJECT_OFFSET);
	while (object && ((u32)object & 1) == 0) {
		switch (object->type) {
		case WOT_ITEM: 
			arrput(object_manager->items, (WoW_Item*)object); 
			break;
		case WOT_CONTAINER: 
			arrput(object_manager->containers, (WoW_Container*)object); 
			break;
		case WOT_UNIT: 
			arrput(object_manager->units, (WoW_Unit*)object); 
			break;
		case WOT_PLAYER: {
			// TODO: Check if the guid in the descriptors field is the same
			if (object->guid == local_player_guid) {
				object_manager->local_player = (WoW_Player*)object;
			} else {
				arrput(object_manager->players, (WoW_Player*)object);
			}
		} break;
		case WOT_GAMEOBJECT: 
			arrput(object_manager->game_objects, (WoW_GameObject*)object); 
			break;
		case WOT_DYNAMICOBJECT: 
			arrput(object_manager->dynamic_objects, (WoW_DynamicObject*)object);
			break;
		case WOT_CORPSE: 
			arrput(object_manager->corpses, (WoW_Corpse*)object); 
			break;
		}
		object = object->next;
	}
}

WoW_Item_Descriptors *object_manager_item_get_descriptors(WoW_Item *item) {
	return (WoW_Item_Descriptors*) item->descriptors;
}

WoW_Container_Descriptors *object_manager_container_get_descriptors(WoW_Container *container) {
	return (WoW_Container_Descriptors*) container->descriptors;
}

WoW_Unit_Descriptors *object_manager_unit_get_descriptors(WoW_Unit *unit) {
	return (WoW_Unit_Descriptors*) unit->descriptors;
}

WoW_Player_Descriptors *object_manager_player_get_descriptors(WoW_Player *player) {
	return (WoW_Player_Descriptors*) player->descriptors;
}

WoW_GameObject_Descriptors *object_manager_gameobject_get_descriptors(WoW_GameObject *game_object) {
	return (WoW_GameObject_Descriptors*) game_object->descriptors;
}

WoW_DynamicObject_Descriptors *object_manager_dynamicobject_get_descriptors(WoW_DynamicObject *dynamic_object) {
	return (WoW_DynamicObject_Descriptors*) dynamic_object->descriptors;
}

WoW_Corpse_Descriptors *object_manager_corpse_get_descriptors(WoW_Corpse *corpse) {
	return (WoW_Corpse_Descriptors*) corpse->descriptors;
}
