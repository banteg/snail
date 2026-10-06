// pop_tracked_allocation @ 0x431b30 (thiscall, ret 0x4)

#include "tracked_allocation_stack.h"

int TrackedAllocationStack::pop_tracked_allocation(void* pointer)
{
    int result = depth - 1;
    depth = result;
    if (records[result].pointer != pointer) {
        int index = 0;
        if (result > 0) {
            while (index < result) {
                if (records[index].pointer == pointer) {
                    return result;
                }
                ++index;
            }
        }
    }
    return result;
}
