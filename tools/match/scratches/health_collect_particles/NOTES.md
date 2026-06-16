# health_collect_particles @ 0x43a010

Live source map for the health-pickup collection burst.

Current match:

- `37.56%`, `93/104` candidate/target instructions, with `11` masked operands
  ok and one schedule-induced masked mismatch.
- The gravity lane is stored with raw bits `0xb951b717` to match the native
  constant exactly.

Evidence:

- The function only emits particles when render flag `0x10` is set.
- It spawns eight sprite `0x80` particles owned by `Player::player_slot`.
- The particles use the shared `Sprite` fields: `flags`, `color`, `position`,
  `velocity`, `size_start`, `size_end`, `progress`, `progress_step`, and
  `gravity_step`.
- The source pickup contributes the initial sprite position through its
  `Sprite*` at pickup `+0x64`.
- The stale build-only draft used `scale_x/scale_y`; this live scratch uses the
  corrected `size_start/size_end` names because those fields are interpolated
  by `draw_sprite_quad`.

Type consolidation:

- `Player::health_collect_particles` is declared in `player.h` with a generic
  pickup pointer. The pickup-side struct is intentionally local until more
  health-pickup callsites agree on the full layout.
