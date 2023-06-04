#include "wow_fun.h"
#include "offsets.h"

i32 wow_wrapper_get_spell_id_by_name(const char *spell_name) {
	static u64 unknown;
	typedef i32 (__cdecl *_fun)(const char *name, void *unknown);
	_fun fun = (_fun) GETSPELLIDBYNAME_FUN_PTR;
	return fun(spell_name, &unknown);
}

void wow_wrapper_cast_spell(i32 spell_id) {
	typedef struct {
		i32 unknown1;
		i32 unknown2;
		i32 unknown3;
		i32 unknown4;
	} CastParameters;
	typedef i32 (*_fun2)(i32 spell_id, CastParameters param, void *item, WoW_Guid guid);
	_fun2 cast = (_fun2) SPELL_C_CASTSPELL_FUN_PTR;

	static CastParameters zeroed_parameters;
	cast(spell_id, zeroed_parameters, NULL, 0);
}

void wow_wrapper_gameobject_interact(WoW_GameObject *game_object) {
	typedef int (__fastcall *_fun)(WoW_GameObject *thiss);
	_fun fun = (_fun) CGGAMEOBJECT_C__ONRIGHTCLICK_FUN_PTR;
	fun(game_object);
}

void *wow_wrapper_object_get_pointer(WoW_Guid guid) {
	typedef void *(__cdecl *_fun)(WoW_Guid guid, u32 flag);
	_fun fun = (_fun) CLNTOBJMGROBJECTPTR_FUN_PTR;
	return fun(guid, 0xFF);
}

void wow_cast_spell_by_name(const char *spell_name) {
	i32 spell_id = wow_wrapper_get_spell_id_by_name(spell_name);
	wow_wrapper_cast_spell(spell_id);
}
