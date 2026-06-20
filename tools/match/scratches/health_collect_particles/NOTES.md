# health_collect_particles @ 0x43a010

Live source map for the health-pickup collection burst.

Current match:

- Exact: `100.00%`, `104/104` candidate/target instructions, with a
  `104/104` common prefix.
- All `13` masked operands audit cleanly with no unresolved or mismatched
  references.
- The burst spells the shared `Sprite` fields directly; VC6 emits the exact
  `0xb951b717` gravity constant for `-0.00019999999f`.

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

Exact closure:

- A named `Vector3` burst value makes VC6 evaluate constructor arguments in the
  native z/cosine/sine order, restores the `0x34` byte frame, spills the loop
  index to the native stack slot, and recovers the dword `0x800` flag OR.
- Declaring the angle after copying the source position preserves the native
  integer/x87 scheduling around the position copy while still compiling the
  angle calculation at its native location.
- Default-constructing `pickup_offset`, assigning x/y/z in order, and advancing
  the loop after the final position update recovers the native x87 tail and
  closes the final scheduling residual.

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
  burst velocity y/z staging regressed to 42.57%; that earlier scalar slice
  remained pinned until the later aggregate-vector shape recovered the full
  frame and register allocation.
- 2026-06-19 stack-frame probes: moving the angle calculation to the decompiler
  order, spelling the `0x800` update through an explicit flag local, and using
  a raw dword lane all stayed neutral at `66.34%` before the offset-vector
  change. The raw dword lane was not kept because it moves away from the shared
  `Sprite::flags` field without improving codegen.
- 2026-06-19 offset probes: constructing both an aggregate
  `Vector3 burst_velocity_value` and `Vector3 pickup_offset` grew the frame only
  to `0x2c` and regressed to `64.39%`. A scalar
  `offset_x/offset_y/offset_z` spelling collapsed back to the old `0x1c` frame
  and `66.34%`. Moving `++index` after the final z-store was codegen-neutral in
  that older scalar-burst shape; it becomes the exact tail only after the burst
  and pickup temporaries are recovered together.
- 2026-06-20 particle-family retry: focused Wibo still reports 69.61%,
  100/104 candidate instructions, 1/104 prefix, and 13 clean masked operands.
  An explicit `sprite_flags` local and the commuted
  `sprite->flags = 0x800u | sprite->flags` spelling are both codegen-neutral
  and still compile to the same byte-OR residual. Splitting `loop_index` from
  the loop counter is also codegen-neutral; VC6 keeps the counter in `ebp`
  instead of recovering native's stack index slot. The final exact shape keeps
  the direct flag update and single `index` local; the named burst vector
  supplies the missing register pressure.

2026-06-20 exact source-shape pass:

- Removing the duplicate angle temporary and constructing the burst as a real
  `Vector3` first raised the focused match to `93.27%` with `104/104`
  instruction-count parity. Moving the angle declaration below the
  source-position copy raised it to `97.12%`; spelling `pickup_offset` as a
  default-constructed vector with ordered component writes raised it to
  `99.04%`; moving the loop increment after the final z update produced the
  exact `100.00%`, `104/104` match with all `13` masks clean.

Type consolidation:

- `Player::health_collect_particles` now takes the promoted partial
  `TrackHealthPickup*`. The layout is still partial: `owner_game +0x44`
  and `source_cell +0x68` are intentionally separate fields.
