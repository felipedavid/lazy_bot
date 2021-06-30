#ifndef POSITION
#define POSITION

class Position {
public:
    float x;
    float y;
    float z;

    Position(float x, float y, float z);
    float get_distance_from(Position pos);
};
#endif
