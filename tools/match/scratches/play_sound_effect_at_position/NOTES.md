# play_sound_effect_at_position @ 0x44dce0

First-pass scratch for the positional sound-effect wrapper.

Recovered semantics:

- builds a camera-relative `Vector3` from the supplied world position and the
  active camera/listener position at `g_game_base + 0x22c`
  (`GameAudioListenerView::listener_position`);
- plays only within a 25.0 unit radius;
- computes gain as `1.0 - distance * 0.04`;
- computes pan from the source x position and clamps it to `[-100, 100]`; and
- dispatches through `play_sound_effect_backend(sound_id, gain, -1.0f, pan)`.

Focused Wibo result:

- 2026-06-18 first pass: 61.79%, 57/66 candidate/target instructions, masked
  operands 10 ok. The clean source shape proves the constants, radius gate,
  gain expression, pan clamp, and backend dispatch, but VC6 collapses the local
  vector staging into a 0x10-byte frame.
- 2026-06-20 local-vector staging pass: 83.72%, 63/66 candidate/target
  instructions, prefix 4/66, masked operands 10 ok. Keeping a second
  `Vector3 magnitude_delta = delta` recovers the native 0x1c-byte frame and the
  copy from x/y/z scalar slots into the vector passed to `vector_magnitude`.
  Remaining residual: native initializes the `distance` local before the delta
  math and keeps the min-distance result in that slot; the scratch stores the
  magnitude in a temporary and short-circuits the impossible far-audible case.

Rejected source-shape probes:

- A `double vector_magnitude()` declaration dirtied the constant audit and
  changed the early delta evaluation order.
- Inlined `Vector3(x, y, z)` constructor syntax evaluated constructor
  arguments in the wrong order and still kept the compact 0x10-byte frame.
- A separate `float delta_values[3]` array plus scalar temps also collapsed to
  the compact frame and regressed below the direct `Vector3` spelling.
- Explicit scalar `delta_x/delta_y/delta_z` locals copied into the `Vector3`
  regressed to 48.00% by changing the FPU evaluation order.
- A narrower scalar staging attempt that delayed `z`, plus conditional-assignment
  and ternary min-distance spellings, either regressed or compiled identically to
  the accepted two-vector shape.
- 2026-06-20 audio-family audit: assignment-in-condition
  `if ((magnitude = vector_magnitude()) < distance)` and comparing against the
  literal `1.0e10f` are codegen-neutral at 83.72%; moving the `distance`
  declaration after `g_game_base` is also neutral. Reversing the comparison to
  `distance > magnitude` regresses to 81.54% by forcing a spilled magnitude and
  reversed x87 compare. Keep the current two-vector source and treat the missing
  initial distance store plus magnitude-temp spill as x87/local-lifetime debt.
- 2026-06-21 helper surface audit: `shoot_subgoldy` now matches exactly only
  when this helper is called as `SoundEffectManager::play_sound_effect_at_position`.
  Promoting this scratch body to the same member signature is codegen-neutral at
  83.72%, confirming that the receiver is unused in the helper body while the
  call surface is still a real `SoundEffectManager` method.
