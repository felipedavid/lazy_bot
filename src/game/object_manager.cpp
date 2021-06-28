#include <stdint.h>

#include "functions.hpp"
#include "../memory_manager.hpp"
#include "objects/object.hpp"
#include "enums/object_type.hpp"
#include "object_manager.hpp"

int enumerate_objects_callback(int filter, uint64_t guid) {
    const uint32_t object_type_offset = 0x14;
    uint32_t pointer = get_object_ptr(guid);
    ObjectType type = (ObjectType) read_uint32(pointer + object_type_offset);
    
    WowObject *object = new WowObject(guid, pointer, type);
    //object_list.push_back(*object);
    object->log_info();
    delete object;

    return 1;
}

void ObjectManager::populate_list() {
    enumerate_visible_objects(enumerate_objects_callback);
}

void ObjectManager::log_objects() {
    for (WowObject object : this->object_list) {
        object.log_info();
    }
}
