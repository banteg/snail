// free_tracked_allocations_to_mark @ 0x431c70 (cdecl)

#include "tracked_allocation_stack.h"

void free_tracked_memory(void* pointer);

void free_tracked_allocations_to_mark()
{
    int depth = g_tracked_allocation_stack.depth;
    while (depth > g_tracked_allocation_stack.bookmark_depth) {
        free_tracked_memory(
            (char*)g_tracked_allocation_stack.records[depth - 1].pointer + 4);
        depth = g_tracked_allocation_stack.depth;
    }
}
