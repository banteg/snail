// RequestEdges @ 0x430570 (thiscall, ret)

#include "object_render_types.h"

#include "tracked_allocation_stack.h"

void cRObject::RequestEdges(int requested_count)
{
    if (edge_count == 0) {
        edge_count = requested_count;
        edges = (ObjectToonEdge*)allocate_tracked_memory(
            requested_count * sizeof(ObjectToonEdge), "Object Edges");
    }
}
