# set_border_justify_centre

Small border/runtime mutator at 0x404730. Both BN and IDA decompiles show it
storing the argument at this+0x435b0 and returning the same value.

Exact match: 100.00%, 3/3 instructions, no masked operands.

The field is the final dword of `BorderManager`. Its union keeps the mutator's
raw-bit ABI and the widget initializers' float interpretation honest.

2026-06-20 update: the allocator relationship now has its evidence pass.
`BorderManager` keeps `BorderRecord` backing storage, but `allocate_border()`
returns a `FrontendWidget*` view because the exact frontend callers consume the
slot through that layout. This does not change the caution for unrelated border
runtime fields: promote them only when multiple callsites agree.

2026-07-12 ownership closure: the exact delayed-lane helpers prove
`BorderManager +0x4359c..+0x435ac`, this exact mutator proves `+0x435b0`, and
the root's fixed BOD bank begins immediately afterward at `GameRoot +0x44100`.
The manager therefore has exact extent `0x435b4`; the duplicate
`BorderRuntime` and `BorderDelayLane` owners were removed.
