#pragma once
#include "object_manager.h"

enum Fisher_State {
	FISHER_STATE_NONE,
	FISHER_STATE_CAST_FISHING,
	FISHER_STATE_LOOK_FOR_BOBBER,
	FISHER_STATE_WAITING_SPLASH,
	FISHER_STATE_LOOTING,
};

struct Fisher {
	Fisher_State state = FISHER_STATE_NONE;
	bool on = false;

	void pulse();
	WoW_GameObject* find_our_bobber();
	bool is_splashing(WoW_GameObject* bobber);
};
