// ObjectProcNull @ 0x41a0a0 (cdecl)

#include "object_render_types.h"

void ObjectProcNull(Object* object)
{
    object->flags |= OBJECT_FLAG_RENDER_DISABLED;
}
