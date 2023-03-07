#pragma once
#include <Windows.h>
#include "logger.h"
#include "defs.h"

template<typename T>
T read_memory(u8 *addr) {
	if (IsBadReadPtr((LPVOID)addr, 0)) {
		log_fatal("Trying to read from bad pointer: 0x%x", addr);
		return 0;
	}
	return *(T *)addr;
}

template<typename T>
void write_memory(u8 *addr, T val) {
	if (IsBadWritePtr((LPVOID)addr, 0)) {
		log_fatal("Trying to read to bad pointer: 0x%x", addr);
		return;
	}
	DWORD orig_protection, protection;
	VirtualProtect(addr, sizeof(T), PAGE_EXECUTE_READWRITE, &orig_protection);
	memcpy(addr, &val, sizeof(T));
	VirtualProtect(addr, sizeof(T), orig_protection, &protection);
}
