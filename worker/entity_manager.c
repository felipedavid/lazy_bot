#include "wow.h"
#include "mem.h"
#include "utils.h"
#include "offsets.h"
#include "entity_manager.h"

Entity *entity_list;

const char *etype_str[] = {
	[ET_NONE]      = "None",
	[ET_ITEM]      = "Item",
	[ET_CONTAINER] = "Container",
	[ET_UNIT] 	   = "Unit",
	[ET_PLAYER]    = "Player",
	[ET_GAMEOBJ]   = "GameObject",
	[ET_DYNOBJ]    = "DynamicObject",
	[ET_CORPSE]    = "Corpse",
};

void log_entity_list() {
	for (int i = 0; i < buf_len(entity_list); i++) {
		Entity ent = entity_list[i];
		ConsolePrintf("Addr: 0x%x, Guid: %llu, Type: %s", ent, get_guid(ent), etype_str[get_type(ent)]);
	}
}

void populate_entity_list() {
	buf_clear(entity_list);

	u32 ent_mgr = read_u32(ENTITY_MANAGER_PTR);
	Entity ent = read_u32(ent_mgr + FIRST_ENTITY);

	while (ent && ((ent & 1) == 0)) {
		buf_push(entity_list, ent);
		ent = read_u32(ent + NEXT_ENTITY);
	}
}

u64 get_guid(Entity ent) {
	return read_u64(ent + ENTITY_GUID);
}

Entity_Type get_type(Entity ent) {
	return (Entity_Type) read_u32(ent + ENTITY_TYPE);
}
