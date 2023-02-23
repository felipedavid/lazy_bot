#pragma once
#include <stddef.h>
#include <stdlib.h>

#include "def.h"

typedef struct {
	size_t len;
	size_t cap;
	u8 payload[0];
} Buf_Header;

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

#define buf__header(ptr) ((ptr) ? (Buf_Header*)((u8*)(ptr) - offsetof(Buf_Header, payload)) : 0)
#define buf__fits(ptr, n) ((buf_len(ptr) < buf_cap(ptr)) ? true : false)
#define buf__makefit(ptr, n) (buf__fits(ptr, n) ? 0 : ((ptr) = buf__grow(ptr, (buf_cap(ptr)+n), sizeof(*ptr))))

#define buf_len(ptr) ((ptr) ? buf__header(ptr)->len : 0)
#define buf_cap(ptr) ((ptr) ? buf__header(ptr)->cap : 0)

#define buf_push(ptr, x) (buf__makefit(ptr, 1), (ptr)[buf__header(ptr)->len++] = (x))
#define buf_free(ptr) ((ptr) ? free(buf__header(ptr)), (ptr) = NULL : 0)

void *buf__grow(void *ptr, size_t least_cap, size_t elem_size);
void buf_test();
