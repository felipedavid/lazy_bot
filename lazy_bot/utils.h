#pragma once
#include "type.h"
#include "entity_manager.h"
#include "menu.h"

extern Menu bot_menu;

template <typename T>
T read(u32 addr) { 
    T value = (T) 0;
    try {
        value = *(T*)addr; 
    } catch (...) {
        char buf[256];
        sprintf_s(buf, "[!] Could not read value at 0x%x", addr);
        bot_menu.add_log(buf);
    }
    return value;
}

const char *entity_type_to_str(Entity_Type type);
