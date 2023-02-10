#include "logger.h"
#include "entity_manager.h"

Entity *entities;

void populate_entities() {
    buf_clear(entities);

    Entity ent;
    u32 client_conn = read_u32(CLIENT_CONNECTION);
    u32 entity_manager = read_u32(client_conn + ENTITY_MANAGER);
    ent.base_addr = read_u32(entity_manager + FIRST_ENTITY);
    ent.type = (Entity_Type) read_u32(ent.base_addr + ENT_TYPE);

    while (ent.base_addr && ((ent.base_addr & 1) == 0)) {
        buf_push(entities, ent);

        ent.base_addr = read_u32(ent.base_addr + NEXT_ENTITY);
        ent.type = (Entity_Type) read_u32(ent.base_addr + ENT_TYPE);
    }
}

const char *entity_type_str[] = {
    [ET_NONE]      = "None",
    [ET_ITEM]      = "Item",
    [ET_CONTAINER] = "Container",
    [ET_NPC]       = "NPC",
    [ET_PLAYER]    = "Player",
    [ET_GAME_OBJ]  = "GameObject",
    [ET_DYN_OBJ]   = "DynamicObject",
    [ET_CORPSE]    = "Corpse",
};

void log_entities() {
    populate_entities();
    for (int i = 0; i < buf_len(entities); i++) {
        Entity ent = entities[i];
        Entity_Type type = ent.type;

        log_info("Entity %d", i);
        log_info("Base addr: 0x%x", ent.base_addr);
        log_info("Type: %s\n", entity_type_str[type]);
    }
}
