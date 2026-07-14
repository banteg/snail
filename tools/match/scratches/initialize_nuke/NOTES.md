# initialize_nuke

- Near-exact/source-shaped match: 93.75%, 64/64 instructions.
- Uses typed `Nuke`, `Player`, `SubgameRuntime`, `SpriteManager`, and
  `Sprite` layouts. This pins the owner player pointer, `subgame_rate` read
  through `GameRoot::subgame`, orbit center-z/phase
  fields, and the 25 sprite slots at controller `+0x18`.
- Semantics: inactive state allocates 25 sprite id `0x83` entries for the
  owner's player slot, sets sprite flag `0x800`, clears sprite progress,
  progress step, gravity, position, and velocity lanes, seeds `3.0f` size, sets
  phase step `0.104719758f`, and dispatches `update_nuke()`. Already-active
  state skips allocation and still dispatches `update_nuke()`.
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
- 2026-06-19 shared signature audit: modeling `initialize_nuke` and
  `update_nuke` as side-effect-only `void` methods lets `update_nuke` exact
  match with the label-shaped state switch used by other exact updaters.
  `initialize_nuke` remains at the same 93.75% residual, so the signature change
  is accepted as shared lifecycle evidence rather than a local initializer fix.
- 2026-06-19 slot-expression audit: focused Wibo still reports 93.75%,
  64/64 instructions, 30/64 prefix, and 5 clean masked operands. The native and
  retained candidate match exactly through the allocator call and slot store;
  only the flag temporary (`edx` native versus `ecx` candidate) and the adjacent
  `3.0f` materialization order differ. Rewriting the allocation as
  `*slots = allocate; (*slots)->flags |= 0x800`, as
  `Sprite* sprite = *slots = allocate`, and as an assignment-expression plus an
  explicit flag local is codegen-neutral. Moving the visible increment earlier,
  including `*slots++ = sprite`, schedules the OR after the slot advance and is
  weaker evidence even though the score stays 93.75%. Keep the retained
  store/flag/increment spelling; the remaining lead needs a different
  source-owner clue, not more slot expression reshuffling.
- 2026-06-19 lane-store retry: focused Wibo still reports 93.75%, 64/64
  instructions, 30/64 prefix, and 5 clean masked operands. Replacing the
  progress/size stores with one raw `unsigned int*` view of `*(slots - 1)`
  regresses to 75.20% by collapsing native's repeated slot reloads and
  changing the tail zeroing schedule. A narrower size-bit store form is
  codegen-neutral, as is spelling the flag assignment as
  `sprite->flags = sprite->flags | 0x800`. Keep the typed progress/size stores
  and direct `|=` flag expression.

## Authored cRNuke owner (2026-07-11)

Android `cRNuke::Init()` uses the same exact Windows layout: state +0x00,
non-owning cRSubGoldy backlink +0x04, orbit z step/center +0x08/+0x0c,
phase/step +0x10/+0x14, and 25 sprite pointers from +0x18 through +0x78.
`cRSubGoldy::Collision()` calls it through that embedded 0x7c-byte owner. The
shared type is now `Nuke`, and the analysis prototypes correctly preserve the
side-effect-only `void` contract. Focused Wibo remains an honest 93.75%, 64/64
instructions, prefix 30/64, with five clean masked operands.
