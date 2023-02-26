#include "fishing.h" 
#include "utils.h"

extern Entity active_player;
extern Entity *entity_list;

typedef enum {
	CAST_FISHING,
	FIND_BOBBER,
	WAIT_SPLASH,
} State;

b32 is_my_fishing_bobber(Entity ent) {
	return (get_type(ent) == ET_GAMEOBJ) && 
		   (get_display_id(ent) == DISPLAY_ID_BOBBER) && 
		   (get_creator_guid(ent) == get_guid(active_player));
}

void try_to_loot(Entity ent) {

}

void fishing_pulse() {
	static State state = CAST_FISHING;
	static Entity my_bobber = 0;
	populate_entity_list();

	switch (state) {
	case CAST_FISHING:
		if (get_casting_spell(active_player) != FISHING) {
			wow_cast_spell(FISHING, 0);
		}
		state = FIND_BOBBER;
		break;
	case FIND_BOBBER:
		if (get_casting_spell(active_player) != FISHING) {
			state = CAST_FISHING;
			break;
		}
		for (int i = 0; i < buf_len(entity_list); i++) {
			Entity ent = entity_list[i];
			if (is_my_fishing_bobber(ent)) {
				my_bobber = ent;
				state = WAIT_SPLASH;
				return;
			}
		}
		state = CAST_FISHING;
		break;
	case WAIT_SPLASH:
		if (get_casting_spell(active_player) != FISHING) {
			state = CAST_FISHING;
			break;
		}

		//if (get_animation_id(my_bobber) == ANIMATION_ID_SPLASHING) {
		//	try_to_loot(my_bobber);
		//	state = CAST_FISHING;
		//}
		break;
	}
}
