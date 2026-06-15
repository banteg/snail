// get_tracked_allocation_size @ 0x431ab0 (thiscall, ret 0x4)

int report_errorf(char* format, ...);

class TrackedAllocationStack {
public:
    int get_tracked_allocation_size(void* pointer);

    int depth; // +0x00
    int field_04;
    int field_08;
    int first_pointer; // +0x0c
    int first_size; // +0x10
};

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
