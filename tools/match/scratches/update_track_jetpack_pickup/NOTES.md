# update_track_jetpack_pickup @ 0x43efb0

Pinned at `72.44%`, `127/127` candidate/target instructions, masked operands
`15 ok / 0 mismatch`.

2026-06-16 vtable correction: this is the jetpack pickup parent updater, not
the sub-lazer projectile updater. `initialize_track_jetpack_pickup_runtime`
installs parent vtable `data_497318`, and `data_497318` points at `0x43efb0`.
The same parent slot starts at `game + 0x355e64`.

Layout facts now shared with `track_jetpack_pickup.h`:

- parent list prefix at `+0x00`, with live/free-list flags at `+0x04`
- world position at `+0x10`; the updater uses y as the sprite bob base and
  z for the owner kill-plane compare
- state `+0x38`, owner `+0x3c`, owner game/paused view `+0x44`
- sprite `+0x64`, source row cell `+0x68`, bob phase/step `+0x6c/+0x70`
- embedded renderable bodies at `+0x74` and `+0x108`, initialized by the
  constructor but not directly advanced by this updater

The remaining diff is block layout/register allocation in the duplicated
remove paths and bob tail, not a known semantic gap.

2026-06-16 pickup/Sprite slice: the scratch-local `FreeAnchor` duplicate was
removed in favor of the shared `BodList` view from `bod_list.h` via
`track_jetpack_pickup.h`. Focused Wibo remains 72.44%, 127/127 insns, with
15 masked operands OK and no unresolved or mismatched operands.

2026-06-17 symbol sync: the tracked IDA/BN decompile exports and the live BN
session now name `0x43efb0` as `update_track_jetpack_pickup`, matching the
gameplay manifest and this scratch. The old shifted labels at `0x43ee50` and
`0x43efb0` were corrected as part of the pickup/sub-lazer vtable cleanup.

2026-06-16 bob-tail layout retry: inverting the state-1 z test so the removal
block was nested under `world_position.z < owner->interaction_max_z` regressed
to `58.12%` (`107/127`). VC6 merged the two unlink blocks just like the health
pickup rejection notes warned. Keep the duplicated state-1/state-2 unlink
source shape; the remaining bob-tail placement is layout debt, not a reason to
change the semantic branch.
