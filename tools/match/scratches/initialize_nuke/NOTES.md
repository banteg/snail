# initialize_nuke

- Near-exact/source-shaped match: 93.75%, 64/64 instructions.
- Uses typed `NukeController`, `Player`, `SubgameRuntime`, `SpriteManager`, and
  `Sprite` layouts. This pins the owner player pointer, `subgame_rate` read
  through the embedded subgame at `root+0x74618+0x38`, orbit center-z/phase
  fields, and the 25 sprite slots at controller `+0x18`.
- Semantics: inactive state allocates 25 sprite id `0x83` entries for the
  owner's player slot, sets sprite flag `0x800`, clears sprite progress,
  progress step, gravity, position, and velocity lanes, seeds `3.0f` size, sets
  phase step `0.104719758f`, and tail-calls `update_nuke()`. Already-active
  state skips allocation and still tail-calls `update_nuke()`.
- Residual: four instructions differ after each `allocate_sprite` call. Native
  uses `edx` for the sprite flag OR and reloads the just-stored slot into `ecx`
  before materializing the `3.0f` bit pattern in `eax`; VC6 emits the equivalent
  flag OR through `ecx` and loads the `3.0f` constant before the slot reload.
- Rejected no-op/source variants: a `register` flag temporary and a named
  first-store `current` sprite plus `sprite_scale` local did not improve the
  match. Keep the direct flag OR and vector-pointer zeroing unless stronger
  original-source evidence appears.
- 2026-06-18 name correction: `orbit_axis`/`orbit_axis_step` were too vague.
  `initialize_nuke` seeds the value from the owner's current z minus 5, and
  `update_nuke` writes it into every sprite's `position.z`, so the shared
  fields are now `orbit_center_z` and `orbit_center_z_step`. The angular fields
  are `orbit_phase` and `orbit_phase_step`.
- 2026-06-19 flag/size scheduling audit: focused Wibo still reproduces 93.75%,
  64/64 instructions, 30/64 prefix, and 5 clean masked operands. Explicit
  unsigned and signed flag locals still used `ecx` for the flag OR; the signed
  form also moved the OR after the slot increment. A `flag_sprite` alias is
  codegen-neutral. A `current = *(slots - 1)` pointer recovers the native `edx`
  flag temporary, but regresses to 53.33% by collapsing the deliberate slot
  reloads and changing saved-register ownership. Chaining the two `3.0f` size
  assignments regresses to 90.62% by reversing the `size_start`/`size_end` store
  order, while a separate `sprite_size` local is codegen-neutral. Keep the raw
  slot-reload spelling and direct `3.0f` stores.
