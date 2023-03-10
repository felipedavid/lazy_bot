#include "pch.h"
#include "offsets.h"
#include "memory.h"
#include "wow.h"
#include "object_manager.h"
#include "logger.h"

const char* object_type_str[] = {
	"None",
	"Item",
	"Container",
	"Unit",
	"Player",
	"GameObject",
	"DynamicObject",
	"Corpse",
};

void WoW_Object::init(u8* ptr, u64 guid, Object_Type type) {
	this->ptr = ptr;
	this->guid = guid;
	this->type = type;
	this->descriptors = read_memory<u8*>(ptr + OBJECT_DESCRIPTOR);
	this->valid = true;
}

b32 WoW_Object::is_valid() {
	return WoW::ClntObjMgrObjectPtr(guid, 0xff) != NULL;
}

void WoW_Object::log() {
	log_info("Type: %s", object_type_str[type]);
	log_info("Guid: %llu", guid);
	log_info("Pointer: 0x%x\n", ptr);
	WoW::ConsoleWrite(" ", 0);
}

void WoW_GameObject::pulse() {
	valid = is_valid();
}

void WoW_DynamicObject::pulse() {
}

void WoW_Unit::log() {
	log_info("Type: %s", object_type_str[type]);
	log_info("Guid: %llu", guid);
	log_info("Pointer: 0x%x", ptr);
	log_info("Position: X=%f Y=%f Z=%f", position.x, position.y, position.z);
	WoW::ConsoleWrite(" ", 0);
}

void WoW_Unit::pulse() {
	valid = is_valid();
	if (!valid) return;

	position = read_memory<Vec3>(ptr + UNIT_POSITION);
}

void WoW_Corpse::pulse() {
}

void Object_Manager::populate_objects() {
	items.clear();
	containers.clear();
	units.clear();
	game_objs.clear();
	dyn_objs.clear();
	corpses.clear();
	players.clear();

	auto local_player_guid = read_memory<u64>(LOCAL_PLAYER_GUID_GLOBAL);
	if (local_player_guid == 0) {
		log_fatal("There is no object manager yet, please log in.");
		return;
	}

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
			unit.pulse();
			units[guid] = unit;
			break;
		case OBJECT_TYPE_PLAYER:
			if (guid == local_player_guid) {
				local_player.init(obj, guid, type);
				local_player.pulse();
			} else {
				WoW_Player player;
				player.init(obj, guid, type);
				player.pulse();
				players[guid] = player;
			}
			break;
		case OBJECT_TYPE_GAMEOBJECT:
			WoW_GameObject gameobject;
			gameobject.init(obj, guid, type);
			gameobject.pulse();
			game_objs[guid] = gameobject;
			break;
		case OBJECT_TYPE_DYNAMICOBJECT:
			WoW_DynamicObject dyn_obj;
			dyn_obj.init(obj, guid, type);
			dyn_obj.pulse();
			dyn_objs[guid] = dyn_obj;
			break;
		case OBJECT_TYPE_CORPSE:
			WoW_Corpse corpse;
			corpse.init(obj, guid, type);
			corpse.pulse();
			corpses[guid] = corpse;
			break;
		}
		obj = read_memory<u8*>(obj + NEXT_OBJECT);
	}
}

void Object_Manager::pulse() {
	for (auto it = game_objs.begin(); it != game_objs.end(); ++it) it->second.pulse();
	for (auto it = dyn_objs.begin(); it != dyn_objs.end(); ++it) it->second.pulse();
	for (auto it = units.begin(); it != units.end(); ++it) it->second.pulse();
	for (auto it = corpses.begin(); it != corpses.end(); ++it) it->second.pulse();
	local_player.pulse();
}

void Object_Manager::log() {
	for (auto it : items)      it.second.log();
	for (auto it : containers) it.second.log();
	for (auto it : game_objs)  it.second.log();
	for (auto it : dyn_objs)   it.second.log();
	for (auto it : units)      it.second.log();
	for (auto it : corpses)    it.second.log();
	for (auto it : players)    it.second.log();

	auto local_player_guid = read_memory<u64>(LOCAL_PLAYER_GUID_GLOBAL);
	if (local_player_guid) {
		local_player.log();
	}
}
