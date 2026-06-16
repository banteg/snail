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
- Focused Wibo result after pointer-loop shaping: 86.49%, 75/73
  candidate/target instructions, with 3 masked operands OK. The remaining
  residual is register choice around the sprite flags zero lane, vector zero
  stores, and a redundant final `xor eax, eax`.
