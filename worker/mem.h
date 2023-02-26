#pragma once
#include "def.h"

void mem_write(void *dst, void *src, u32 len);

#define read_u32(addr) (*(u32 *)(addr))
#define read_u64(addr) (*(u64 *)(addr))
#define read_pointer(addr) (*(u8 **)(addr))
#define write_u32(addr, x) (*(u32*)(addr) = (x))
#define write_f32(addr, x) (*(f32*)(addr) = (x))
