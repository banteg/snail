// push_tracked_allocation @ 0x431af0 (thiscall, ret 0xc)

#include "tracked_allocation_stack.h"

void report_errorf(char* format, ...);

void TrackedAllocationStack::push_tracked_allocation(int unused, void* pointer, int size)
{
    *(&first_size + depth * 3) = size;
    *(&first_pointer + depth * 3) = (int)pointer;

    ++depth;
    int result = depth;
    if (depth > 15000) {
        report_errorf("Memory Stack Full");
    }
}
