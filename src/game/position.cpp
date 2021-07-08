#include <math.h>

#include "position.h"

float Position::distance_from(Position pos) {
    float delta_x = x - pos.x;
    float delta_y = y - pos.y;
    float delta_z = z - pos.z;

    return sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
}
