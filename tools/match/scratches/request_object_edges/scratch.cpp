// request_object_edges @ 0x430570 (thiscall, ret)

#include "object_render_types.h"

void* allocate_tracked_memory(int size, char* name);

void* Object::request_object_edges(int edge_count)
{
    void* result = (void*)this->edge_count;
    if (result == 0) {
        this->edge_count = edge_count;
        result = allocate_tracked_memory(edge_count * 0x24, "Object Edges");
        edges = (ObjectToonEdge*)result;
    }
    return result;
}
