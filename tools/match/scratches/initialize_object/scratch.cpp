// initialize_object @ 0x42f6f0 (thiscall, ret)

#include "object_render_types.h"

int Object::initialize_object()
{
    flags = 0;
    field_14 = 0;
    vertex_count = 0;
    facequad_count = 0;
    vertex_normals = 0;
    field_40 = 0;
    texture_group_count = 0;
    return 0;
}
