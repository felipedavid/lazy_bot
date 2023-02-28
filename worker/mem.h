#pragma once
#include "defs.h"

u32 read_u32(u32 addr);
u64 read_u64(u32 addr);

void mem_write(u8* dst, u8* src, u32 len);
