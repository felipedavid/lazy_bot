#include <windows.h>
#include <stdint.h>

#include "memory_manager.h"

void unlock_lua() {
    const uint32_t lua_unlock_addr = 0x494A50; 
    uint8_t bytes[] = { 0xB8, 0x01, 0x00, 0x00, 0x00, 0xc3 };
    write_bytes(lua_unlock_addr, bytes, sizeof(bytes));
}
