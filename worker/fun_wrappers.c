#include "wow.h"
#include "fun_wrappers.h"

void wow_cast_spell(u32 spell_id, u32 target_guid) {
	Spell_C_CastSpell(spell_id, 0, 0, target_guid);
}
