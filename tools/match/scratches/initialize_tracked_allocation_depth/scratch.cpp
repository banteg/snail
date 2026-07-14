// initialize_tracked_allocation_depth @ 0x430e30 (cdecl)

#include "tracked_allocation_stack.h"

void initialize_tracked_allocation_depth()
{
    g_tracked_allocation_stack.depth = 0;
}
