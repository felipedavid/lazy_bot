#include "utils.h"

u32 read_u32(u32 addr) { return *(u32*)addr; }
u64 read_u64(u32 addr) { return *(u64*)addr; }
