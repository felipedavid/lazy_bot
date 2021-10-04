#pragma once
#include "type.h"

// Needed as argument for "click_to_move" function
enum Click_Type {
    CT_MOVE = 0x4,
};

typedef void (__fastcall *_enumerate_visible_entities)(void *callback, int filter);
typedef u32 (__stdcall *_get_entity_ptr)(u64 guid);
typedef u64 (__stdcall *_get_player_guid)();
typedef void (__fastcall *_click_to_move)(u32 thiss, u32 player_ptr, u32 click_type, u64 *i_guid_ptr, u32 pos, float precision);
typedef void (__fastcall *_run_lua)(const char *lua_code, const char *whatever);

struct Game {
    static _enumerate_visible_entities enumerate_visible_entities;
    static _get_entity_ptr get_entity_ptr;
    static _get_player_guid get_player_guid;
    static _click_to_move click_to_move;
    static _run_lua run_lua;
};
