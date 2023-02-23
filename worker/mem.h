#pragma once
#include "def.h"

void mem_write(void *dst, void *src, u32 len);

#define read_u32(addr) (*(u32 *)(addr))
#define read_u64(addr) (*(u64 *)(addr))
