#include "logger.h"
#include "entity_manager.h"

Player local_player;
Game_Object *game_objs;

Entity_Type get_type(Entity ent) {
    return (Entity_Type) read_u32(ent + ENT_TYPE);
}

u32 get_descriptor(Entity ent) {
    return read_u32(ent + ENT_DESCRIPTOR);
}

u64 get_guid(Entity ent) {
    return read_u64(get_descriptor(ent));
}

i32 get_display_id(Entity ent) {
    return read_u32(get_descriptor(ent) + GAME_OBJ_DISPLAY_ID);
}

u64 get_creator_guid(Entity ent) {
    return read_u64(get_descriptor(ent) + GAME_OBJ_CREATED_BY);
}

bool is_casting(Unit unit, u32 spell_id) {
    return read_u32(unit + UNIT_CHANNEL_ID) == spell_id;
}

void populate_entities() {
    buf_clear(game_objs);

    Entity ent;
    u32 client_conn = read_u32(CLIENT_CONNECTION);
    u32 entity_manager = read_u32(client_conn + ENTITY_MANAGER);
    ent = read_u32(entity_manager + FIRST_ENTITY);

    while (ent && ((ent & 1) == 0)) {
        switch (get_type(ent)) {
        case ET_PLAYER:
            if (get_guid(ent) == read_u64(LOCAL_PLAYER_GUID)) {
                local_player = ent;
            }
            break;
        case ET_GAME_OBJ: buf_push(game_objs, ent); break;
        }

        ent = read_u32(ent + NEXT_ENTITY);
    }
}

const char *entity_type_str[] = {
    [ET_NONE]      = "None",
    [ET_ITEM]      = "Item",
    [ET_CONTAINER] = "Container",
    [ET_UNIT]       = "NPC",
    [ET_PLAYER]    = "Player",
    [ET_GAME_OBJ]  = "GameObject",
    [ET_DYN_OBJ]   = "DynamicObject",
    [ET_CORPSE]    = "Corpse",
};

void log_entities() {
    populate_entities();
    for (int i = 0; i < buf_len(game_objs); i++) {
        Entity ent = game_objs[i];

        log_info("Entity %d", i);
        log_info("Base addr: 0x%x", ent);
        log_info("Type: %s\n", entity_type_str[get_type(ent)]);
    }
}
