#include "game_info.h"
#include "entity_manager.h"
#include "logger.h"
#include "function_wrappers.h"

extern Player local_player;
extern Game_Object *game_objs;

inline bool created_by_local_player(Entity ent) {
    return get_creator_guid(ent) == get_guid(local_player);
}

inline bool is_fishing_bobber(Game_Object obj) {
    assert(get_type(obj) == ET_GAME_OBJ);
    return get_display_id(obj) == DISPLAY_ID_FISHING_BOBBER;
}

inline bool is_bobber_splashing(Dynamic_Object bobber) {
    assert(is_fishing_bobber(bobber));
    u32 flags = read_u32(get_descriptor(bobber) + GAME_OBJ_FLAGS);
    return flags == 0x20;
}

void pulse() {
    populate_entities();
    Game_Object bobber = 0;

    if (!is_casting(local_player, SPELL_ID_FISHING)) {
        cast_spell(SPELL_ID_FISHING);
    }

    // Find player bobber
    for (int i = 0; i < buf_len(game_objs); i++) {
        if (is_fishing_bobber(game_objs[i]) && created_by_local_player(game_objs[i])) {
            bobber = game_objs[i];
            if (is_bobber_splashing(bobber)) {
                interact(bobber);
                log_info("Looting...\n");
            }
            break;
        }
    }

}