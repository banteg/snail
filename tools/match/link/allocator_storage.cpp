#include "tracked_allocation_stack.h"

// Integration backing only. The native object's upper bound is not proven:
// its declared final unknown record word reaches the neighboring music buffer.
// This does not assert the original BSS allocation extent or placement.
TrackedAllocationStack g_tracked_allocation_stack;
int g_tracked_allocation_total_bytes;
