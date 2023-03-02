#include "object_manager.h"
#include "offsets.h"
#include "mem.h"

extern Active_Player *meg;

void WoW_Object::init(u8 *ptr) {
	this->descriptors_field = read_pointer(ptr + OBJECT_DESCRIPTOR);
	this->ptr = ptr;
	this->guid = guid;
	this->type = type;
}

u8* WoW_Object::get_descriptor() {
	return read_pointer(ptr + OBJECT_DESCRIPTOR);
}

bool WoW_Object::is_valid() {
	return WoW::ClntObjMgrObjectPtr(this->guid, 0xffff) == this->ptr;
}

u64 WoW_GameObject::get_creator() {
	return read_u64(descriptors_field + GAMEOBJECT_CREATOR_GUID);
}

u32 WoW_GameObject::get_flags() {
	return read_u32(descriptors_field + GAMEOBJECT_FLAGS);
}

int WoW_GameObject::interact() {
	return WoW::CGGameObject_C__OnRightClick(this->ptr);
}

GameObject_DisplayID WoW_GameObject::get_display_id() {
	return (GameObject_DisplayID) read_u32(descriptors_field + GAMEOBJECT_DISPLAYID);
}

bool WoW_Unit::is_casting(SpellID spell_id) {
	return get_channel_spell() == spell_id;
}

// Returns the id of the spell that is being casted
SpellID WoW_Unit::get_channel_spell() {
	return (SpellID)read_u32(descriptors_field + UNIT_CHANNEL_SPELL);
}

// Returns the guid of the object created by the currently casting spell
u64 WoW_Unit::get_channel_object() {
	return read_u64(descriptors_field + UNIT_FIELD_CHANNEL_OBJECT);
}

void Active_Player::cast_spell(SpellID id) {
	WoW::Spell_C_CastSpell(id, 0, 0, 0, 0, 0, 0, 0);
}

void Object_Manager::pulse() {
	auto connection = read_pointer(CLIENT_CONNECTION_PTR);
	auto obj_mgr = read_pointer(connection + CURR_OBJECT_MANAGER);
	auto obj_ptr = read_pointer(obj_mgr + FIRST_OBJECT);

	auto active_player_guid = read_u64(obj_mgr + LOCAL_PLAYER_GUID);

	while (obj_ptr && ((u32)obj_ptr & 1) == 0) {
		auto type = (Object_Type) read_u32(obj_ptr + OBJECT_TYPE);
		auto guid = read_u64(read_pointer(obj_ptr + OBJECT_DESCRIPTOR));

		switch (type) {
		case OBJECT_TYPE_GAMEOBJECT:
			WoW_GameObject game_object;
			game_object.init(obj_ptr);
			game_objects[guid] = game_object;
			break;
		case OBJECT_TYPE_PLAYER:
			if (guid == active_player_guid) {
				Active_Player me;
				me.init(obj_ptr);
				this->me = me;
			}
			break;
		}
		obj_ptr = read_pointer(obj_ptr + NEXT_OBJECT);
	}
}