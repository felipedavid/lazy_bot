#pragma once
#include "type.h"

typedef int (__fastcall *_enumerate_visible_entities)(void *callback, int filter);
typedef u32 (__fastcall *_get_entity_ptr)(u64 guid);

struct Game {
    static _enumerate_visible_entities enumerate_visible_entities;
    static _get_entity_ptr get_entity_ptr;
};
