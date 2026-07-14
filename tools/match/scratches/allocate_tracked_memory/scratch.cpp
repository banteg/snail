// allocate_tracked_memory @ 0x431b60 (cdecl)

#include "tracked_allocation_stack.h"

extern "C" void* malloc(unsigned int size);
extern "C" void* memset(void* destination, int value, unsigned int count);

void report_errorf(char* format, ...);

extern int g_tracked_allocation_total_bytes;

void* allocate_tracked_memory(int size, char* name)
{
    size += 8;
    char* block = (char*)malloc(size);
    if (block == 0) {
        report_errorf("Not enough memory\n\n");
    }

    g_tracked_allocation_stack.push_tracked_allocation((int)name, block, size);
    memset(block, 0, size);

    block[0] = -34;
    block[1] = -83;
    block[2] = -70;
    block[3] = -66;
    block[size - 4] = -34;
    block[size - 3] = -83;
    block[size - 2] = -70;
    block[size - 1] = -66;
    g_tracked_allocation_total_bytes += size;
    return block + 4;
}
