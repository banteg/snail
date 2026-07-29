// RequestVerticesCopy @ 0x42f7d0 (thiscall, ret)

#include "object_render_types.h"

void* allocate_tracked_memory(int size, char* name);

void cRObject::RequestVerticesCopy()
{
    copied_vertices = (Vector3*)allocate_tracked_memory(
        vertex_count * sizeof(Vector3), "Object Vertex List");
    CopyVertices();
}
