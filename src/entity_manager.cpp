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

Position Unit::get_position() {
    Position pos;
    pos.x = read_float(base_addr + 0x9B8);
    pos.y = read_float(base_addr + 0x9B8 + 0x4);
    pos.z = read_float(base_addr + 0x9B8 + 0x8);
    return pos;
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

// Just a wrapper for a client's function that returns the local player guid.
// If the player is not logged in, zero is returned.
u64 Local_Player::get_guid() {
    return ((u64 (__stdcall*)())(get_player_guid_fun_ptr))();
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
                if (player_guid == local_player.get_guid()) {
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
