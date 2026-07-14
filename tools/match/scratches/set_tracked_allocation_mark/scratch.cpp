// set_tracked_allocation_mark @ 0x431cb0 (cdecl)

#include "tracked_allocation_stack.h"

int set_tracked_allocation_mark()
{
    int result = g_tracked_allocation_stack.depth;
    g_tracked_allocation_stack.bookmark_depth = result;
    return result;
}
