// cRDuplicateVertices::Init(int) @ 0x419f50 (thiscall, ret 0x4)

#include "duplicate_vertices.h"
#include "tracked_allocation_stack.h"

extern char g_duplicate_vertices_alloc_label[]; // "Duplicate vertices"

void* cRDuplicateVertices::Init(int count)
{
    active_count = 0;
    void* result = allocate_tracked_memory(count * 10, g_duplicate_vertices_alloc_label);
    records = (DuplicateVertexRecord*)result;
    return result;
}
