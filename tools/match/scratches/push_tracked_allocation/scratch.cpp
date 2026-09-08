// push_tracked_allocation @ 0x431af0 (thiscall, ret 0xc)

#include "tracked_allocation_stack.h"
#include "rdebug.h"

void TrackedAllocationStack::push_tracked_allocation(char* label, void* pointer, int size)
{
    records[depth].guarded_size = size;
    records[depth].pointer = pointer;

    ++depth;
    int result = depth;
    if (depth > 15000) {
        report_errorf("Memory Stack Full");
    }
}
