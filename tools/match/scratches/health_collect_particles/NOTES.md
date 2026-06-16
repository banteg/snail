# health_collect_particles @ 0x43a010

Live source map for the health-pickup collection burst.

Current match:

- `43.56%`, `98/104` candidate/target instructions, with `11` masked operands
  ok and one schedule-induced masked mismatch.
- The gravity lane is stored with raw bits `0xb951b717` to match the native
  constant exactly.

Evidence:

- The function only emits particles when render flag `0x10` is set.
- It spawns eight sprite `0x80` particles owned by `Player::player_slot`.
- Native returns `char`, not `int`; the skipped path returns the render-flag
  byte loaded from `g_render_flags`.
- The particles use the shared `Sprite` fields: `flags`, `color`, `position`,
  `velocity`, `size_start`, `size_end`, `progress`, `progress_step`, and
  `gravity_step`.
- The source pickup is the shared partial `TrackHealthPickup`; it contributes
  the initial sprite position through `sprite` at pickup `+0x64`.
- The stale build-only draft used `scale_x/scale_y`; this live scratch uses the
  corrected `size_start/size_end` names because those fields are interpolated
  by `draw_sprite_quad`.
- The current source uses word-copy lanes in the hot sprite initialization block
  to keep VC6 closer to native scheduling while preserving the typed
  `TrackHealthPickup*` and allocated `Sprite*` relationships.

Remaining mismatch:

- Native uses a `0x34` byte stack frame, keeps `this` in `ebx`, and updates the
  loop index through the stack slot. The current candidate uses a `0x1c` byte
  frame, keeps `this` in `ebp`, and keeps the loop index in `ebx`, so VC6 still
  sinks the angle multiply into the lane where native multiplies
  `velocity.z * 0.400000006f`.

Rejected source-shape probes:

- Spelling the `0x800` sprite flag update through an explicit
  `unsigned int flags` local regressed to 37.81% and still compiled as a byte
  OR, so keep the direct word-lane OR used by the current scratch.
- 2026-06-16 pickup/Sprite slice: spelling the loop result as a post-loop
  assignment after `++index` raises the focused match from 43.35% to 43.56%
  and better reflects native's increment-before-final-z-store order. Explicit
  burst velocity y/z staging regressed to 42.57%, so keep the direct velocity
  stores.

Type consolidation:

- `Player::health_collect_particles` now takes the promoted partial
  `TrackHealthPickup*`. The layout is still partial: `visibility_cell +0x44`
  and `source_cell +0x68` are intentionally separate fields.
