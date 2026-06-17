# update_track_parcel

First structured scratch for `update_track_parcel` @ `0x4431d0`.

Recovered relationships:

- `TrackParcelRuntime::game` is a subgame-base pointer (`g_game_base +
  0x74618`), not the root game base.
- State `1` is the live bobbing pickup state. It culls behind
  `subgame+0x3be0e4`, mirrors `world_position` into the sprite, and copies the
  owner facing angle from `owner+0x370`, optionally adding `owner+0x3a0`.
- State `4` starts the collected-parcel home arc: it applies the final bob lift,
  computes distance from `subgame+0x3bf91c`, stores the normalized
  `travel_dir`, then falls into state `5`.
- State `5` interpolates back toward `subgame+0x3bf91c`, shrinks the sprite
  from `1.0` to `0.4`, and adds a sine arc along `subgame+0x3be130`.
- State `6` starts the row-display delivery arc and randomizes
  `delivery_offset`; state `7` flies from `subgame+0x3bf91c` to
  `RowEventDisplayController::widget_world_*` at `subgame+0x12727d8`, then
  calls `register_parcel_delivery()`.

The shared parcel header now names the tail as `progress`, `progress_step`,
`target_distance`, `travel_dir`, and `delivery_offset`, matching BN's existing
field evidence while using `Vector3` for the two three-float groups.

Current result: 60.14%, 260/312 instructions, with 32 clean masked operands.
The switch still lowers as a narrowed `state - 1` jump table even with explicit
empty states; avoid contorting that until the stack/local shape is closer. The
main remaining shape gap is temporary-vector staging: native reserves `0x28`
bytes and keeps `edi` live from the prologue, while the structured scratch
direct-stores several vector components and only needs `0x10` bytes.
