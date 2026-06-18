# Track health pickup layout notes (2026-06-16)

This is a partial promoted layout, not a full object recovery. The useful
correction after matching `reset_subgame` is that the health pickup has a
game-view pointer and a separate row/source-cell pointer:

- `owner_game +0x44`: initialized by `reset_subgame` with the containing
  `Game*` and read by `update_track_health_pickup` for the pause byte at `+0x09`.
- `source_cell +0x68`: written by `spawn_track_health_pickup` from the row cell
  argument. This is distinct from the owner-game pause view.

Evidence anchors:

- `initialize_track_health_pickup_runtime` installs the health pickup vtable
  after the shared bod base initializer.
- `spawn_track_health_pickup` scans the eight-slot pool at `game + 0x356000`,
  stride `0x74`, seeds `world_position +0x10`, `state +0x38`, `owner +0x3c`,
  `sprite +0x64`, `source_cell +0x68`, and bob fields `+0x6c/+0x70`. Its live
  scratch stages the row-cell position through a normal `Vector3` local,
  matching the native stack-frame shape.
- `reset_subgame` seeds `owner_game +0x44` for all eight slots and proves this
  lane is a game pause view, matching speedup and jetpack pickup ownership.
- `update_track_health_pickup` reads `owner_game +0x44`, `state +0x38`,
  `owner +0x3c`, `sprite +0x64`, `world_position.y/z`, and bob fields
  `+0x6c/+0x70`.
- `health_collect_particles` now takes `TrackHealthPickup*` and reads
  `sprite +0x64` as the source position for the eight-particle collection burst.
- `handle_subgoldy_collisions` iterates the health slots with stride `0x74`,
  sets `state +0x38` to `2`, and calls `health_collect_particles` with
  `game + 0x356000 + slot_offset`.

Current promoted fields live in `tools/match/include/track_health_pickup.h`.
Keep the struct partial until another function explains the unknown lane around
`+0x40..+0x48` beyond the owner-game pause view and row source split.
