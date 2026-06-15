// set_tracked_allocation_mark @ 0x431cb0 (cdecl)

extern int g_tracked_allocation_depth;
extern int g_tracked_allocation_mark;

int set_tracked_allocation_mark()
{
    int result = g_tracked_allocation_depth;
    g_tracked_allocation_mark = result;
    return result;
}
