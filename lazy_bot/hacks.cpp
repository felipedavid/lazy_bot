#include "utils.h"

void unlock_lua() {
    char patch[] = { 0xB8, 0x01, 0x00, 0x00, 0x00, 0xc3 };
    write_to_memory((char *)0x494A50, (char *)patch, 6);
}
