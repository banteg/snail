# initialize_ring_or_special_effect_particles @ 0x43e470

Live source map for the ten child halo sprites attached to a `SubRing`.

Current match: 100.00%, 153/153 instructions, with 10 clean masked operands.

Evidence:

- Parent `+0x80` is the state word cleared or set by the spawner, initializer,
  and updater.
- Parent `+0x90` starts an inline array of ten `SubRingStar` entries with
  stride `0x20`.
- The child layout matches the updater and emitter scratches:
  `sprite +0x00`, `parent +0x04`, `base_position +0x08`, `phase +0x14`,
  `phase_step +0x18`, and `radius +0x1c`.
- Parent `+0x1d0` borrows its enclosing `SubgameRuntime`; that owner's
  `subgame_rate +0x38` feeds child orbit phase step as
  `rate * 0.104719758`.
- The scratch includes `subgame_runtime.h` directly because dereferencing that
  backlink requires the complete owner definition; a forward declaration in
  the ring layout header is intentionally sufficient only for storage.

Source-shape win:

- Spelling the loop as `RingOrSpecialEffectParticle* particle = &particles[i]`
  inside the body, instead of holding a `particle++` cursor, matches the native
  state/counter stores before the particle setup and removes the extra carried
  `ebx += 0x20` induction update. This improves the focused match from 96.42%
  to 98.69% and raises the prefix from 8 to 21 instructions.
- Spelling the `base_position` copy through a local destination pointer,
  `Vector3* base_position = &particle->base_position`, recovers native's
  copy-before-radius schedule and improves the focused match from 98.69% to
  99.35%.
- Spelling `phase_step` through a pointer-to-field local (`float* phase_step =
  &particle->phase_step; *phase_step = ...`) forces the native x87 spill before
  the parent pointer store without changing semantics. Focused Wibo is now
  100.00%, 153/153, with 10 clean masked operands.

Rejected/source-shape probes:

- Splitting the `particle = particles` assignment from its declaration compiled
  identically; VC6 still hoisted `lea esi, [this + 0x90]` ahead of the state
  stores.
- Spelling the state store as `state = i + 1` also compiled identically. The
  residual is pointer scheduling, not uncertainty about the `state` field.
- Introducing a local `phase_step` compiled identically after the indexed-loop
  fix, so it was reverted as source-neutral churn.
- Rewriting `base_position = *parent_position` as explicit x/y/z field copies
  regressed to 50.33% by changing register ownership across the whole loop.
- Moving the `parent` assignment after the local `base_position` pointer
  declaration compiled identically at 99.35%, so keep the clearer source order.

Type consolidation:

- `RingOrSpecialEffectParent` now inherits shared `RenderableBod`, carries the
  initializer-used `state` and `rate_source` fields in the shared header, and
  asserts the pool stride as `0x1f8`. Known fields end at `0x1f0`, so the final
  `8` bytes remain explicit tail padding.
- 2026-06-17 renderable inheritance correction: parent `position +0x68` is now
  consumed as `transform.position` from the inherited `RenderableBod`. The
  runtime initializer, spawner identity-matrix write, child initializer, child
  updater, parent virtual updater, and collision consumer all agree on this
  transform block.
- `RingOrSpecialEffectParticle` is now promoted in the shared header, and parent
  `+0x90..+0x1cf` is modeled as `particles[10]`. The updater method is modeled
  as `void` because its native return is not consumed by any known caller; the
  emitter remains byte-return shaped.
- 2026-06-16 child-stride assertion: the shared header now asserts
  `sizeof(RingOrSpecialEffectParticle) == 0x20`, matching this initializer's
  ten-entry loop and the updater/emitter consumers.
- 2026-06-16 correction: `+0x80` is named `state`, not `active`; the virtual
  updater confirms it is a multi-state lane rather than a boolean.
- 2026-06-16 lives-snapshot correction: the ignored `ret 0x4` argument is the
  same `Player::lives` snapshot passed by the ring spawner. The initializer
  still does not consume it, but the signature is now an ignored integer rather
  than a fake pointer.

## 2026-07-11 authored owner promotion

- iOS and Android preserve this owner family as `cRSubRing::Init(int)`; the
  shared Windows type is now `SubRing`.
- The ten inline children are authored `SubRingStar` records, matching the
  cross-port `cRSubRingStar::AI()` and `Shower()` symbols. The historical
  combined-effect names remain compatibility aliases only.
- The method stays exact at 153/153 instructions with ten clean operands.

## 2026-07-13 Sprite consumer ownership recovery

- Restoring the complete live `Sprite` definition recovers the child sprite's
  `draw_mode`, `color`, flags, animation progress, size, position, gravity, and
  facing fields in the tracked Binary Ninja artifact.
- The same repair restores typed `Sprite` velocity/position ownership in
  `emit_ring_star_shower` and the position owner in the child updater.
- These are analysis-only ownership gains: the exact 153/153 initializer
source and its native bytes are unchanged.

## 2026-07-14 particle extent derivation

The child initializer now derives its terminal bound from the owned
`SubRing::particles` array. Its normalized listing remains byte-identical
(`a8c10dd83dfdc6db3bc0dd25b8b9709dd1e0c0b973e1f28ebabb14d9482adcc4`)
and exact at 153/153 instructions with ten clean operands.

## 2026-07-14 ring kind and lifecycle ownership

The initializer now consumes `SubRingKind` for its normal, explode, and slow
sprite-family dispatch and writes `SUB_RING_STATE_ACTIVE`. This is type-only:
the scratch remains exact at 153/153 instructions with ten clean operands.
