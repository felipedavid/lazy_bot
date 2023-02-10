#pragma once
#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct {
    u32 cap;
    u32 len;
    u8 a[0];
} Buf_Hdr;

#define buf__hdr(b) ((b) ? (Buf_Hdr*)(((u8*)(b))-offsetof(Buf_Hdr, a)) : 0)
#define buf__fits(b, n) ((buf_len(b) < buf_cap(b)))
#define buf__make__fit(b, n) (buf__fits(b, n) ? 0 : ((b) = buf__grow((b), buf_cap(b)+(n), sizeof(*(b)))))

#define buf_len(b) ((b) ? buf__hdr(b)->len : 0)
#define buf_cap(b) ((b) ? buf__hdr(b)->cap : 0)

#define buf_push(b, v) (buf__make__fit((b), 1), (b)[buf__hdr(b)->len++] = (v))
#define buf_free(b) ((b) ? free(b), (b) = NULL : 0)
#define buf_clear(b) ((b) ? buf__hdr(b)->len = 0 : 0)

void *xmalloc(u32 n_bytes);
void *xrealloc(void *ptr, u32 n_bytes);
void *buf__grow(void *ptr, u32 min_cap, u32 elem_size);
void buf_test();
