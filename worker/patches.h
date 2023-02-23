#pragma once
#include "def.h"

typedef struct {
	u32 addr;
	u32 len;
	u8 *payload;
	u8 *original;
	b32 applied;
} Patch;

void apply_patch(Patch *p);
void remove_patch(Patch *p);
void apply_essential_patches();
void remove_essential_patches();
