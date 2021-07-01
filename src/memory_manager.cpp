#include <cstdint>

uint32_t read_uint(uint32_t addr) {
    return *(uint32_t *) addr;
}

float read_float(uint32_t addr) {
    return *(float *) addr;
}

uint64_t read_uint64(uint32_t addr) {
    return *(uint64_t *) addr;
}
