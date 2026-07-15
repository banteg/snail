# set_border_justify_centre

Small border/runtime mutator at 0x404730. Both BN and IDA decompiles show it
storing the argument at `this+0x435b0`. All ten Windows callers discard `EAX`,
and the independent iOS symbol names the authored method
`cRBorderManager::SetJustifyCentre(float)`.

Exact match: 100.00%, 3/3 instructions, no masked operands.

The field is the final dword of `BorderManager`. The exact `void(float)` source
naturally compiles to the same load/store/`ret 4` body: the observed value left
in `EAX` is only the compiler's argument-transfer residue, not an API result.
The ten source callers now use the authored `0.0f` and `25.0f` values directly
instead of spelling their IEEE-754 bit patterns as integers.

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

2026-07-15 ABI closure: all ten native callers discard `EAX`; seven remain
exact after changing their source arguments to floats, and the three partial
callers retain their previous scores and clean-operand counts. Live Binary
Ninja readback now gives `void __thiscall(struct BorderManager*, float)` and a
`float justify_centre` field at `+0x435b0`; IDA gives the corresponding
`FrameBorderManager*` prototype. A strict eleven-function export refreshed the
setter and all ten callers with zero cross-decompiler mismatches.
