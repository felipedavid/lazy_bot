#include "mem.h"
#include <windows.h>
#include <string.h>

void mem_write(u8 *dst, u8 *src, u32 len) {
	u32 old_protect, new_protect;

	VirtualProtect(dst, len, PAGE_EXECUTE_READWRITE, &old_protect);
	while (len--) *dst = *src;
	VirtualProtect(dst, len, old_protect, &new_protect);
}
