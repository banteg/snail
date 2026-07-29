// CopyVertices @ 0x42f790 (thiscall)

#include "object_render_types.h"

void cRObject::CopyVertices()
{
    for (int i = 0; i < vertex_count; ++i) {
        copied_vertices[i] = vertices[i];
    }
}
