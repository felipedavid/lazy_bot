#include "game_info.h"
#include "entity_manager.h"
#include "logger.h"

extern Player local_player;
extern Game_Object *game_objs;

bool created_by_local_player(Entity ent) {
    return get_creator_guid(ent) == get_guid(local_player);
}

inline bool is_fishing_bobber(Dynamic_Object obj) {
    return get_display_id(obj) == DISPLAY_ID_FISHING_BOBBER;
}

void pulse() {
    populate_entities();
    Game_Object bobber = 0;

    // Find player bobber
    for (int i = 0; i < buf_len(game_objs); i++) {
        if (is_fishing_bobber(game_objs[i]) && created_by_local_player(game_objs[i])) {
            log_info("Found bobber!");
            bobber = game_objs[i];
            break;
        }
    }
}