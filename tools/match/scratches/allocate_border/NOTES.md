# allocate_border @ 0x4032a0

Exact border-record allocator.

The manager storage remains modeled as 150 `BorderRecord` slots with stride
`0x724`; the allocator scans `flags` at slot `+0x1a0`, stamps
`created_time` from `GameRoot::frame_counter +0x51c`, and returns the slot base at
`manager+0x684 + index*0x724`.

2026-06-20 ABI cleanup: the shared method now returns `FrontendWidget*` because
all frontend callsites consume the allocated record through that view. The
backing storage still uses `BorderRecord` for the manager layout. Focused
matcher stays exact at 23/23 instructions with 3 clean masked operands.

2026-07-11 root-owner pass: the timestamp load now uses the shared typed root
field. This independently proves `frame_counter` outside the main frame loop;
the allocator stays exact at 23/23.

2026-07-14 base ownership closure: `BorderRecord` and its returned
`FrontendWidget` semantic view now share the same inherited `BodBase`. This is
the storage relationship already proved by the exact record constructor and
the allocator's unchanged 0x724-byte stride. The allocator remains exact at
23/23 instructions with three clean operands.
