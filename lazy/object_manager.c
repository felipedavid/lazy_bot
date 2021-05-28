#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "memory_manager.h"
#include "game_functions.h"
#include "object_manager.h"
#include "object.h"

int n_units;
object_t local_player = {0};
object_t closest_unit = {0};

float local_player_distance_from_position(position_t position) {
    int delta_x = local_player.position.x - position.x;
    int delta_y = local_player.position.y - position.y;
    int delta_z = local_player.position.z - position.z;

    return (float) sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
}

// Units have their details stored in a different memory location
uint32_t get_object_descriptor_addr(object_t *object) {
    static const uint32_t DESCRIPTOR_OFFSET = 0x8;
    return read_uint32(object->pointer + DESCRIPTOR_OFFSET);
}

// The player its a type of unit, so this functions will also work with the
// player object
void set_unit_position(object_t *object) {
    static const uint32_t POS_X_OFFSET = 0x9B8;
    static const uint32_t POS_Y_OFFSET = 0x9BC;
    static const uint32_t POS_Z_OFFSET = 0x9C0;

    position_t *pos = &(object->position);
    pos->x = read_float(object->pointer + POS_X_OFFSET);
    pos->y = read_float(object->pointer + POS_Y_OFFSET);
    pos->z = read_float(object->pointer + POS_Z_OFFSET);
}

void set_unit_name_ptr(object_t *object) {
    static const uint32_t UNIT_NAME_OFFSET = 0xB30;
    object->name_ptr = (char *)read_uint32(read_uint32(object->pointer + UNIT_NAME_OFFSET));
}

// The players name is stored differently from other units
void set_player_name_ptr(object_t *object) {
    static const uint32_t NAME_BASE_OFFSET   = 0xC0E230;
    static const uint32_t NEXT_NAME_OFFSET   = 0xC;
    static const uint32_t PLAYER_NAME_OFFSET = 0x14;

    uint32_t name_ptr = read_uint32(NAME_BASE_OFFSET);
    while (true)
    {
        uint64_t next_guid = read_uint64(name_ptr + NEXT_NAME_OFFSET);

        if (next_guid != object->guid) {
            name_ptr = read_uint32(name_ptr);
        } else {
            break;
        }
    }
    object->name_ptr = (char *)(name_ptr + PLAYER_NAME_OFFSET);
}

int32_t __fastcall objects_callback(void *thiscall_garbage, uint32_t filter, uint64_t guid) {

    static const uint32_t OBJECT_TYPE_OFFSET = 0x14;
    static const uint32_t UNIT_HEALTH_OFFSET = 0x58;

    object_t object = {0};
    object.guid = guid;
    object.pointer = game_get_object_ptr(guid);
    object.type = 
        (object_type_t) read_byte(object.pointer + OBJECT_TYPE_OFFSET);

    if (object.type == Unit || object.type == Player) {
        uint32_t object_descriptor_addr = get_object_descriptor_addr(&object);
        object.health = read_uint32(object_descriptor_addr + UNIT_HEALTH_OFFSET);
        set_unit_position(&object);
    }

    if (object.type == Unit && object.health > 0) {
        set_unit_name_ptr(&object);
        object.distance_from_local_player = 
            local_player_distance_from_position(object.position);
        if (n_units == 0) {
            closest_unit = object;
        } else if (object.distance_from_local_player <
                   closest_unit.distance_from_local_player) {
            closest_unit = object;
        }
        n_units++;
    } else if (object.type == Player) {
        set_player_name_ptr(&object);
        if (object.guid == game_get_player_guid()) {
            local_player = object;
        }
    }

    return 1;
}

const char *object_type_code_to_string(object_type_t object_type) {
    switch (object_type) {
        case None:          return "None";
        case Item:          return "Item";
        case Container:     return "Container";
        case Unit:          return "Unit";
        case Player:        return "Player";
        case GameObject:    return "GameObject";
        case DynamicObject: return "DynamicObject";
        case Corpse:        return "Corpse";
    }
    return NULL;
}

void print_object_info(object_t object) {
    printf("ObjectType: %s\n", object_type_code_to_string(object.type));
    printf("Guid: %llu\n", object.guid);
    printf("Pointer: %u\n", object.pointer);

    if (object.type == Player || object.type == Unit) {
        printf("Health: %u\n", object.health);
        printf("Position: %f %f %f\n", object.position.x,
                                       object.position.y,
                                       object.position.z);
        printf("Name: %s\n", object.name_ptr);
    }
    printf("\n");
}
