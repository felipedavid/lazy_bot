#include "entity_manager.h"

#include "utils.h"

Entity::Entity(u32 base_addr) {
    this->base_addr = base_addr;
}

u64 Entity::get_guid() { 
    return read_u64(base_addr + guid_offset); 
}

Entity_Type Entity::get_type() { 
    return (Entity_Type) read_u32(base_addr + type_offset); 
}

u32 Unit::get_descriptor_ptr() {
    return read_u32(base_addr + descriptor_ptr_offset);
}

int Unit::get_health() {
    return read_int(get_descriptor_ptr() + health_offset);
}

char *Unit::get_name() {
    return (char *) read_u32(read_u32(base_addr + name_offset));
}

char *Player::get_name() {
    u32 name_ptr = read_u32(name_base_offset); 
    for (;;) {
        u64 next_guid = read_u64(name_ptr + next_name_offset);
        if (next_guid != get_guid()) {
            name_ptr = read_u32(name_ptr);
        } else {
            break;
        }
    }
    return (char *) name_ptr + player_name_offset;
}

void Entity_Manager::populate_lists() {
    units.erase(units.begin(), units.end());
    players.erase(players.begin(), players.end());

    // Get a pointer to the first entity of the linked list
    u32 current = read_u32(read_u32(entity_manager_addr) + first_entity_offset);
    u32 next;
    // Iterate over the linked list and populate our entity vectors
    while (current != 0 && (current & 1) == 0) {
        
        auto entity_type = (Entity_Type) read_u32(current + entity_type_offset);
        switch (entity_type) {
            case ET_UNIT: units.push_back(Unit(current)); break;
            case ET_PLAYER: {
                u64 player_guid = read_u64(current + entity_guid_offset);
                if (player_guid == local_player_guid) {
                    local_player.base_addr = current;
                } else {
                    players.push_back(Player(current));
                }
            } break;
        }

        next = read_u32(current + next_entity_offset);
        if (next == current) break;
        current = next;
    }
}
