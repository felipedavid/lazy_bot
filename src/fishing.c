#include "game_info.h"
#include "entity_manager.h"
#include "logger.h"
#include "function_wrappers.h"

extern Player local_player;
extern Game_Object *game_objs;

inline bool is_fishing_bobber(Game_Object obj) {
    assert(get_type(obj) == ET_GAME_OBJ);
    return get_display_id(obj) == DISPLAY_ID_FISHING_BOBBER;
}

inline bool is_bobber_splashing(Dynamic_Object bobber) {
    assert(is_fishing_bobber(bobber));
    u32 flags = read_u32(get_descriptor(bobber) + GAME_OBJ_FLAGS);
    return flags == 0x20;
}

typedef enum {
    STATE_CAST_FISHING,
    STATE_FIND_BOBBER,
    STATE_WAIT_SPLASH,
    STATE_LOOT,
} State;

void pulse() {
    static State state;
    static Entity bobber = 0;

    switch (state) {
    case STATE_CAST_FISHING:
        populate_entities();
        if (!is_casting(local_player, SPELL_ID_FISHING))
            cast_spell(SPELL_ID_FISHING);
        state = STATE_FIND_BOBBER;
        break;
    case STATE_FIND_BOBBER:
        populate_entities();
        for (int i = 0; i < buf_len(game_objs); i++) {
            Game_Object ent = game_objs[i];
            if (is_fishing_bobber(ent) && created_by(local_player, ent)) {
                bobber = ent;
                state = STATE_WAIT_SPLASH;
                return;
            }
        }
        state = STATE_CAST_FISHING;
        break;
    case STATE_WAIT_SPLASH:
        if (!is_casting(local_player, SPELL_ID_FISHING)) {
            state = STATE_CAST_FISHING;
            return;
        }

        if (is_bobber_splashing(bobber)) {
            state = STATE_LOOT;
        }
        break;
    case STATE_LOOT:
        interact(bobber);
        state = STATE_CAST_FISHING;
        break;
    }
}