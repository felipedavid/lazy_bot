#pragma once
#include "defs.h"
#include "wow_types.h"

typedef WoW_Item** WoW_Item_Arr;
typedef WoW_Container** WoW_Container_Arr;
typedef WoW_Unit** WoW_Unit_Arr;
typedef WoW_Player** WoW_Player_Arr;
typedef WoW_GameObject** WoW_GameObject_Arr;
typedef WoW_DynamicObject** WoW_DynamicObject_Arr;
typedef WoW_Corpse** WoW_Corpse_Arr;

typedef struct {
	WoW_Player *local_player;
	WoW_Item_Arr items;
	WoW_Container_Arr containers;
	WoW_Unit_Arr units;
	WoW_Player_Arr players;
	WoW_GameObject_Arr game_objects;
	WoW_DynamicObject_Arr dynamic_objects;
	WoW_Corpse_Arr corpses;
} Object_Manager;

void object_manager_init(Object_Manager *);
void object_manager_release(Object_Manager *);
void object_manager_refresh(Object_Manager *);

WoW_Item_Descriptors *object_manager_item_get_descriptors(WoW_Item *);
WoW_Container_Descriptors *object_manager_container_get_descriptors(WoW_Container *);
WoW_Unit_Descriptors *object_manager_unit_get_descriptors(WoW_Unit *);
WoW_Player_Descriptors *object_manager_player_get_descriptors(WoW_Player *);  
WoW_GameObject_Descriptors *object_manager_gameobject_get_descriptors(WoW_GameObject *);  
WoW_DynamicObject_Descriptors *object_manager_dynamicobject_get_descriptors(WoW_DynamicObject *);  
WoW_Corpse_Descriptors *object_manager_corpse_get_descriptors(WoW_Corpse *);  