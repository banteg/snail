// RequestVertices @ 0x42f710 (thiscall, ret 0x4)

#include "object_render_types.h"

#include "tracked_allocation_stack.h"
#include "rdebug.h"

void cRObject::RequestVertices(int requested_count)
{
    if (requested_count > 0x10000)
        report_errorf("Too many Vertices");

    int current_count = vertex_count;
    if (current_count > 0 && current_count < requested_count) {
        report_errorf("Reallocation of Vertices impending\n");
        free_tracked_memory(vertices);
        vertex_count = 0;
    }

    if (vertex_count == 0) {
        vertex_count = requested_count;
        vertices = (Vector3*)allocate_tracked_memory(
            requested_count * sizeof(Vector3), "Object Vertex List");
        RequestColours();
    }
}
