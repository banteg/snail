# play_sound_effect_at_position @ 0x44dce0

First-pass scratch for the positional sound-effect wrapper.

Recovered semantics:

- builds a camera-relative `Vector3` from the supplied world position and the
  active listener at `GameRoot::players[0].camera.transform.position`
  (`Game +0x22c`);
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
- 2026-06-21 distance-slot barrier: forcing the sentinel through a narrow
  volatile write to the `distance` local recovers the native stack slot and
  raises focused Wibo to 89.23%, with 64/66 candidate/target instructions and
  ten clean masked operands. VC6 still schedules the sentinel store one
  instruction before the native `position` argument load, and it keeps the
  magnitude result in the temporary slot rather than native's min-distance
  slot. Naming `position` as a local before the store, making all later reads use
  that local, and using a volatile distance declaration all failed to recover
  the native prologue order; the declaration form also regressed saved-register
  ownership.
- 2026-06-21 distance-gate read pass: reading the min-distance slot through a
  narrow volatile `audible_distance` local before the radius gate preserves the
  native conditional `distance = magnitude` store and raises focused Wibo to
  98.48%, with 66/66 instructions and 11 clean masked operands. Volatile writes
  inside the min branch regress to the low 70% range; a plain pointer view is
  neutral at 89.23%. The only remaining diff is the known sentinel-store order
  before the first `position` argument load.

2026-07-10 exact listener-loop and ownership pass:

- Removing both volatile casts exposes the honest 83.72%, 63/66 baseline. A
  one-iteration listener loop is the real source shape that preserves the
  initialized minimum-distance slot across the magnitude call; VC6 folds the
  loop control away and emits the native stream exactly. Focused Wibo is now
  100.00%, 66/66 instructions, full prefix, and 11 clean masked operands.
- The loop shape explains the otherwise redundant `1.0e10f` sentinel and
  conditional minimum around a single Windows listener. No volatile, register
  hint, inline assembly, or other code-shape barrier remains.
- Root construction initializes two consecutive 0x1f8-byte `cRPlayer` records
  at `Game +0x124/+0x31c`. Each owns an inherited `RenderableBod`-based
  `cRCamera` at player `+0xa0`; startup lends those camera subobjects at
  `Game +0x1c4/+0x3bc` to viewport slots 1 and 4. Therefore the audio read at
  `Game +0x22c` is precisely player 0 camera `+0x68`, the inherited transform
  position, rather than a standalone root listener vector.
- iOS independently names this overload `cRSound::Play(int, tVector&)`, so the
  Windows surface now takes a typed `Vector3&`. The exact `shoot_subgoldy`
  caller remains 48/48 after passing its unstaggered origin by reference.
