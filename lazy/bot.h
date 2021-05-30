#include <windows.h>
#include <stdint.h>
#include "object.h"

extern HINSTANCE instance_handle; // <- keep an eye on this buddy :)
extern object_t local_player;
extern object_t closest_unit;
extern int n_units;
//extern object_t units[100];

void bot();
void update();
void start();
void stop();
