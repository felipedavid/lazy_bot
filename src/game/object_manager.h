#ifndef OBJECT_MANAGER
#define OBJECT_MANAGER
#include <cstdint>
#include <vector>

#include "objects\object.h"
#include "objects\unit.h"

struct ObjectManager {
    std::vector<Unit> units;

    void populate_lists();
    void log_info();
};
#endif
