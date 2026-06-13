# create_golb

create_golb @ 0x415280 initializes one live Golb projectile slot from Goldy's
movement-flag family and emitter slot.

Recovered semantics covered by this scratch:

- clears the one-tick skip and slug-bounce bytes, then links the slot into the
  shared active body list unless it is already linked;
- classifies `player+0x338` movement flags into Golb kind `0`, `1`, or `2`;
- initializes the live matrix, state, owner pointer, and spawn position from
  `player+0x68..0x70` plus half extents at `player+0x58..0x60`;
- handles all movement-flag spawn-anchor families used by
  `update_movement_flag_emitters`: side offsets at `+0x4134/+0x414c/+0x4164`,
  attachment lanes at `+0x417c/+0x4188`, and the rocket lane at `+0x41ac`;
- seeds velocity from `player+0x418`, including the side-biased `+/-0.1`,
  `+/-0.5` x offsets, kind `1` velocity doubling, and kind `2` `0.8` scale;
- copies velocity to direction, sets per-kind lifetime step from game rate,
  and routes kind `0` through sprite allocation, kind `1` through vapour setup,
  and kind `2` through the exact `search_path_for_golb` helper;
- seeds the embedded follow state from `player+0x384` when the active player
  follow lane is available, otherwise clears it and installs the `-1.0f`
  path-entry z latch;
- stores the velocity magnitude into `path_factor`, copies the starting
  position to the previous-output vector, and dispatches through the slot
  vtable just like the native tail.

Residuals:

- Current matcher result: 27.93% (`tools/match/match.sh
  tools/match/scratches/create_golb --full`).
- Remaining diff is dominated by source-shape, especially the branchy
  movement-flag selector. Native keeps a compact fallthrough tree with several
  shared velocity-staging labels; the scratch uses clearer C++ branches.
- Native stages several vector copies through stack locals and callee-saved
  registers. The scratch writes most `Vec3` fields directly, so register choice
  and stack frame use differ even where the same fields are covered.
- The sprite path's position copy now uses whole-`Vec3` assignment, improving
  local pointer-copy shape. The same source shape was tested and rejected for
  the velocity-to-direction copy (27.21% -> 21.10%) and previous-output copy
  (27.21% -> 26.99%) in isolated trials, so keep those as explicit field stores
  unless a broader source-shape change changes the surrounding register
  allocation.
- The kind-specific setup lanes are complete, but vapour/list insertion,
  sprite color copy, and path-search hit handling still differ in local
  ordering. Do not add dummy temporaries solely to force those byte layouts
  without stronger source evidence.
