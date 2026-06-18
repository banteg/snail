// pop_tracked_allocation @ 0x431b30 (thiscall, ret 0x4)

class TrackedAllocationStack {
public:
    int pop_tracked_allocation(void* pointer);

    int depth; // +0x00
    int field_04;
    int field_08;
    int first_pointer; // +0x0c
    int first_size; // +0x10
};

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
