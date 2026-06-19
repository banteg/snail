# update_track_health_pickup @ 0x43ecc0

Current match: 71.88%, with instruction-count parity at 128 target instructions
and 128 candidate instructions.

Recovered behavior:

- skip when the reset-initialized owner-game `subgame_pause_gate` byte at
  `+0x09` is set;
- state `0` returns immediately;
- state `2` unlinks the pickup from the shared `g_game_base + 0x5a8` bod list,
  pushes it onto the free stack, clears `0x200`, and kills the sprite;
- state `1` performs the same teardown once `world_z` falls behind
  `owner->interaction_max_z`;
- all other nonzero states advance the health bob phase, wrap only when the
  phase is strictly greater than `1.0f`, and write
  `(sine(phase * tau) + 1.0f) * 0.30000001f + world_y` to
  `sprite->position.y`.

The unlink source shape intentionally mirrors exact `update_track_speedup`
with duplicated state-1/state-2 blocks. The remaining diff is source-shape and
layout: native branches the state-1 non-removal path to a final bob tail, while
the current switch spelling places the bob tail before the state-1 duplicated
unlink block. The emitted x87 wrap condition now matches the native strict
`> 1.0f` test (`test ah, 0x41`), but the moved bob tail also shifts the final
sprite pointer register and epilogue scheduling.

Rejected source-shaped probes:

- nesting the state-1 removal block under `if (world_z < interaction_max_z)`
  recovered the native branch direction but let VC6 merge the two unlink error
  tails, regressing to 58.47% and shrinking the candidate to 108 instructions;
- spelling the state dispatch as the IDA-style `state`, `state - 1`,
  `state - 2` ladder similarly merged duplicate unlink blocks and regressed to
  56.54%;
- an explicit `state_one_remove` label emitted the same merged 58.47% layout.

2026-06-19 branch-layout retry:

- spelling the state-one guard as `!(world_z < interaction_max_z)` is
  codegen-neutral at 71.88%; VC6 simplifies it back to the pinned
  bob-before-removal layout with `jne` into the state-one unlink block;
- retesting the structured `if (world_z < interaction_max_z) { remove; }`
  form still recovers the native `je` around the state-one unlink block but
  merges the duplicated unlink error tails, reproducing the 58.47%,
  108-instruction regression;
- adding explicit local labels around the state-two error exits does not
  prevent the merge and further regresses to 58.97%/106 instructions by
  changing the state-two branch polarity. Keep the speedup-shaped duplicated
  blocks until a structured spelling preserves both native branch polarity and
  the duplicated error exits.

Keep this pinned unless a source-plausible dispatch spelling preserves both the
duplicated unlink blocks and the native final bob-tail placement.

2026-06-16 type cleanup: this now uses the shared partial
`TrackHealthPickup` layout from `track_health_pickup.h`, including the shared
`BodNode` list prefix from `bod_list.h`. Match remains 71.88%.

2026-06-16 initializer consolidation: `initialize_track_health_pickup_runtime`
now uses this same promoted `TrackHealthPickup` type, while casting through
`BodBase` for the exact initializer and vtable write. The first `0x38` bytes are
therefore both the BOD base prefix at initialization time and the pickup
world/state payload used by spawn/update/collision paths.

Important naming correction: reset_subgame initializes health pickup `+0x44`
with the `Game*`, so this lane is now `owner_game`, not a visibility-cell
pointer. `spawn_track_health_pickup` stores the row/source cell at
`source_cell +0x68`. Do not collapse those into one `source_cell` field.
Do not merge health and jetpack into one full pickup struct either: both use
the owner-game pause view at `+0x44`, while jetpack has embedded renderable
bodies below `+0x74`.

2026-06-18 owner-game rename: the earlier `TrackVisibilityCell` interpretation
was invalidated by reset_subgame, which writes the containing `Game*` into
`+0x44` for every health pickup slot. The update check is the same pause-byte
view used by speedup and jetpack pickups.

2026-06-18 pickup pause-view consolidation: speedup, health, and jetpack
pickups now share `TrackPickupOwnerSubgameView`. The `+0x09` byte is named
`subgame_pause_gate`, distinguishing this embedded subgame update gate from the
global/UI `Game::pause_gate` view at root `+0x74621`.
