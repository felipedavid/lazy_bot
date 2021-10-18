#include <cstdio>

#define _USE_MATH_DEFINES

#include "utils.h"
#include "entity_manager.h"
#include "bot.h"
#include "math.h"

extern Bot bot;

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

int Unit::get_max_health() {
    return read<int>(get_descriptor_ptr() + max_health_offset);
}

int Unit::get_health_percentage() {
    return read<int>(get_health() / get_max_health() * 100);
}

int Unit::get_rage() {
    return read<int>(get_descriptor_ptr() + rage_offset) / 10;
}

char *Unit::get_name() {
    return (char *) read<u32>(read<u32>(base_addr + name_offset));
}

Vec3 Unit::get_position() {
    return read<Vec3>(base_addr + position_offset);
}

float Unit::get_facing_direction() {
    return read<float>(base_addr + facing_offset);
}

bool Unit::can_be_looted() {
    return get_health() == 0 && read<u32>(get_descriptor_ptr() + dynamic_flags_offset) == CAN_BE_LOOTED;
}

int Unit::get_level() {
    return read<int>(get_descriptor_ptr() + level_offset);
}

int Unit::get_mana() {
    return read<int>(get_descriptor_ptr() + mana_offset);
}

std::vector<u32> Unit::get_buff_ids() {
    std::vector<u32> buff_ids(10, 0);

    u32 current_buff_offset = buffs_base_offset;
    for (int i = 0; i < 10; i++) {
        u32 buff_id = read<u32>(get_descriptor_ptr() + current_buff_offset);
        if (buff_id == 0) break; 

        buff_ids[i] = buff_id;
        current_buff_offset += 4;
    }
    return buff_ids;
}

std::vector<u32> Unit::get_debuff_ids() {
    std::vector<u32> debuff_ids(16, 0);

    u32 current_debuff_offset = debuffs_base_offset;
    for (int i = 0; i < 16; i++) {
        u32 debuff_id = read<u32>(get_descriptor_ptr() + current_debuff_offset);
        if (debuff_id == 0) break;

        debuff_ids[i] = debuff_id;
        current_debuff_offset += 4;
    }
    return debuff_ids;
}

bool Unit::has_buff(const char *buff_name) {
    auto ids = get_buff_ids();
    for (auto id : ids) {
        if (id && !strcmp(buff_name, get_spell_name(id))) {
            return true;
        }
    }
    return false;
}

Creature_Type Unit::get_type() {
    return (Creature_Type) Game::get_unit_type(base_addr);
}

Creature_Reaction Unit::get_reaction(u32 player_ptr) {
    return (Creature_Reaction) Game::get_unit_reaction(base_addr, base_addr, player_ptr);
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

void Local_Player::click_to_stop() {
    u64 interact_guid_ptr = 0;
    Vec3 pos = get_position();
    Game::click_to_move(base_addr, base_addr, CT_NONE, &interact_guid_ptr, (u32)&pos, 2);
}

Unit Local_Player::select_closest_enemy(std::unordered_map <u64, Unit> *units) {
    Unit enemy = units->begin()->second;
    for (auto unit : *units) {
        auto type = unit.second.get_type();
        auto react = unit.second.get_reaction(base_addr);
        if (type != UT_CRITTER && type != UT_NOT_SPECIFIED && type != UT_TOTEM &&
            (react == CR_HOSTILE || react == CR_UNFRIENDLY || react == CR_NEUTRAL) &&
            (unit.second.get_health() > 0) && (distance_to(enemy.get_position()) >
            distance_to(unit.second.get_position()))) {
            enemy = unit.second;
        }
    }
    Game::set_target(enemy.get_guid());
    return enemy;
}

float Local_Player::distance_to(Vec3 pos) {
    Vec3 me_position = get_position();
    float delta_x = me_position.x - pos.x;
    float delta_y = me_position.y - pos.y;
    float delta_z = me_position.z - pos.z;

    return (float)sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
}

void Local_Player::cast_spell(const char *spell_name) {
    char lua_code[256];
    snprintf(lua_code, sizeof(lua_code), "CastSpellByName('%s')", spell_name);
    Game::run_lua(lua_code, "Nothing");
}

void Local_Player::set_target(u64 guid) {
    Game::set_target(guid);
}

u64 Local_Player::get_target_guid() {
    static const u32 target_offset = 0x40;
    return read<u64>(get_descriptor_ptr() + target_offset);
}

void Local_Player::refresh_spells() {
    spells.erase(spells.begin(), spells.end());
    for (u32 *s_id = (u32*) player_spells_base_addr, i = 0; *s_id != 0 && i < 1024; s_id++) {
        const char *name = get_spell_name(*s_id);
        spells[std::string(name)] = *s_id;
    }
}

// TODO: Properly check spells rank
bool Local_Player::is_spell_ready(const char *spell_name, int spell_rank) {
    if (spells.find(std::string(spell_name)) == spells.end()) return false;

    return Game::is_spell_ready(spells[spell_name]);
}

// Returns which the correct angle to face the specified position
// TODO: Apparently, that is something wrong with the math. Fix it.
float Local_Player::get_facing_for_position(Vec3 pos) {
    float target_x = pos.x;
    float player_x = get_position().x;
    float target_y = pos.y;
    float player_y = get_position().y;
    
    float atan2X = (player_x - target_x);
    float atan2Y = (player_y - target_y);
    
    double angle = atan2(atan2X, atan2Y);
    if( angle < 0.0f )
        angle += M_PI * 2.0f;
    else if(angle > M_PI * 2.0f )
        angle -= M_PI * 2.0f;
    return (float)angle;
}

bool Local_Player::is_facing(Vec3 pos) {
    return (get_facing_for_position(pos) - get_facing_direction()) < 0.3f;
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
