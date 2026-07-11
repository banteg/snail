# initialize_jet_particles

Initial scratch for the jetpack hover-particle initializer.

Recovered relationships:

- `SubHover::particle_slots` is a 15x2 grid at `+0x20`; each
  `JetParticleSlot` is 0x10 bytes.
- each slot owns a sprite pointer at `+0x00` and three local particle lanes at
  `+0x04/+0x08/+0x0c`.
- allocated sprite id is `0x9e`, owner bucket is `1`, and the sprite uses the
  shared `Sprite` fields for flags, progress/lifetime, size, velocity, gravity,
  color, and draw mode.
- Focused Wibo result: 100%, 73/73 instructions, with 3 masked operands OK.
  The accepted shape uses an explicit `flags` local for the `0x800` OR, clears
  `Sprite::velocity` through a local `Vector3*` in z/y/x order, stores
  `wobble_x` through a local `float*`, and places `draw_mode` between the slot
  `wobble_x` and `wobble_y` stores. This recovers the native saved-register
  and vector-zero schedule while keeping the shared `Sprite` field names.
- The callee is modeled as the authored void `SubHover` member; converting the
  former fastcall-shaped surface and its caller to direct member calls remains
  exact in both functions.
- 2026-06-16 layout assertion pass: `sub_hover.h` now asserts
  `sizeof(JetParticleSlot) == 0x10`. This matches the exact initializer's
  30-slot walk and the exact uninitializer's kill loop.

Rejected/source-shaped probes:

- Incrementing the particle-slot pointer before the tail stores looked closer
  to native's `add esi, 0x10` schedule, but it made VC6 keep the inner column
  count in `ebp`, displaced the `0.166666672f` alpha constant, and regressed to
  87.07%. Keep the current clearer tail spelling.
- Modeling the callee as `int` with no source return would only formalize an
  incidental register value. Cross-port `cRSubHover::JetInit()` and the exact
  void caller now remove that obsolete local return shim.
- 2026-06-18 BN/IDA sync: the durable BN prototype is now
  `void __thiscall initialize_jet_particles(SubHover*)`, and the
  BN/IDA exports no longer preserve the synthetic loop-counter return. The
  shared BN headers also promote `JetParticleSlot` to `Sprite* sprite`,
  `wobble_x`, `wobble_y`, and `wobble_alpha`, matching this exact initializer
  and the hover updater.

Android independently exports `cRSubHover::JetInit()` and initializes the same
30 inline sprite records. Focused Windows remains exact at 73/73 instructions.
