#pragma once

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;

typedef float f32;
typedef double f64;

typedef u32 bool;
#define true  1
#define false 0

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

#define read_u32(addr) (*(u32*)(addr))
#define read_u64(addr) (*(u64*)(addr))