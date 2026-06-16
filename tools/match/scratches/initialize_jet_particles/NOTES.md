# initialize_jet_particles

Initial scratch for the jetpack hover-particle initializer.

Recovered relationships:

- `JetpackGaugeController::particle_slots` is a 15x2 grid at `+0x20`; each
  `JetParticleSlot` is 0x10 bytes.
- each slot owns a sprite pointer at `+0x00` and three local particle lanes at
  `+0x04/+0x08/+0x0c`.
- allocated sprite id is `0x9e`, owner bucket is `1`, and the sprite uses the
  shared `Sprite` fields for flags, progress/lifetime, size, velocity, gravity,
  color, and draw mode.
- Focused Wibo result after Sprite-field source shaping: 97.96%, 74/73
  candidate/target instructions, with 3 masked operands OK. The accepted shape
  uses an explicit `flags` local for the `0x800` OR, clears
  `Sprite::velocity` through a local `Vector3*` in z/y/x order, and places
  `draw_mode` between the slot `wobble_x` and `wobble_y` stores. This recovers
  the native saved-register and vector-zero schedule while keeping the shared
  `Sprite` field names.

Rejected/source-shaped probes:

- Incrementing the particle-slot pointer before the tail stores looked closer
  to native's `add esi, 0x10` schedule, but it made VC6 keep the inner column
  count in `ebp`, displaced the `0.166666672f` alpha constant, and regressed to
  87.07%. Keep the current clearer tail spelling; the remaining miss is only
  the `wobble_x` store versus sprite reload order plus a redundant final
  `xor eax, eax`.
