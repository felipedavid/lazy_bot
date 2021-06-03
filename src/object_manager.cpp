#include <stdio.h>

#include "object_manager.h"
#include "game_functions.h"
#include "object.h"
#include "stdint.h"
#include "memory_manager.h"

object_t objects[500];
size_t n_objects;

uint32_t __fastcall enumerate_objects_callback(void *thiss, uint32_t filter, uint64_t guid) {
    object_t object = {0};
    object.guid = guid;
    object.pointer = get_object_ptr(object.guid);
    object.type = get_object_type(object.pointer);

    if (object.type == Unit || object.type == Player) {
        objects[n_objects++] = object;
    }

    return 1;
}

void update_view() {
    // temporary
    n_objects = 0; 
    enumerate_visible_objects(enumerate_objects_callback);

    for (size_t i = 0; i < n_objects; i++) {
        printf("Object %u\n", i);
        printf("Guid: %lld\n", objects[i].guid);
        printf("Pointer: 0x%x\n", objects[i].pointer);
        printf("Type: 0x%x\n", objects[i].type);
        if (objects[i].type == Unit) {
            printf("Health %d\n", get_object_health(objects[i]));
            printf("Name %s\n", get_object_name(objects[i]));
        }
        printf("\n");
    }
}

object_type_t get_object_type(uint32_t object_ptr) {
    const uint32_t OBJECT_TYPE_OFFSET = 0x14;
    return (object_type_t) read_byte(object_ptr + OBJECT_TYPE_OFFSET);
}

char *get_object_name(object_t object) {
    const uint32_t NAME_OFFSET = 0xB30;
    char *name = NULL;

    switch (object.type) {
        case Unit: {
            uint32_t ptr = read_dword(object.pointer + 0xB30);
            name = (char *) read_dword(ptr);
            } break;
        default:
            break;
    }

    return name;
}

uint32_t get_object_health(object_t object) {
    const uint32_t DESCRIPTOR_OFFSET = 0x8;
    const uint32_t HEALTH_OFFSET     = 0x58;

    uint32_t health = 0;

    switch(object.type) {
        case Unit: {
            uint32_t descriptor_collection_addr = 
                read_dword(object.pointer + DESCRIPTOR_OFFSET);
            health = read_dword(descriptor_collection_addr + HEALTH_OFFSET);
            } break;
        default:
            break;
    }

    return health;
}
