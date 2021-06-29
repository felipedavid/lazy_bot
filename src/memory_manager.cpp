#include <stdint.h>

uint32_t read_uint32(uint32_t address) {
    return *(uint32_t *) address;
}

void write_uint32(uint32_t address, uint32_t value) {
    *(uint32_t*) address = value;
}

int32_t read_int32(uint32_t address) {
    return *(int32_t *) address;
}

float read_float(uint32_t address) {
    return *(float *) address;
}

void write_float(uint32_t address, float value) {
    *(float *) address = value;
}
