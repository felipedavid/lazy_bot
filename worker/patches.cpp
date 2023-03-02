#include <string.h>
#include <assert.h>
#include "mem.h"
#include "patches.h"

Patch::Patch(u8 *addr, u8 *payload, size_t len) {
	assert(len <= 64);

	memcpy(this->payload, payload, len);
	this->len = len;
}

void Patch::enable() {
	if (enabled) return;

	memcpy(original, addr, len);
	mem_write(addr, payload, len);
	enabled = true;
}

void Patch::disable() {
	if (!enabled) return;

	mem_write(addr, original, len);
	enabled = false;
}

Patch_Manager::Patch_Manager() {
	u8 payload[] = { 0x45 };
	dev_patches.push_back(Patch((u8*)0x6571D1, payload, sizeof(payload)));
}

void Patch_Manager::apply_dev_patches() {
	for (auto p : dev_patches) {
		p.enable();
	}
}

void Patch_Manager::disable_dev_patches() {
	for (auto p : dev_patches) {
		p.disable();
	}
}