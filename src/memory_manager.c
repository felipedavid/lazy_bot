#include <stdint.h>
#include <windows.h>

uint8_t read_byte(uint32_t addr) {
    return *(uint8_t *)addr;
}

uint32_t read_dword(uint32_t addr) {
    return *(uint32_t *)addr;
}

uint64_t read_qword(uint32_t addr) {
    return *(uint64_t *)addr;
}

float read_float(uint32_t addr) {
    return *(float *) addr;
}

void write_bytes(uint32_t addr_to_write, uint8_t bytes[], size_t n_bytes) {
     WriteProcessMemory(GetCurrentProcess(), 
                       (void *)addr_to_write, 
                       (void*)bytes, 
                       n_bytes, 
                       NULL);
}
