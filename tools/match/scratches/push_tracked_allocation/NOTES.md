# push_tracked_allocation

Tracked-allocation stack append helper at 0x431af0. Each stack entry is three
words wide; the pointer is stored at the entry's first word and the guarded
allocation size is stored at the second word.

Current scratch models the real side effect and overflow check. The second
integer argument is intentionally unused; `allocate_tracked_memory` passes the
debug label before the backing pointer and size, but this helper only records
the pointer and size.

Exact match: 100.00%, 19/19 instructions, with two masked operands resolved.
The helper is modeled as `void`: `allocate_tracked_memory` ignores the return,
and the apparent integer result is just the depth left in `eax` on the normal
path or `report_errorf`'s leftover `eax` on overflow.
