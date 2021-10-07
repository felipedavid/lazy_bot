#pragma once
#include "type.h"
#include "entity_manager.h"
#include "menu.h"

extern Menu bot_menu;

template <typename T>
T read(u32 addr) { 
    return *(T*)addr; 
}

const char *entity_type_to_str(Entity_Type type);
void write_to_memory(char *dst, char *src, int size);
void run_procedure_on_main_thread(void* procedure);