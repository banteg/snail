// get_tracked_allocation_size @ 0x431ab0 (thiscall, ret 0x4)

#include "tracked_allocation_stack.h"

int report_errorf(char* format, ...);

int TrackedAllocationStack::get_tracked_allocation_size(void* pointer)
{
    int count = depth;
    int index = 0;
    if (count > 0) {
        while (index < count) {
            if (*(&first_pointer + index * 3) == (int)pointer)
                return *(&first_size + index * 3);
            ++index;
        }
    }

    report_errorf("Cannot find Memory Size");
    return 0;
}
