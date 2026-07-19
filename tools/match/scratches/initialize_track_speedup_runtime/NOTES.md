# initialize_track_speedup_runtime

`initialize_track_speedup_runtime` @ 0x4084b0 is the exact seven-instruction
Windows constructor for the authored `SubSpeedUp` (`cRSubSpeedUp` cross-port)
singleton at `SubgameRuntime +0x355db0`. It constructs the inherited
`RenderableBod`, installs table `0x497314`, and returns the receiver. That
table's sole entry is the exact `update_track_speedup` @ 0x43ee50.

The complete object is 0xb4 bytes and ends exactly at the adjacent
`JetPack +0x355e64`, matching the native `Size of cRSubSpeedUp` ledger.
`TrackSpeedupRuntime` remains only a compatibility alias.

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
