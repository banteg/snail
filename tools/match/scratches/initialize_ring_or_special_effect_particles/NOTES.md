# initialize_ring_or_special_effect_particles @ 0x43e470

Live source map for the ten child halo sprites attached to a
`RingOrSpecialEffectParent`.

Current match: 96.42%, 154 candidate instructions versus 153 target
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

Residual:

- MSVC hoists the child pointer setup before the native state stores and keeps
  the child base-position pointer live across loop iterations (`add ebx,
  0x20`). Native writes `state` and `star_shower_counter` first and recomputes
  `child + 0x08` inside each iteration.

Type consolidation:

- `RingOrSpecialEffectParent` now carries the initializer-used `state` and
  `rate_source` fields in the shared header.
- `RingOrSpecialEffectParticle` is now promoted in the shared header, and parent
  `+0x90..+0x1cf` is modeled as `particles[10]`. The updater method is modeled
  as `void` because its native return is not consumed by any known caller; the
  emitter remains byte-return shaped.
- 2026-06-16 correction: `+0x80` is named `state`, not `active`; the virtual
  updater confirms it is a multi-state lane rather than a boolean.
