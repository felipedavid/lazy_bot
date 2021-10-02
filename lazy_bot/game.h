#pragma once
#include "type.h"

typedef void (__fastcall *_enumerate_visible_entities)(void *callback, int filter);
typedef u32 (__stdcall *_get_entity_ptr)(u64 guid);
typedef u64 (__stdcall *_get_player_guid)();

struct Game {
    static _enumerate_visible_entities enumerate_visible_entities;
    static _get_entity_ptr get_entity_ptr;
    static _get_player_guid get_player_guid;
};
