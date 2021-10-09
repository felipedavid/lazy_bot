#include "utils.h"

void unlock_lua() {
    u8 patch[] = { 0xB8, 0x01, 0x00, 0x00, 0x00, 0xc3 };
    write_to_memory((u8*)0x494A50, (u8*)patch, 6);
}
