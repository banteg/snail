// initialize_duplicate_vertices @ 0x419f50 (thiscall, ret 0x4)

#include "duplicate_vertices.h"

void* allocate_tracked_memory(int size, char* label);
extern char g_duplicate_vertices_alloc_label[]; // "Duplicate vertices"

void* DuplicateVertices::initialize_duplicate_vertices(int count)
{
    active_count = 0;
    void* result = allocate_tracked_memory(count * 10, g_duplicate_vertices_alloc_label);
    records = (DuplicateVertexRecord*)result;
    return result;
}
