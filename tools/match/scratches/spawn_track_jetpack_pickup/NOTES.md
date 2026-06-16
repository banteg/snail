# spawn_track_jetpack_pickup @ 0x43d890

Live source map for `cRSubGame::AddJetPack(cRSubLoc*, cRSubGoldy*)`.

Current match:

- `52.86%`, `136/144` candidate/target instructions, with `9` masked
  operands ok.
- The scratch now uses the promoted `TrackJetpackPickup` field names and the
  shared `BodList`/`BodNode` active-list shape. Prefix improves to `25/144`;
  the remaining mismatch is mostly the choice to base `esi` at the pickup slot
  rather than at `game + slot_index * 0x19c`.

Evidence:

- Allocates the single jetpack pickup runtime at `game + 0x355e64`; the
  shared parent layout now lives in `track_jetpack_pickup.h`.
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
- The active-list add path matches the same insertion semantics as health:
  insert the pickup before the old first node, clear the new head's prev link,
  and set the `0x200` linked bit.

2026-06-16 vtable correction: the earlier "different local view" was a shifted
symbol assumption. `0x43efb0` is the jetpack pickup updater installed by the
parent vtable, while the exact `0x43ee50` updater belongs to the speedup
singleton.
