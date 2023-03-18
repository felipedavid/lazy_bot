#pragma once
#include "object_manager.h"
#include "defs.h"

typedef struct {
	WoW_GameObject *pointer;
	WoW_Guid guid;
	b32 is_splashing;
	b32 is_valid;
} Bobber;

b32 fisher_bobber_tick();

typedef enum {
	FS_LURE,
	FS_CAST,
	FS_FISHING,
	FS_LOOT,
	FS_LOOTING,
} Fisher_State;

typedef struct {
	Object_Manager *object_manager;
	Fisher_State state;
	b32 is_fishing;
	Bobber bobber;
	WoW_Spell_ID fishing_spell_id;
	// Some states need a little more space between them,
	// since we are in the main thread we can't just call
	// Sleep(), so we just set the attribute 
	// "next_sleep_duration" to tell the code responsible
	// for execute the tick function on the main thread
	// to sleep for the right amount of time
	i32 next_sleep_duration;
} Fisher;

void fisher_init(Fisher *, Object_Manager *);
void fisher_tick(Fisher *);
void fisher_bobber_refresh(Fisher *);    
b32 fisher_is_casting_fishing(Fisher *);
void fisher_bobber_find(Fisher *fisher);
