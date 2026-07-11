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
