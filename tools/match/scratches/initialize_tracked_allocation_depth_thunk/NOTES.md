# initialize_tracked_allocation_depth_thunk @ 0x430e20

CRT constructor-table entry at `0x4a102c`. The shipped body tail-jumps to the
adjacent initializer that clears the tracked-allocation stack depth before
shell startup.

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
