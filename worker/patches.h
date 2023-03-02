#pragma once
#include "defs.h"
#include "vector"

struct Patch {
	b32 enabled = false;
	u8 payload[64];
	u8 original[64];
	u8 *addr;
	size_t len;

	Patch(u8 *addr, u8* payload, size_t len);
	void enable();
	void disable();
};

struct Patch_Manager {
	std::vector<Patch> dev_patches; // patches to make the development easier

	Patch_Manager();
	void apply_dev_patches();
	void disable_dev_patches();
};
