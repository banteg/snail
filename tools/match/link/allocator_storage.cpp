#include "tracked_allocation_stack.h"

// The two-word Windows header plus 15000 twelve-byte records occupy 0x2bf28
// bytes: native 0x5108c0..0x53c7e8. The first record word is still unnamed.
// Integration placement is selected by the linker, independently of native BSS.
TrackedAllocationStack g_tracked_allocation_stack;
int g_tracked_allocation_total_bytes;

// Integration-only sizeof witnesses exclude the alignment between these owners.
extern "C" const unsigned int allocator_storage_sizes[] = {
    sizeof(g_tracked_allocation_stack), sizeof(g_tracked_allocation_total_bytes)
};
