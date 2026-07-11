#ifndef TRACKED_ALLOCATION_STACK_H
#define TRACKED_ALLOCATION_STACK_H

struct TrackedAllocationRecord {
    void* pointer;     // +0x00
    int guarded_size;  // +0x04
    int unknown_08;    // +0x08
};

typedef char TrackedAllocationRecord_must_be_0x0c[
    (sizeof(TrackedAllocationRecord) == 0x0c) ? 1 : -1];

class TrackedAllocationStack {
public:
    // The one-store body is linker-folded with cREnemyManager::Init at 0x415e20.
    void initialize_tracked_allocation_stack();
    int get_tracked_allocation_size(void* pointer);
    void push_tracked_allocation(int unused, void* pointer, int size);
    int pop_tracked_allocation(void* pointer);

    int depth;              // +0x00
    int mark_or_unknown_04; // +0x04
    int unknown_08;         // +0x08
    union {
        struct {
            int first_pointer;    // +0x0c
            int first_size;       // +0x10
            int first_unknown_14; // +0x14
        };
        TrackedAllocationRecord records[15000];
    };
};

#endif
