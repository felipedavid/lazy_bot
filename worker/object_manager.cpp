#include "object_manager.h"
#include "offsets.h"
#include "mem.h"

void Object_Manager::refresh() {
	len = 0;

	auto connection = read_pointer(CLIENT_CONNECTION_PTR);
	auto obj_mgr = read_pointer(connection + CURR_OBJECT_MANAGER);
	auto obj_ptr = read_pointer(obj_mgr + FIRST_OBJECT);

	WoW_Object obj;
	while (obj_ptr && (obj_ptr & 1) == 0) {
		obj.ptr = obj_ptr;
		obj.guid = read_u64(obj_ptr + OBJECT_GUID);
		obj.type = (Object_Type) read_i32(obj_ptr + OBJECT_TYPE);
		objs[len++] = obj;

		obj_ptr = read_pointer(obj_ptr + NEXT_OBJECT);
	}
}