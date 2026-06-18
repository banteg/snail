// push_tracked_allocation @ 0x431af0 (thiscall, ret 0xc)

void report_errorf(char* format, ...);

class TrackedAllocationStack {
public:
    void push_tracked_allocation(int unused, void* pointer, int size);

    int depth; // +0x00
    int field_04;
    int field_08;
    int first_pointer; // +0x0c
    int first_size; // +0x10
};

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
