#include <stdint.h>
#include "object.h"

void update_view();
uint32_t __fastcall enumerate_objects_callback(void *thiss, uint32_t filter, uint64_t guid);
object_type_t get_object_type(uint32_t object_ptr);
char *get_object_name(object_t object);
uint32_t get_object_health(object_t object);
position_t get_object_position(object_t object);
