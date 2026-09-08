#ifndef TRACKED_ALLOCATION_STACK_H
#define TRACKED_ALLOCATION_STACK_H

struct TrackedAllocationRecord {
    int unknown_00;    // +0x00: unused by the Windows push/pop bodies
    void* pointer;     // +0x04
    int guarded_size;  // +0x08
};

typedef char TrackedAllocationRecord_must_be_0x0c[
    (sizeof(TrackedAllocationRecord) == 0x0c) ? 1 : -1];

class TrackedAllocationStack {
public:
    // The one-store body is linker-folded with cREnemyManager::Init at 0x415e20.
    void initialize_tracked_allocation_stack();
    int get_tracked_allocation_size(void* pointer);
    void push_tracked_allocation(char* label, void* pointer, int size);
    int pop_tracked_allocation(void* pointer);

    int depth;          // +0x00
    int bookmark_depth; // +0x04
    TrackedAllocationRecord records[15000]; // +0x08, pointer +0x0c, size +0x10
};

typedef char TrackedAllocationStack_must_be_0x2bf28[
    (sizeof(TrackedAllocationStack) == 0x2bf28) ? 1 : -1];

extern TrackedAllocationStack g_tracked_allocation_stack;
extern int g_tracked_allocation_total_bytes;

void* allocate_tracked_memory(int size, char* name);
void free_tracked_memory(void* pointer);
void initialize_tracked_allocation_depth();
void set_tracked_allocation_mark();
void free_tracked_allocations_to_mark();

#endif
