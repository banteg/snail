// free_tracked_memory @ 0x431bf0 (cdecl)

extern "C" void free(void* pointer);

void report_errorf(char* format, ...);

class TrackedAllocationStack {
public:
    int get_tracked_allocation_size(void* pointer);
    void pop_tracked_allocation(void* pointer);
};

extern int g_tracked_allocation_total_bytes;
extern int g_tracked_allocation_depth;

void free_tracked_memory(void* pointer)
{
    char* block = (char*)pointer;
    block -= 4;
    int guarded_size =
        ((TrackedAllocationStack*)&g_tracked_allocation_depth)->get_tracked_allocation_size(block);
    g_tracked_allocation_total_bytes -= guarded_size;

    if (block[0] != -34 || block[1] != -83 || block[2] != -70 || block[3] != -66 ||
        block[guarded_size - 4] != -34 || block[guarded_size - 3] != -83 ||
        block[guarded_size - 2] != -70 || block[guarded_size - 1] != -66) {
        report_errorf("Memory corruption");
    }

    free(block);
    ((TrackedAllocationStack*)&g_tracked_allocation_depth)->pop_tracked_allocation(block);
}
