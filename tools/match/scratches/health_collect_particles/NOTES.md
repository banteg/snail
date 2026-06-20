# health_collect_particles @ 0x43a010

Live source map for the health-pickup collection burst.

Current match:

- `69.61%`, `100/104` candidate/target instructions, with `13` masked operands
  ok and no masked mismatch.
- The burst now spells the shared `Sprite` fields directly; VC6 still emits
  the exact `0xb951b717` gravity constant for `-0.00019999999f`.

Evidence:

- The function only emits particles when render flag `0x10` is set.
- It spawns eight sprite `0x80` particles owned by `Player::player_slot`.
- The helper is modeled as `void`: the only tracked caller ignores the return.
  Native still loads `g_render_flags` into `al` for the render gate, and the
  success path leaves incidental loop/index state in registers, but that is not
  a gameplay return value.
- The particles use the shared `Sprite` fields: `flags`, `color`, `position`,
  `velocity`, `size_start`, `size_end`, `progress`, `progress_step`, and
  `gravity_step`.
- The source pickup is the shared partial `TrackHealthPickup`; it contributes
  the initial sprite position through `sprite` at pickup `+0x64`.
- The stale build-only draft used `scale_x/scale_y`; this live scratch uses the
  corrected `size_start/size_end` names because those fields are interpolated
  by `draw_sprite_quad`.
- 2026-06-16 Sprite-field consolidation: rewriting the hot initialization block
  from raw word/byte lanes to direct `Sprite` fields raised the focused match
  from `43.56%` to `62.07%` and removed the lone masked mismatch. Keep the
  direct field spelling here; this callsite confirms `flags`, `color`,
  `position`, `velocity`, `size_start`, `size_end`, `progress`,
  `progress_step`, and `gravity_step` together.
- 2026-06-16 return-type correction: changing the shared declaration and
  scratch implementation from `char` to `void` improves focused Wibo from
  `62.07%` to `66.34%` while leaving the sole known caller
  `handle_subgoldy_collisions` unchanged. This matches the garbage smoke and
  ring star emitter pattern: ignored particle helpers can leave incidental
  register values without exposing a meaningful source-level return.
- 2026-06-19 offset-vector stack audit: spelling the player velocity offset as
  a real `Vector3 pickup_offset` raises the focused match from `66.34%` to
  `69.61%`, grows the candidate frame from `0x1c` to `0x28`, and moves the
  candidate length from `98/104` to `100/104`. This is the only retained
  stack-shape improvement from this audit.

Remaining mismatch:

- Native uses a `0x34` byte stack frame, keeps `this` in `ebx`, and updates the
  loop index through the stack slot. The current candidate uses a `0x28` byte
  frame, keeps `this` in `ebx`, but still keeps the loop index in `ebp`. The
  mismatch is now mostly the remaining stack-frame/register allocation and the
  dword-vs-byte flag OR.

Rejected source-shape probes:

- Spelling the `0x800` sprite flag update through an explicit
  `unsigned int flags` local regressed to 37.81% and still compiled as a byte
  OR, so keep the direct word-lane OR used by the current scratch.
- 2026-06-16 retest after Sprite field-name consolidation: the explicit
  `unsigned int flags` local is now score-neutral at `62.07%`, but it still
  compiles to the same byte OR and does not recover the native dword OR or
  frame shape. Keep the direct `sprite->flags |= 0x800u` spelling.
- 2026-06-16 pickup/Sprite slice: spelling the loop result as a post-loop
  assignment after `++index` raises the focused match from 43.35% to 43.56%
  and better reflects native's increment-before-final-z-store order. Explicit
  burst velocity y/z staging regressed to 42.57%, so keep the direct velocity
  stores.
- 2026-06-19 stack-frame probes: moving the angle calculation to the decompiler
  order, spelling the `0x800` update through an explicit flag local, and using
  a raw dword lane all stayed neutral at `66.34%` before the offset-vector
  change. The raw dword lane was not kept because it moves away from the shared
  `Sprite::flags` field without improving codegen.
- 2026-06-19 offset probes: an aggregate `Vector3 burst_velocity_value` plus
  `Vector3 pickup_offset` grew the frame only to `0x2c` and regressed to
  `64.39%`. A scalar `offset_x/offset_y/offset_z` spelling collapsed back to
  the old `0x1c` frame and `66.34%`. Moving `++index` after the final z-store
  was neutral at `69.61%` but made the tail less like native, so the increment
  stays before the z assignment.
- 2026-06-20 particle-family retry: focused Wibo still reports 69.61%,
  100/104 candidate instructions, 1/104 prefix, and 13 clean masked operands.
  An explicit `sprite_flags` local and the commuted
  `sprite->flags = 0x800u | sprite->flags` spelling are both codegen-neutral
  and still compile to the same byte-OR residual. Splitting `loop_index` from
  the loop counter is also codegen-neutral; VC6 keeps the counter in `ebp`
  instead of recovering native's stack index slot. Keep the current direct
  flag update and single `index` local until a stronger register-pressure or
  source-idiom lead appears.

Type consolidation:

- `Player::health_collect_particles` now takes the promoted partial
  `TrackHealthPickup*`. The layout is still partial: `owner_game +0x44`
  and `source_cell +0x68` are intentionally separate fields.
