// request_object_edges @ 0x430570 (thiscall, ret)

#include "object_render_types.h"

void* allocate_tracked_memory(int size, char* name);

void Object::request_object_edges(int requested_count)
{
    if (edge_count == 0) {
        edge_count = requested_count;
        edges = (ObjectToonEdge*)allocate_tracked_memory(
            requested_count * sizeof(ObjectToonEdge), "Object Edges");
    }
}
