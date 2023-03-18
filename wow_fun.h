#pragma once

#include "defs.h"
#include "wow_types.h"

void wow_wrapper_cast_spell(i32 spell_id);
void wow_wrapper_gameobject_interact(WoW_GameObject *);
void *wow_wrapper_object_get_pointer(WoW_Guid);
i32 wow_wrapper_get_spell_id_by_name(const char *);

void wow_cast_spell_by_name(const char *);
