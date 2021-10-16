#pragma once
#include "type.h"
#include "entity_manager.h"

template <typename T>
T read(u32 addr) { 
    return *(T*)addr; 
}

const char *entity_type_to_str(Entity_Type type);
const char *get_spell_name(u32 spell_id);
void write_to_memory(u8 *dst, u8 *src, int size);
void run_procedure_on_main_thread(void* procedure);
