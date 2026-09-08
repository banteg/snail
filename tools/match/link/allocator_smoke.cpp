// Exercise separately compiled recovered code on valid LIFO allocations.
#include <stdio.h>
#include <stddef.h>
#include "tracked_allocation_stack.h"
#include "rdebug.h"

static int checks;
static int failures;
static struct {
    TrackedAllocationStack stack;
    int next_owner;
} boundary;

static void check(bool condition, const char* label)
{
    ++checks;
    if (!condition) {
        ++failures;
        printf("FAIL: %s\n", label);
    }
}

static bool guard(const unsigned char* p)
{
    return p[0] == 0xde && p[1] == 0xad && p[2] == 0xba && p[3] == 0xbe;
}

int main(int argc, char** argv)
{
    check(sizeof(TrackedAllocationStack) == 180008 &&
          offsetof(TrackedAllocationStack, records) == 8 &&
          offsetof(TrackedAllocationRecord, pointer) == 4 &&
          offsetof(TrackedAllocationRecord, guarded_size) == 8,
          "native two-word header and record boundaries");
    boundary.stack.depth = 14999;
    boundary.stack.records[14999].unknown_00 = 0x12345678;
    boundary.next_owner = 0x23456789;
    boundary.stack.push_tracked_allocation("last", &boundary, 17);
    check(boundary.stack.depth == 15000 &&
          boundary.stack.records[14999].pointer == &boundary &&
          boundary.stack.records[14999].guarded_size == 17,
          "last valid record uses recovered push body");
    check(boundary.stack.records[14999].unknown_00 == 0x12345678,
          "push preserves first record word");
    check(boundary.next_owner == 0x23456789,
          "last valid record preserves adjacent owner");

    g_tracked_allocation_stack.depth = 7;
    g_tracked_allocation_stack.bookmark_depth = 9;
    initialize_tracked_allocation_depth();
    check(g_tracked_allocation_stack.depth == 0, "initialize clears depth");
    check(g_tracked_allocation_stack.bookmark_depth == 9, "initialize preserves bookmark");
    set_tracked_allocation_mark();
    check(g_tracked_allocation_stack.bookmark_depth == 0, "mark saves current depth");

    unsigned char* a = (unsigned char*)allocate_tracked_memory(16, "first");
    check(a != 0 && g_tracked_allocation_stack.depth == 1, "first allocation recorded");
    check(g_tracked_allocation_total_bytes == 24, "accounting includes both guards");
    check(guard(a - 4) && guard(a + 16), "allocation guard bytes");
    bool zero = true;
    for (int i = 0; i < 16; ++i)
        zero = zero && a[i] == 0;
    check(zero, "payload zero initialized");
    check(g_tracked_allocation_stack.get_tracked_allocation_size(a - 4) == 24,
          "size lookup uses raw allocation pointer");
    for (int j = 0; j < 16; ++j)
        a[j] = (unsigned char)(j + 1);
    if (argc == 2 && argv[1][0] == '!')
        a[15] = 0;
    check(a[0] == 1 && a[15] == 16, "payload can hold application data");

    set_tracked_allocation_mark();
    check(g_tracked_allocation_stack.bookmark_depth == 1, "nonzero mark");
    void* b = allocate_tracked_memory(37, "second");
    void* c = allocate_tracked_memory(0, "empty");
    check(g_tracked_allocation_stack.depth == 3 && g_tracked_allocation_total_bytes == 77,
          "multiple allocations and zero length accounting");
    check(guard((unsigned char*)c - 4) && guard((unsigned char*)c), "empty allocation guards");
    check(g_tracked_allocation_stack.get_tracked_allocation_size(b) == 0,
          "payload pointer is not a raw record pointer");
    free_tracked_allocations_to_mark();
    check(g_tracked_allocation_stack.depth == 1 && g_tracked_allocation_total_bytes == 24,
          "unwind frees through saved mark");
    check(a[0] == 1 && guard(a - 4), "unwind preserves earlier allocation");
    free_tracked_allocations_to_mark();
    check(g_tracked_allocation_stack.depth == 1 && g_tracked_allocation_total_bytes == 24,
          "unwind at mark is a no-op");
    free_tracked_memory(a);
    check(g_tracked_allocation_stack.depth == 0 && g_tracked_allocation_total_bytes == 0,
          "last free restores accounting");
    set_tracked_allocation_mark();
    void* reused = allocate_tracked_memory(5, "reuse");
    check(g_tracked_allocation_stack.depth == 1 && g_tracked_allocation_total_bytes == 13,
          "stack records reused after free");
    free_tracked_memory(reused);
    check(g_tracked_allocation_total_bytes == 0, "reused allocation freed");
    check(report_errorf("format %d %s", 12, "test") == 0 && debug_report_stub("test") == 0,
          "variadic reporting ABI returns through recovered no-op sink");

    printf("allocator checks=%d failures=%d\n", checks, failures);
    fflush(0);
    return failures ? 1 : 0;
}
