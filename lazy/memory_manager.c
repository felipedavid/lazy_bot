#include <stdint.h>
#include <windows.h>

uint8_t read_byte(uint32_t addr) {
    return *(uint8_t *)addr;
}

uint32_t read_uint32(uint32_t addr) {
    return *(uint32_t *)addr;
}

uint64_t read_uint64(uint32_t addr) {
    return *(uint64_t *)addr;
}

float read_float(uint32_t addr) {
    return *(float *)addr;
}
