#include "fisher.h"
#include "wow.h"

extern Object_Manager obj_mgr;

WoW_GameObject* Fisher::find_our_bobber() {
	auto me = &obj_mgr.me;
	if (!me->is_casting(SPELLID_FISHING)) {
		return NULL;
	}

	u64 bobber_guid = me->get_channel_object();
	if (!bobber_guid) {
		return NULL;
	}

	auto it = obj_mgr.game_objects.find(bobber_guid);
	if (it != obj_mgr.game_objects.end()) {
		auto bobber = it->second;
		return &bobber;
	}

	return NULL;
}

bool Fisher::is_splashing(WoW_GameObject* bobber) {
	return (bobber->get_flags() & GO_FLAG_NODESPAWN) != 0;
}

void Fisher::pulse() {
	obj_mgr.pulse();
	static Active_Player *me = &obj_mgr.me;
	static WoW_GameObject *bobber = NULL;

	switch (state) {
	case FISHER_STATE_NONE:
		// Check if it's possible to cast fishing
		state = FISHER_STATE_CAST_FISHING;
		break;
	case FISHER_STATE_CAST_FISHING:
		if (!me->is_casting(SPELLID_FISHING)) {
			me->cast_spell(SPELLID_FISHING);
		}
		state = FISHER_STATE_LOOK_FOR_BOBBER;
		break;
	case FISHER_STATE_LOOK_FOR_BOBBER:
		bobber = find_our_bobber();
		if (!bobber) {
			state = FISHER_STATE_CAST_FISHING;
		} else {
			state = FISHER_STATE_WAITING_SPLASH;
		}
		break;
	case FISHER_STATE_WAITING_SPLASH:
		if (!bobber->is_valid()) {
			state = FISHER_STATE_CAST_FISHING;
			break;
		}

		if (is_splashing(bobber)) {
			state = FISHER_STATE_LOOTING;
		}
		break;
	case FISHER_STATE_LOOTING:
		if (!bobber->is_valid()) {
			state = FISHER_STATE_CAST_FISHING;
			break;
		}
		bobber->interact();
		state = FISHER_STATE_NONE;
		break;
	}
}