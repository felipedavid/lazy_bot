#ifndef WOW_OBJECT
#define WOW_OBJECT
#include <stdint.h>
#include "../enums/object_type.hpp"

class WowObject {
    uint64_t guid;
    uint32_t pointer;
    ObjectType type;

public:
    WowObject(uint64_t obj_guid, uint32_t obj_pointer, ObjectType obj_type);
    void log_info();
    uint32_t get_pointer();
    uint64_t get_guid();
    ObjectType get_object_type();
};
#endif
