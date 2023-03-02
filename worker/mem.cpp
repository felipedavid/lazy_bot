#include <Windows.h>
#include "mem.h"

void mem_write(u8 *dst, u8 *src, size_t len) {
	DWORD old_protect, new_protect;

	VirtualProtect(dst, len, PAGE_EXECUTE_READWRITE, &old_protect);
	while (len--) *dst = *src;
	VirtualProtect(dst, len, old_protect, &new_protect);
}
