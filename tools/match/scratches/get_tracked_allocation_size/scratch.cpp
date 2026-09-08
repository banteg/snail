// get_tracked_allocation_size @ 0x431ab0 (thiscall, ret 0x4)

#include "tracked_allocation_stack.h"
#include "rdebug.h"

int TrackedAllocationStack::get_tracked_allocation_size(void* pointer)
{
    int count = depth;
    int index = 0;
    if (count > 0) {
        while (index < count) {
            if (records[index].pointer == pointer)
                return records[index].guarded_size;
            ++index;
        }
    }

    report_errorf("Cannot find Memory Size");
    return 0;
}
