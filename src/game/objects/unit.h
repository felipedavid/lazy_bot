#ifndef UNIT
#define UNIT
#include <cstdint>

#include "object.h"

struct Unit : WowObject {
    static const uint32_t health_offset = 0x58;
    static const uint32_t name_offset = 0xB30;

    int get_health();
    char *get_name();
    void log_info() override;
};
#endif
