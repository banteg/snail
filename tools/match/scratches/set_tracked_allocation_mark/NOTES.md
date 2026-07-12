# set_tracked_allocation_mark

Small tracked-allocation helper at 0x431cb0. Copies the current tracked
allocation stack depth at 0x5108c0 into the saved unwind mark at 0x5108c4 and
returns the copied depth.

Exact match: 100.00%, 3/3 instructions, with both tracked-allocation globals
resolved through g_tracked_allocation_depth/g_tracked_allocation_mark.

iOS `RShell.o` names this lifecycle edge `RShellMemoryBookmark()`. Both ports
snapshot the current allocation depth for a later unwind, though their
platform-specific allocation-stack layouts place the saved field at different
offsets.
