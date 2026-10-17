# initialize_tracked_allocation_depth @ 0x430e30

Clears `g_tracked_allocation_stack.depth` before `initialize_game_data_archive`
and the guarded allocation helpers begin using the shared stack. Allocation,
free, unwind, and bookmark paths independently prove that `0x5108c0` is the
first word of their common owner. The member spelling remains exact at 2/2
instructions with its operand resolved.

## 2026-10-17 compiler-generated pair

The thunk and body are VC6's dynamic-initializer pair for the global definition
`TrackedAllocationStack g_tracked_allocation_stack`, which replaces the
hand-written wrapper and initializer function. Both scratches compile the one
source file, the body as `_$E1` and the thunk as `_$E2` in the whole RShell TU
(VC6 numbers each initialized declaration's pair in steps of three). Here
`TrackedAllocationStack`'s inline constructor clears `depth`. The file still
opens with `rshell_prelude.h`, so the prelude stays at the head of the RShell
TU. Both functions stay exact, with every masked operand resolved through the
`function_alias` reference entries.
