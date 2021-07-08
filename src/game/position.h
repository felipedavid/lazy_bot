#ifndef POSITION
#define POSITION

struct Position {
    float x;
    float y;
    float z;

    float distance_from(Position pos);
};

#endif
