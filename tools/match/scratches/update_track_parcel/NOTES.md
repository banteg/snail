# update_track_parcel

Structured scratch for `update_track_parcel` @ `0x4431d0`.

Recovered relationships:

- `Parcel::owner_subgame` is a borrowed subgame-base pointer
  (`g_game_base + 0x74618`), not the root game base. Its `+0x09` byte is the
  `subgame_pause_gate` checked at entry.
- State `1` is the live bobbing pickup state. It culls behind
  `Player::interaction_max_z` at `subgame+0x3be0e4`, mirrors inherited
  `BodBase::position` into the sprite, and copies `Player::heading_roll` from
  the borrowed `owner_player`, optionally adding `follow_orientation_b` when
  `follow_active` is set.
- State `4` starts the collected-parcel home arc: it applies the final bob lift,
  computes distance from `subgame+0x3bf91c`, stores the normalized
  `travel_dir`, then falls into state `5`.
- State `5` interpolates back toward `subgame+0x3bf91c`, shrinks the sprite
  from `1.0` to `0.4`, and adds a sine arc along `subgame+0x3be130`.
- State `6` starts the row-display delivery arc and randomizes
  `delivery_offset`; state `7` flies from `subgame+0x3bf91c` to
  `Completion::widget_world_*` at `subgame+0x12727d8`, then
  calls `register_parcel_delivery()`.

The shared parcel header now models the primary authored `Parcel : BodBase`;
the exact initializer and table entry join it to Android/iOS `cRParcel::AI()`.
The fixed `ParcelManager` proves 50 owned inline records. A parcel itself only
borrows its `SubgameRuntime`, embedded `Player`, and SpriteManager sprite
handles. The tail remains named as `progress`, `progress_step`,
`target_distance`, `travel_dir`, and `delivery_offset`.

Current result: 63.79%, 290/312 instructions, prefix 8/312, with 34 clean
masked operands. Function-scope delta temporaries, staged vector results, and
the direct state 0..7 switch recover native's prologue and substantially more
of the vector-copy shape. The sole audit mismatch is real: BN proves
`0x44362c` is the target's eight-entry state jump table, but the candidate's
table entries differ because the residual control-flow tails still differ.
