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

2026-06-16 live BN symbol audit: the open BN database still resolves
`update_track_jetpack_pickup` by name to `0x43ee50`, which is the exact
speedup updater by vtable and field window. Use the manifest/dashboard target
address `0x43efb0` for this jetpack parent updater unless the BN symbols are
renamed; `0x43efb0` may also appear under the stale sub-lazer name in BN.
