#include "pch.h"
#include "offsets.h"
#include "memory.h"
#include "wow.h"
#include "object_manager.h"
#include "logger.h"

const char* object_type_str[] = {
	"OBJECT_TYPE_NONE",
	"OBJECT_TYPE_ITEM",
	"OBJECT_TYPE_CONTAINER",
	"OBJECT_TYPE_UNIT",
	"OBJECT_TYPE_PLAYER",
	"OBJECT_TYPE_GAMEOBJECT",
	"OBJECT_TYPE_DYNAMICOBJECT",
	"OBJECT_TYPE_CORPSE",
};

void WoW_Object::init(u8* ptr, u64 guid, Object_Type type) {
	this->ptr = ptr;
	this->guid = guid;
	this->type = type;
	this->descriptors = read_memory<u8*>(ptr + OBJECT_DESCRIPTOR);
}

b32 WoW_Object::is_valid() {
	return WoW::ClntObjMgrObjectPtr(guid, 0xff) != NULL;
}

void WoW_Object::log() {
	log_info("Type: %s", object_type_str[type]);
	log_info("Guid: %llu", guid);
	log_info("Pointer: 0x%x\n", ptr);
}

void Object_Manager::populate_objects() {
	auto client_conn = read_memory<u8*>(CLIENT_CONNECTION_PTR);
	auto obj_mgr = read_memory<u8*>(client_conn + CURR_OBJECT_MANAGER);
	auto obj = read_memory<u8*>(obj_mgr + FIRST_OBJECT);

	while (obj && ((u64)obj & 1) == 0) {
		auto type = read_memory<Object_Type>(obj + OBJECT_TYPE);
		auto guid = read_memory<u64>(read_memory<u8*>(obj + OBJECT_DESCRIPTOR) + OBJECT_FIELD_GUID);
		switch (type) {
		case OBJECT_TYPE_ITEM:
			WoW_Item item;
			item.init(obj, guid, type);
			items[guid] = item;
			break;
		case OBJECT_TYPE_CONTAINER:
			WoW_Container container;
			container.init(obj, guid, type);
			items[guid] = container;
			break;
		case OBJECT_TYPE_UNIT:
			WoW_Unit unit;
			unit.init(obj, guid, type);
			units[guid] = unit;
			break;
		case OBJECT_TYPE_PLAYER:
			WoW_Player player;
			player.init(obj, guid, type);
			players[guid] = player;
			break;
		case OBJECT_TYPE_GAMEOBJECT:
			WoW_GameObject gameobject;
			gameobject.init(obj, guid, type);
			game_objs[guid] = gameobject;
			break;
		case OBJECT_TYPE_DYNAMICOBJECT:
			WoW_DynamicObject dyn_obj;
			dyn_obj.init(obj, guid, type);
			dyn_objs[guid] = dyn_obj;
			break;
		case OBJECT_TYPE_CORPSE:
			WoW_Corpse corpse;
			corpse.init(obj, guid, type);
			corpses[guid] = corpse;
			break;
		}
		obj = read_memory<u8*>(obj + NEXT_OBJECT);
	}
}

void Object_Manager::log() {
	for (auto it : items)      it.second.log();
	for (auto it : containers) it.second.log();
	for (auto it : units)      it.second.log();
	for (auto it : game_objs)  it.second.log();
	for (auto it : dyn_objs)   it.second.log();
	for (auto it : corpses)    it.second.log();
	for (auto it : players)    it.second.log();
}