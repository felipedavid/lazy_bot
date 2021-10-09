#pragma once
#include "type.h"

// Needed as argument for "click_to_move" function
enum Click_Type {
    CT_MOVE = 0x4,
    CT_NONE = 0xD,
};

typedef void (__fastcall *_enumerate_visible_entities)(void *callback, int filter);
typedef u32 (__stdcall *_get_entity_ptr)(u64 guid);
typedef u64 (__stdcall *_get_player_guid)();
typedef void (__fastcall *_click_to_move)(u32 thiss, u32 player_ptr, u32 click_type, u64 *i_guid_ptr, u32 pos, float precision);
typedef void (__fastcall *_run_lua)(const char *lua_code, const char *whatever);
typedef void (__stdcall *_set_target)(u64 guid);
typedef void (__fastcall *_right_click_unit)(u32 unit_base_addr, u32 unit_base_addr2, u32 auto_loot);
typedef u32 (__fastcall *_get_item_cache_entry)(u32 base_ptr, u32 base_ptr2, u32 item_id, u64 *guid, u32 x, u32 y, u32 z); // base_ptr = 0x00C0E2A0

struct Game {
    static _enumerate_visible_entities enumerate_visible_entities;
    static _get_entity_ptr get_entity_ptr;
    static _get_player_guid get_player_guid;
    static _click_to_move click_to_move;
    static _run_lua run_lua;
    static _set_target set_target;
    static _right_click_unit right_click_unit;
    static _get_item_cache_entry get_item_cache_entry;
    static u32 get_item_cache_entry_wrapper(u32 item_id);
};
