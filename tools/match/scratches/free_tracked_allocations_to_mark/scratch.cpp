// free_tracked_allocations_to_mark @ 0x431c70 (cdecl)

extern int g_tracked_allocation_depth;
extern int g_tracked_allocation_mark;

void free_tracked_memory(void* pointer);

int free_tracked_allocations_to_mark()
{
    int depth = g_tracked_allocation_depth;
    while (depth > g_tracked_allocation_mark) {
        free_tracked_memory((void*)((&g_tracked_allocation_depth)[depth * 3] + 4));
        depth = g_tracked_allocation_depth;
    }
    return depth;
}
