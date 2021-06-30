#include <math.h>

#include "position.hpp"

Position::Position(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

float Position::get_distance_from(Position pos) {
    float delta_x = x - pos.x;
    float delta_y = y - pos.y;
    float delta_z = z - pos.z;

    return sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
}
