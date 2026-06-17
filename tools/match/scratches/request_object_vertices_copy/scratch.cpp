// request_object_vertices_copy @ 0x42f7d0 (thiscall, ret)

#include "object_render_types.h"

void* allocate_tracked_memory(int size, char* name);

int Object::request_object_vertices_copy()
{
    copied_vertices = (Vector3*)allocate_tracked_memory(vertex_count * 0xc, "Object Vertex List");
    return copy_object_vertices();
}
