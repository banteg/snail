# initialize_track_speedup_runtime

`initialize_track_speedup_runtime` @ 0x4084b0 is the exact seven-instruction
Windows constructor for the authored `cRSubSpeedUp` singleton at
`cRSubGame +0x355db0`. It constructs the inherited
`RenderableBod`, installs table `0x497314`, and returns the receiver. That
table's sole entry is the exact `update_track_speedup` @ 0x43ee50.

The complete object is 0xb4 bytes and ends exactly at the adjacent
`JetPack +0x355e64`, matching the native `Size of cRSubSpeedUp` ledger.
`SubSpeedUp` and `TrackSpeedupRuntime` remain compatibility aliases.

2026-07-14 renderable inheritance closure: `SubSpeedUp` now derives directly
from the `RenderableBod` initialized here. This retires its duplicated
`BodBase + TransformMatrix` fields while preserving inherited zero-offset list
linkage. The constructor remains exact at 7/7 with both operands clean.

## 2026-07-19 analysis-lane base composition

The narrow Binary Ninja view now owns the same complete zero-offset
`RenderableBod body` as the broad path header and matcher instead of replaying
flattened base subfields. Broad and narrow syncs are consequently idempotent
in either order. The constructor remains exact at 7/7 with both operands
clean.

## 2026-08-09 primary cRSubSpeedUp ownership

The matcher now emits this leaf as the authored
`cRSubSpeedUp::cRSubSpeedUp()` constructor and selects the owner-qualified VC6
symbol `??0cRSubSpeedUp@@QAE@XZ`. Live Windows disassembly shows the canonical
constructor sequence: call the inherited renderable constructor, install
table `0x497314`, and return the receiver in `eax`. The table's raw bytes are
`50 ee 43 00`, the little-endian address of `cRSubSpeedUp::AI` at `0x43ee50`.
The authored spelling remains exact at 7/7 instructions with both references
clean.

This ownership does not invent an activation producer. The one-instruction
`spawn_track_speedup` target remains the separately proved fold of
`cRSubGame::AddSpeedUp(cRSubLoc*, cRSubGoldy*)` and
`cRSubHover::Hover(tVector&, float)`; neither empty surface is treated as a
write into this singleton.
