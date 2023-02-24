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
		ConsolePrintf("Addr: 0x%x, Guid: %llu, Type: %s", ent.addr, ent.guid, etype_str[ent.type]);
	}
}

void populate_entity_list() {
	buf_clear(entity_list);
	auto ent_mgr = read_u32(ENTITY_MANAGER_PTR);
	auto ent = read_u32(ent_mgr + FIRST_ENTITY);

	while (ent && ((ent & 1) == 0)) {
		Entity_Type type = read_u32(ent + ENTITY_TYPE);
		u64 guid = read_u32(ent + ENTITY_GUID);

		buf_push(entity_list, ((Entity){guid, ent, type}));

		ent = read_u32(ent + NEXT_ENTITY);
	}
}
