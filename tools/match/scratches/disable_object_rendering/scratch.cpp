// disable_object_rendering @ 0x41a0a0 (cdecl)

#include "object_render_types.h"

void disable_object_rendering(Object* object)
{
    object->flags |= 0x40000;
}
