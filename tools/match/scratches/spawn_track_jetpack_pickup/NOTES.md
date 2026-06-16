# spawn_track_jetpack_pickup @ 0x43d890

Live source map for `cRSubGame::AddJetPack(cRSubLoc*, cRSubGoldy*)`.

Current match:

- `55.52%`, `137/144` candidate/target instructions, with `8` masked
  operands ok.
- This is a first live scratch. The offsets below are useful; the remaining
  mismatch is mostly scheduling/register shape in the scan, position staging,
  list splice, and parity tail.

Evidence:

- Allocates the single jetpack pickup runtime at `game + 0x355e64`.
- The collision-visible lanes are `position +0x10`, `state +0x38`,
  `owner +0x3c`, `sprite +0x64`, `source_cell +0x68`, `bob_phase +0x6c`,
  and `bob_phase_step +0x70`, matching the corrected
  `handle_subgoldy_collisions` offsets `position 0x355e74` and
  `state 0x355e9c`.
- The runtime footprint is `0x19c`; `initialize_track_jetpack_pickup_runtime`
  proves the parent has two embedded renderable bodies beyond the
  collision/spawn prefix.
- The lateral `x` correction is lane/tile dependent: lane `3` shifts `+0.5`
  when the neighboring row bytes are `14`; lane `4` shifts `-0.5` for the
  mirrored neighbors.
- Sprite texture `124` is allocated at size `1.5`, and the bob phase uses the
  same numeric float-to-int parity test seen in the health pickup spawner.

Do not promote a full `TrackJetpackPickup` header from this alone. The exact
`update_track_jetpack_pickup` scratch is still modeled from a different local
view and needs reconciliation with this spawn/initializer prefix.
