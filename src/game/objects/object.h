#ifndef WOW_OBJECT
#define WOW_OBJECT
#include <cstdint>
#include "../../position.h"

struct WowObject {
    static const uint32_t guid_offset = 0x30;
    static const uint32_t type_offset = 0x14;
    static const uint32_t position_x_offset = 0x9B8;
    static const uint32_t descriptor_offset = 0x8;

    uint32_t base_addr;

    uint32_t get_descriptor_fields();
    Position get_position();
    void log_info();
};
#endif
