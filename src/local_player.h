#include "objects.h"

extern size_t n_objects;
extern object_t objects[500];

float get_distance_from_object(object_t object);
object_t get_closest_enemy_named(char *unit_name);
