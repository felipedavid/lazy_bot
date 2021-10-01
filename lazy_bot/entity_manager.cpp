#include <cstdio>

#include "utils.h"

#include "entity_manager.h"

Entity::Entity(u32 base_addr) {
    this->base_addr = base_addr;
}

u64 Entity::get_guid() { 
    return read<u64>(base_addr + guid_offset); 
}

Entity_Type Entity::get_type() { 
    return read<Entity_Type>(base_addr + type_offset); 
}

u32 Unit::get_descriptor_ptr() {
    return read<u32>(base_addr + descriptor_ptr_offset);
}

int Unit::get_health() {
    return read<int>(get_descriptor_ptr() + health_offset);
}

char *Unit::get_name() {
    return (char *) read<u32>(read<u32>(base_addr + name_offset));
}

Position Unit::get_position() {
    Position pos;
    pos.x = read<f32>(base_addr + 0x9B8);
    pos.y = read<f32>(base_addr + 0x9B8 + 0x4);
    pos.z = read<f32>(base_addr + 0x9B8 + 0x8);
    return pos;
}

char *Player::get_name() {
    u32 name_ptr = read<u32>(name_base_offset); 
    for (;;) {
        u64 next_guid = read<u64>(name_ptr + next_name_offset);
        if (next_guid != get_guid()) {
            name_ptr = read<u32>(name_ptr);
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

    u32 current = read<u32>(read<u32>(read<u32>(client_connection_offset) + entity_manager_offset) + first_entity_offset);
    //u32 current = read<u32>(client_connection_offset) + entity_manager_offset;
    //current = read<u32>(current + first_entity_offset);
    u32 next = current;

    while (current != 0 && (current & 1) == 0) {
        auto guid = read<u64>(current + entity_guid_offset);
        auto type = read<Entity_Type>(current + entity_type_offset);
        switch (type) {
            case ET_UNIT: 
                units.insert({guid, Unit(current)}); 
                break;
            case ET_PLAYER: {
                //if (guid == local_player.get_guid()) {
                //    local_player.base_addr = current;
                //} else {
                    players.insert({guid, Player(current)});
                //}
            } break;
        }

        next = read<u32>(current + next_entity_offset);  
        if (current == next) break;
        current = next;  
    }
}
