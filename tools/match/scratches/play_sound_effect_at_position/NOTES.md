# play_sound_effect_at_position @ 0x44dce0

First-pass scratch for the positional sound-effect wrapper.

Recovered semantics:

- builds a camera-relative `Vector3` from the supplied world position and the
  active camera position at `g_game_base + 0x22c`;
- plays only within a 25.0 unit radius;
- computes gain as `1.0 - distance * 0.04`;
- computes pan from the source x position and clamps it to `[-100, 100]`; and
- dispatches through `play_sound_effect_backend(sound_id, gain, -1.0f, pan)`.

Focused Wibo result:

- 2026-06-18 first pass: 61.79%, 57/66 candidate/target instructions, masked
  operands 10 ok. The clean source shape proves the constants, radius gate,
  gain expression, pan clamp, and backend dispatch, but VC6 collapses the local
  vector staging into a 0x10-byte frame. Native uses a 0x1c-byte frame with
  separate x/y/z scalar temps copied into a second 3-float vector before the
  `vector_magnitude` thiscall.

Rejected source-shape probes:

- A `double vector_magnitude()` declaration dirtied the constant audit and
  changed the early delta evaluation order.
- Inlined `Vector3(x, y, z)` constructor syntax evaluated constructor
  arguments in the wrong order and still kept the compact 0x10-byte frame.
- A separate `float delta_values[3]` array plus scalar temps also collapsed to
  the compact frame and regressed below the direct `Vector3` spelling.
