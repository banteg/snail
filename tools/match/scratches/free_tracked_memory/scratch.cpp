// free_tracked_memory @ 0x431bf0 (cdecl)

#include "tracked_allocation_stack.h"

extern "C" void free(void* pointer);

void report_errorf(char* format, ...);

extern int g_tracked_allocation_total_bytes;
extern int g_tracked_allocation_depth;

void free_tracked_memory(void* pointer)
{
    pointer = (char*)pointer - 4;
    int guarded_size =
        ((TrackedAllocationStack*)&g_tracked_allocation_depth)->get_tracked_allocation_size(pointer);
    g_tracked_allocation_total_bytes -= guarded_size;

    char* block = (char*)pointer;
    if (block[0] != -34 || block[1] != -83 || block[2] != -70 || block[3] != -66 ||
        block[guarded_size - 4] != -34 || block[guarded_size - 3] != -83 ||
        block[guarded_size - 2] != -70 || block[guarded_size - 1] != -66) {
        report_errorf("Memory corruption");
    }

    free(pointer);
    ((TrackedAllocationStack*)&g_tracked_allocation_depth)->pop_tracked_allocation(pointer);
}
