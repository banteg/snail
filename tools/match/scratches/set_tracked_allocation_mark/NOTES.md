# set_tracked_allocation_mark

Small tracked-allocation helper at 0x431cb0. Copies the current tracked
allocation stack depth at 0x5108c0 into the saved unwind mark at 0x5108c4.
The copied depth remains incidentally in EAX, but the authored API is `void`.

Exact match: 100.00%, 3/3 instructions, with both tracked-allocation operands
resolved as `g_tracked_allocation_stack.depth` and `.bookmark_depth`.

Android/iOS `RShell.o` names this lifecycle edge `RShellMemoryBookmark()`.
The symbol-bearing Android body never writes `r0`, independently proving the
void return contract. Both ports snapshot the current allocation depth for a
later unwind, though their platform-specific allocation-stack layouts place the
saved field at different offsets.

The Windows read/write pair proves that `+0x04` is the active bookmark member,
replacing the former `mark_or_unknown_04` placeholder. The reference manifest
keeps `g_tracked_allocation_depth` and `g_tracked_allocation_mark` as compatible
field aliases while making the aggregate at `0x5108c0` canonical.

The 2026-07-16 paired replay now types this function in both databases and
renders the copy exclusively as
`g_tracked_allocation_stack.bookmark_depth = g_tracked_allocation_stack.depth`.
The legacy reference name remains only as matcher provenance for the interior
address; health checks reject it in decompile output. The exact 3/3 match and
both operand proofs are unchanged.
