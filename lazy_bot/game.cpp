#include "game.h"

_enumerate_visible_entities Game::enumerate_visible_entities = 
    (_enumerate_visible_entities) 0x00468380;
_get_entity_ptr Game::get_entity_ptr = (_get_entity_ptr) 0x00464870;
_get_player_guid Game::get_player_guid = (_get_player_guid) 0x00468550;
_click_to_move Game::click_to_move = (_click_to_move) 0x00611130;
_run_lua Game::run_lua = (_run_lua) 0x00704CD0;
_set_target Game::set_target = (_set_target) 0x00493540;
_right_click_unit Game::right_click_unit = (_right_click_unit) 0x0060BEA0;
_get_item_cache_entry Game::get_item_cache_entry = (_get_item_cache_entry) 0x0055BA30;
_get_unit_type Game::get_unit_type = (_get_unit_type) 0x00605570;
_get_unit_reaction Game::get_unit_reaction = (_get_unit_reaction) 0x006061E0;
_get_spell_cooldown Game::get_spell_cooldown = (_get_spell_cooldown) 0x006E13E0;
_set_facing Game::set_facing = (_set_facing) 0x007C6F30;
_send_movement_update Game::send_movement_update = (_send_movement_update) 0x00600A30;

u32 Game::get_item_cache_entry_wrapper(u32 item_id) {
    u64 guid = 0;
    return get_item_cache_entry(0x00C0E2A0, item_id, (u32)&guid, 0, 0, 0);
}

bool Game::is_spell_ready(u32 spell_id) {
    const static u32 get_spell_cooldown_base = 0x00CECAEC;
    u32 cooldown = 0;
    get_spell_cooldown(get_spell_cooldown_base, get_spell_cooldown_base, spell_id, 0, &cooldown, 0, 0);
    return cooldown == 0;
}
