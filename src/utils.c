#include "utils.h"

void *xmalloc(u32 n_bytes) {
    void *ptr = malloc(n_bytes);
    if (!ptr) {
        fprintf(stderr, "xmalloc failed.");
        exit(-1);
    }
    return ptr;
}

void *xrealloc(void *ptr, u32 n_bytes) {
    ptr = realloc(ptr, n_bytes);
    if (!ptr) {
        fprintf(stderr, "xmalloc failed.");
        exit(-1);
    }
    return ptr;
}

void *buf__grow(void *ptr, u32 min_cap, u32 elem_size) {
    u32 new_cap = MAX(min_cap, buf_cap(ptr)*2+1);
    u32 new_size = offsetof(Buf_Hdr, a) + (new_cap * elem_size);

    Buf_Hdr *buf; 
    if (ptr) {
        buf = realloc(buf__hdr(ptr), new_size);
    } else {
        buf = malloc(new_size);
        buf->len = 0;
    }
    buf->cap = new_cap;

    return buf->a;
}

void buf_test() {
    int *buffer = NULL;
    assert(buf_len(buffer) == 0);
    assert(buf_cap(buffer) == 0);

    for (int i = 0; i < 1024; i++) {
        buf_push(buffer, i);
    }
    assert(buf_len(buffer) == 1024);

    for (int i = 0; i < 1024; i++) {
        assert(buffer[i] == i);
    }

    buf_clear(buffer);
    assert(buf_len(buffer) == 0);

    buf_free(buffer);
    assert(buf_cap(buffer) == 0);
}
