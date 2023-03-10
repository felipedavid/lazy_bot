#pragma once
#include <type_traits>
#include <Windows.h>
#include "logger.h"
#include "defs.h"

template<typename T>
T read_memory(u8 *addr) {
	if (IsBadReadPtr((LPVOID)addr, sizeof(T))) {
		log_fatal("Trying to read from bad pointer: 0x%x", addr);
		if constexpr (std::is_same<T, u8*>::value) {
			return (u8*)-1;
		}
		return T{};
	}
	return *(T *)addr;
}

template<typename T>
void write_memory(u8 *addr, T val) {
	DWORD orig_protection, protection;
	VirtualProtect(addr, sizeof(T), PAGE_EXECUTE_READWRITE, &orig_protection);
	if (IsBadWritePtr((LPVOID)addr, sizeof(T))) {
		log_fatal("Trying to write to bad pointer: 0x%x", addr);
		VirtualProtect(addr, sizeof(T), orig_protection, &protection);
		return;
	}
	memcpy(addr, &val, sizeof(T));
	VirtualProtect(addr, sizeof(T), orig_protection, &protection);
}
