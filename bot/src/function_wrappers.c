#include "function_wrappers.h"

void interact(Entity ent) {
    typedef int(__fastcall *interact_fun)(u32 thisptr);
    interact_fun _interact = (interact_fun) virtual_function(ent, INTERACT_INDEX);
    _interact(ent);
}

void cast_spell(u32 spell_id) {
    typedef char(__cdecl *cast_spell_fun)(u32 id, u32, u32, u32);
    cast_spell_fun _cast_spell = (cast_spell_fun) CAST_SPELL_FUN;
    _cast_spell(spell_id, 0, 0, 0);
}