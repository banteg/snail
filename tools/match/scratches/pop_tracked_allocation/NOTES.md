# pop_tracked_allocation

Tracked-allocation stack pop helper at 0x431b30. It decrements the stack depth
first, checks whether the freed pointer was the top stack entry, and falls back
to a linear pointer search if the free order differs.

Focused match: 100%, 20/20 instructions, no masked operands.

The native helper leaves the decremented depth in `eax`. Spelling the scratch as
an `int` return with an early `return result` from the fallback search makes VC6
emit the same direct `cmp dword [ecx], esi` loop header; the sole native callsite
from `free_tracked_memory` does not consume the return value.

The 2026-07-16 paired replay types the receiver as
`TrackedAllocationStack*` and the 12-byte trailing entries as
`TrackedAllocationRecord`. Both analysis lanes now show the depth and pointer
ownership without raw integer receivers; focused matching stays exactly 20/20.
