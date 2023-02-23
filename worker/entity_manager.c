#include "wow.h"
#include "mem.h"
#include "utils.h"
#include "offsets.h"
#include "entity_manager.h"

Entity *entity_list;

void log_entity_list() {
	Entity *el = entity_list;
	for (int i = 0; i < buf_len(el); i++) {
		ConsolePrintf("Addr: 0x%x, Guid: %llu, Type: %d lul", el[i].addr, el[i].guid, el[i].type);
	}
}

void populate_entity_list() {
	auto ent_mgr = read_u32(ENTITY_MANAGER_PTR);
	auto ent = read_u32(ent_mgr + FIRST_ENTITY);

	while (ent && ((ent & 1) == 0)) {
		Entity_Type type = read_u32(ent + ENTITY_TYPE);
		u64 guid = read_u32(ent + ENTITY_GUID);

		buf_push(entity_list, ((Entity){.guid = guid, .addr = ent, .type = type}));

		ent = read_u32(ent + NEXT_ENTITY);
	}
}
