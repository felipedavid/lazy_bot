#include <cstdio>

#include "utils.h"
#include "entity_manager.h"

std::unordered_map<u64, Unit> Entity_Manager::units;
std::unordered_map<u64, Player> Entity_Manager::players;
Local_Player Entity_Manager::local_player = 0;

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

Vec3 Unit::get_position() {
    return read<Vec3>(base_addr + position_offset);
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
u64 Local_Player::get_guid() { return Game::get_player_guid(); }

// Wrapper around game function
void Local_Player::click_to_move(Vec3 pos) {
    // 0x4 == move click type
    u64 interact_guid_ptr = 0;
    Vec3 *p = &pos;
    Game::click_to_move(base_addr, base_addr, CT_MOVE, &interact_guid_ptr, (u32)p, 2);
}


float Local_Player::distance_to(Vec3 pos) {
    Vec3 me_position = get_position();
    float delta_x = me_position.x - pos.x;
    float delta_y = me_position.y - pos.y;
    float delta_z = me_position.z - pos.z;

    return (float)sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
}

// Callback for "Game::enumarate_visible_entities"
int Entity_Manager::process_entity(void *thiss, int filter, u64 guid) {
    u32 base_addr = Game::get_entity_ptr(guid);
    auto type = read<Entity_Type>(base_addr + entity_type_offset);

    switch(type) {
        case ET_UNIT: units.insert({guid, base_addr}); break;
        case ET_PLAYER: {
            if (guid == local_player.get_guid()) { 
                local_player.base_addr = base_addr;
            } else {
                players.insert({guid, base_addr});
            }
        } break;
    }

    return 1;
}

void Entity_Manager::populate_lists() {
    units.erase(units.begin(), units.end());
    players.erase(players.begin(), players.end());

    Game::enumerate_visible_entities(process_entity, 0);
}
