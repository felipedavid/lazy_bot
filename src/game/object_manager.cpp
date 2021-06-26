#include <stdint.h>

#include "object_manager.hpp"
#include "functions.hpp"

ObjectManager::callback(int filter, uint64_t guid) {
    const uint32_t object_type_offset = 0x14;
    uint32_t pointer = get_object_pointer(guid);
    auto type = read_memory<ObjectType>(pointer + object_type_offset);
    
    WowObject *object = new WowObject(guid, pointer, type);
    this->object_list.push_back(*object);

    return 1;
}

ObjectManager::populate_lists() {
    enumerate_visible_objects(this->callback);
}

ObjectManager::log_objects() {
    for (WowObject object : this->object_list) {
        object.log_object_info();
    }
}
