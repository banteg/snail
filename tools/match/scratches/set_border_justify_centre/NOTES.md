# set_border_justify_centre

Small border/runtime mutator at 0x404730. Both BN and IDA decompiles show it
storing the argument at this+0x435b0 and returning the same value.

Exact match: 100.00%, 3/3 instructions, no masked operands.

Shared in `border_runtime.h` for the menu/background callers that only need the
trailing justify field.

2026-06-20 update: the allocator relationship now has its evidence pass.
`BorderManager` keeps `BorderRecord` backing storage, but `allocate_border()`
returns a `FrontendWidget*` view because the exact frontend callers consume the
slot through that layout. This does not change the caution for unrelated border
runtime fields: promote them only when multiple callsites agree.
