#pragma once
#include "defs.h"

#define read_u8(ptr)  (*(u8*)(ptr))
#define read_u16(ptr) (*(u16*)(ptr))
#define read_u32(ptr) (*(u32*)(ptr))
#define read_u64(ptr) (*(u64*)(ptr))

#define read_i8(ptr)  (*(i8*)(ptr))
#define read_i16(ptr) (*(i16*)(ptr))
#define read_i32(ptr) (*(i32*)(ptr))
#define read_i64(ptr) (*(i64*)(ptr))

#define read_f32(ptr) (*(f32*)(ptr))
#define read_f64(ptr) (*(f64*)(ptr))

#define read_pointer(ptr) (*(u8**)(ptr))

void mem_write(u8* dst, u8* src, size_t len);
