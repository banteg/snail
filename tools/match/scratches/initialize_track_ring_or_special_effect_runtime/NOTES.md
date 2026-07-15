# initialize_track_ring_or_special_effect_runtime @ 0x408570

Exact Windows constructor wrapper for one authored `SubRing` (`cRSubRing` on
iOS and Android): constructs the inherited RenderableBod, installs the table at
`0x49732c`, and returns the receiver. The table entry points directly to
`update_ring_or_special_effect_parent @ 0x43e830`, the cross-port
`cRSubRing::AI()` method.

`SubgameRuntime` owns two 0x1f8-byte `SubRing` records inline. Their exact
0x3f0 total matches the native `Size of cRSubRing` ledger entry. The scratch
now defines the constructor on `SubRing` and remains exact at 7/7 instructions
with two clean operands.

## 2026-07-15 durable owner replay

The paired Binary Ninja and IDA replay now persists this constructor as
`SubRing* __thiscall initialize_track_ring_or_special_effect_runtime(SubRing*)`
instead of IDA's stale `_DWORD*` shell. Readback closes `SubRingStar` at `0x20`,
`SubRing` at `0x1f8`, and its two-slot `SubRingPool` at `0x3f0`; strict paired
export reports no database/export mismatches. The source remains exact at 7/7.
