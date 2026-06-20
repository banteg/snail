# allocate_border @ 0x4032a0

Exact border-record allocator.

The manager storage remains modeled as 150 `BorderRecord` slots with stride
`0x724`; the allocator scans `flags` at slot `+0x1a0`, stamps
`created_time` from `game+0x51c`, and returns the slot base at
`manager+0x684 + index*0x724`.

2026-06-20 ABI cleanup: the shared method now returns `FrontendWidget*` because
all frontend callsites consume the allocated record through that view. The
backing storage still uses `BorderRecord` for the manager layout. Focused
matcher stays exact at 23/23 instructions with 3 clean masked operands.
