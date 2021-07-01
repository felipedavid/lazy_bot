#ifndef OBJECT_MANAGER
#define OBJECT_MANAGER
#include <cstdint>
#include <vector>

#include "objects\object.h"

struct ObjectManager {
    std::vector<WowObject> objects;

    void populate_lists();
    void log_info();
};
#endif
