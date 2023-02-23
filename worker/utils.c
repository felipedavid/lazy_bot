#include "utils.h"

#include <assert.h>

void buf_test() {
	int *b = NULL;

	assert(buf_len(b) == 0);
	assert(buf_cap(b) == 0);

	enum { N = 1024 };
	for (int i = 0; i < N; i++) {
		buf_push(b, i);
	}
	assert(buf_len(b) == N);

	for (int i = 0; i < N; i++) {
		assert(b[i] == i);
	}

	buf_free(b);
	assert(buf_len(b) == 0);
	assert(buf_cap(b) == 0);
}

void *buf__grow(void *ptr, size_t least_cap, size_t elem_size) {
	size_t new_cap = MAX(least_cap, buf_cap(ptr)*2+1);
	size_t new_size = offsetof(Buf_Header, payload) + (new_cap * elem_size);

	Buf_Header *new_header = NULL;
	if (ptr) {
		new_header = realloc(buf__header(ptr), new_size);
	} else {
		new_header = malloc(new_size);
		new_header->len = 0;
	}
	new_header->cap = new_cap;
	
	return new_header->payload;
}
