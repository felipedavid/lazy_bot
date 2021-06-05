#include <math.h>

#include "local_player.h"
#include "game_functions.h"
#include "objects.h"

object_t *local_player;

float get_distance_from_object(object_t object) {
    position_t local_player_position = get_object_position(*local_player);
    position_t object_position = get_object_position(object);

    float delta_x = local_player_position.x - object_position.x;
    float delta_y = local_player_position.y - object_position.y;
    float delta_z = local_player_position.z - object_position.z;

    return (float) sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
}

object_t get_closest_enemy() {
    object_t closest_enemy;
    for (size_t i = 0; i < n_objects; i++) {
        if (objects[i].type != Unit) {
            continue;
        } else if (get_object_health(objects[i]) <= 0) {
            continue;
        } else if (i == 0) {
            closest_enemy = objects[i];
        } else if (get_distance_from_object(objects[i]) < 
                   get_distance_from_object(closest_enemy)) {
            closest_enemy = objects[i]; 
        }
    }
    return closest_enemy;
}
