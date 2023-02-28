#include "pch.h"
#include "object_manager.h"
#include "offsets.h"
#include "wow.h"
#include "defs.h"
#include "mem.h"

void populate_objs() {
	u32 connection = read_u32(CLIENT_CONNECTION_PTR);
	u32 obj_mgr = read_u32(connection + CURR_OBJ_MGR);
	u32 ptr = read_u32(obj_mgr + FIRST_OBJ);

	while (ptr && (ptr & 1) != 0) {
		Object_Type type = (Object_Type)read_u32(ptr + OBJ_TYPE);
		u64 guid = read_u64(ptr + OBJ_GUID);

		ConsolePrintf("Ptr: %d, Type: %d, GUID: %llu", ptr, type, guid);

		ptr = read_u32(ptr + NEXT_OBJ);
	}
}
