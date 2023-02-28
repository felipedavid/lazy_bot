#include "pch.h"
#include "mem.h"

u32 read_u32(u32 addr) {
	if (IsBadReadPtr((void*)addr, 4)) {
		__debugbreak();
		return 0xdeadbeef;
	}
	return *(u32*)addr;
}

u64 read_u64(u32 addr) {
	if (IsBadReadPtr((void*)addr, 8) || IsBadWritePtr((void*)addr, 8)) {
		__debugbreak();
		return 0xdeaddeadbeefbeef;
	}
	return *(u64*)addr;
}

void mem_write(u8 *dst, u8 *src, u32 len) {
	DWORD old_protect, new_protect;
	VirtualProtect(dst, len, PAGE_EXECUTE_READWRITE, &old_protect);
	while (len--) *dst = *src;
	VirtualProtect(dst, len, old_protect, &new_protect);
}