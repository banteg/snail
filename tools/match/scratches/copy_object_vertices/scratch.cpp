// copy_object_vertices @ 0x42f790 (thiscall)

#include "object_render_types.h"

void Object::copy_object_vertices()
{
    for (int i = 0; i < vertex_count; ++i) {
        copied_vertices[i] = vertices[i];
    }
}
