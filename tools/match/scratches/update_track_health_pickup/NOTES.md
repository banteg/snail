# update_track_health_pickup @ 0x43ecc0

Current match: 71.88%, with instruction-count parity at 128 target instructions
and 128 candidate instructions.

Recovered behavior:

- skip when shared `TrackVisibilityCell +0x09` is hidden;
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

Important naming correction: the update hidden check reads
`visibility_cell +0x44`, while `spawn_track_health_pickup` stores the row/source
cell at `source_cell +0x68`. Do not collapse those into one `source_cell` field.
Do not merge health and jetpack into one full pickup struct either: health has
a visibility-cell gate at `+0x44`, while jetpack uses that lane for the owner
game/paused view and has embedded renderable bodies below `+0x74`.

2026-06-16 visibility-gate rename: the old `TrackRuntimeCell` name in
`track_runtime.h` was too broad and easy to confuse with the full 0x54-byte
`TrackRowCell` runtime-grid record used by spawners and attachment paths. It is
now `TrackVisibilityCell`, a narrow view for the `hidden +0x09` gate only.
