#pragma once
#include "common.h"
#include "entity_manager.h"

#define virtual_function(thisptr, index) ((*(u32**)thisptr)[index])

void interact(Entity ent);
void cast_spell(u32 spell_id);