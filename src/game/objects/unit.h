#ifndef UNIT
#define UNIT
#include <cstdint>

#include "object.h"

struct Unit : WowObject {
    static const uint32_t health_offset = 0x58;
    static const uint32_t mana_offset = 0x5C;
    static const uint32_t max_health_offset = 0x70;
    static const uint32_t max_mana_offset = 0x74;
    static const uint32_t name_offset = 0xB30;

    int get_health();
    int get_max_health();
    int get_health_percentage();
    int get_mana();
    int get_max_mana();
    int get_mana_percentage();
    virtual char *get_name();
    void log_info() override;
};
#endif
