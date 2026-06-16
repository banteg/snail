# initialize_ring_or_special_effect_particles @ 0x43e470

Live source map for the ten child halo sprites attached to a
`RingOrSpecialEffectParent`.

Current match: 99.35%, 153 candidate instructions versus 153 target
instructions, with 10 clean masked operands.

Evidence:

- Parent `+0x80` is the state word cleared or set by the spawner, initializer,
  and updater.
- Parent `+0x90` starts an inline array of ten `RingOrSpecialEffectParticle`
  entries with stride `0x20`.
- The child layout matches the updater and emitter scratches:
  `sprite +0x00`, `parent +0x04`, `base_position +0x08`, `phase +0x14`,
  `phase_step +0x18`, and `radius +0x1c`.
- Parent `+0x1d0` is a rate source pointer whose `+0x38` float feeds child
  orbit phase step as `rate * 0.104719758`.

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

Residual:

- Native stores `phase_step` before `parent`, while VC6 schedules the parent
  pointer store before the x87 `fstp`. This is the only remaining focused diff.

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
