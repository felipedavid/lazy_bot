#include "object_manager.h"
#include "offsets.h"
#include "mem.h"

WoW_Object::WoW_Object(u8 *ptr, u64 guid, Object_Type type) {
	this->descriptors_field = read_pointer(ptr + OBJECT_DESCRIPTOR);
	this->ptr = ptr;
	this->guid = guid;
	this->type = type;
}

u8* WoW_Object::get_descriptor() {
	return read_pointer(ptr + OBJECT_DESCRIPTOR);
}

WoW_GameObject::WoW_GameObject(u8* ptr, u64 guid, Object_Type type) : WoW_Object(ptr, guid, type) {

}

u64 WoW_GameObject::get_creator() {
	return read_u64(descriptors_field + GAMEOBJECT_CREATOR_GUID);
}

GameObject_DisplayID WoW_GameObject::get_display_id() {
	return (GameObject_DisplayID) read_u32(descriptors_field + GAMEOBJECT_DISPLAYID);
}

void Object_Manager::pulse() {
	auto connection = read_pointer(CLIENT_CONNECTION_PTR);
	auto obj_mgr = read_pointer(connection + CURR_OBJECT_MANAGER);
	auto obj_ptr = read_pointer(obj_mgr + FIRST_OBJECT);

	me.guid = read_u64(obj_mgr + LOCAL_PLAYER_GUID);

	while (obj_ptr && ((u32)obj_ptr & 1) == 0) {
		auto type = (Object_Type) read_u32(obj_ptr + OBJECT_TYPE);
		auto guid = read_u64(read_pointer(obj_ptr + OBJECT_DESCRIPTOR));

		switch (type) {
		case OBJECT_TYPE_GAMEOBJECT:
			game_objects.push_back(WoW_GameObject(obj_ptr, guid, type));
			break;
		case OBJECT_TYPE_PLAYER:
			if (guid == me.guid) {
				me.ptr = obj_ptr;
				me.descriptors_field = read_pointer(obj_ptr + OBJECT_DESCRIPTOR);
			}
			break;
		}
		obj_ptr = read_pointer(obj_ptr + NEXT_OBJECT);
	}
}