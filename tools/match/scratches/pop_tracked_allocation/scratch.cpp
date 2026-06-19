// pop_tracked_allocation @ 0x431b30 (thiscall, ret 0x4)

#include "tracked_allocation_stack.h"

int TrackedAllocationStack::pop_tracked_allocation(void* pointer)
{
    int result = depth - 1;
    depth = result;
    if (*(&first_pointer + result * 3) != (int)pointer) {
        int index = 0;
        if (result > 0) {
            while (index < result) {
                if (*(&first_pointer + index * 3) == (int)pointer) {
                    return result;
                }
                ++index;
            }
        }
    }
    return result;
}
