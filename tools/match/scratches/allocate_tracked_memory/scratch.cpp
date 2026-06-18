// allocate_tracked_memory @ 0x431b60 (cdecl)

extern "C" void* malloc(unsigned int size);
extern "C" void* memset(void* destination, int value, unsigned int count);

void report_errorf(char* format, ...);

class TrackedAllocationStack {
public:
    void push_tracked_allocation(int unused, void* pointer, int size);
};

extern int g_tracked_allocation_total_bytes;
extern int g_tracked_allocation_depth;

void* allocate_tracked_memory(int size, char* name)
{
    int guarded_size = size;
    char* label = name;
    guarded_size += 8;
    char* block = (char*)malloc(guarded_size);
    if (block == 0) {
        report_errorf("Not enough memory\n\n");
    }

    ((TrackedAllocationStack*)&g_tracked_allocation_depth)
        ->push_tracked_allocation((int)label, block, guarded_size);
    memset(block, 0, guarded_size);

    block[0] = -34;
    block[1] = -83;
    block[2] = -70;
    block[3] = -66;
    block[guarded_size - 4] = -34;
    block[guarded_size - 3] = -83;
    block[guarded_size - 2] = -70;
    block[guarded_size - 1] = -66;
    g_tracked_allocation_total_bytes += guarded_size;
    return block + 4;
}
