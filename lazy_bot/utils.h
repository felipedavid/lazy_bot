#pragma once
#include "type.h"
#include "entity_manager.h"
#include "menu.h"

extern Menu bot_menu;

template <typename T>
T read(u32 addr) { 
    try {return *(T*)addr; } 
    catch (const char *e) {
        bot_menu.add_log(e);
    }
}

const char *entity_type_to_str(Entity_Type type);
