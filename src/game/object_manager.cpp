#include <stdint.h>
#include <stdio.h> // remove it

#include "functions.hpp"
#include "../memory_manager.hpp"
#include "objects/object.hpp"
#include "objects/unit.hpp"
#include "enums/object_type.hpp"
#include "object_manager.hpp"

int __fastcall enumerate_objects_callback(void *base_pointer, int filter, uint64_t guid) {
    const uint32_t object_type_offset = 0x14;
    uint32_t base_addr = get_object_ptr(guid);
    auto type = (ObjectType) read_uint32(base_addr + object_type_offset);
    
    switch (type) {
        case Unit:
            UnitObject unit = UnitObject(guid, base_addr, type);
            unit.log_info();
            break;
    }

    return 1;
}

void ObjectManager::populate_list() {
    enumerate_visible_objects(enumerate_objects_callback);
}

void ObjectManager::log_objects() {
    for (WowObject object : object_list) {
        object.log_info();
    }
}
