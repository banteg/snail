# update_garbage_hazard

update_garbage_hazard @ 0x43f200 = `cRSubGarbage::AI()`.

Recovered semantics covered by the initial scratch:

- state `1` copies the live body position to the sprite, destroys the slot
  when it falls behind `player+0x2980`, reacts to `player+0x374 > 0` by
  entering burst setup, records the collision side from world x, adds garbage
  score event `0`, and appends the contact target through exact-matched
  `append_subgame_contact_target`;
- state `2` seeds randomized burst velocity from
  `random_signed_float_below(0.1)`, `random_float_below(0.2)+0.1`, and
  `random_float_below(0.30000001)`, biases x by collision side, then arms
  smoke cadence fields;
- state `3` integrates the live body, copies it to the sprite, applies native
  y gravity `rate*rate*-0.0099999998`, tears down below y -10 or behind the
  player, and emits smoke through `spawn_garbage_smoke_particle` once
  `smoke_timer > 1`;
- every live/default path refreshes sprite `+0x7c` from player roll plus the
  slot offset, with the `player+0x384` addend path.

Residuals:

- Current matcher result: 55.45% (`tools/match/match.sh
  tools/match/scratches/update_garbage_hazard --full`).
- Helper conventions are source-evidenced: `destroy_garbage_hazard`,
  `add_subgoldy_score`, and `spawn_garbage_smoke_particle` are thiscall
  members; `append_subgame_contact_target` is the exact-matched registry
  helper.
- 2026-06-13 follow-up: the burst RNG calls carry the same ignored debug/tag
  argument pattern seen in garbage spawn. Raw image disassembly shows the first
  call pushes `0x4a4e6c`, which resolves to `"GDI"`, and the next two calls
  push null. The scratch now spells this as
  `random_signed_float_below(0.1f, "GDI")`,
  `random_float_below(0.2f, 0)`, and
  `random_float_below(0.30000001f, 0)`.
- Collision-side x classification and side-bias adjustment now use float-width
  locals, matching native 32-bit zero comparisons instead of forcing qword
  constants through `double`.
- Remaining diff is dominated by VC6 source-shape/allocation issues, not
  uncovered behavior: native keeps a `0x1c` local frame and stages the burst
  random/scaled velocity floats through locals before writing velocity fields,
  while the scratch keeps a smaller frame and writes several values directly.
- The case-1 and case-3 position copies are semantically identical but use a
  different register/source ordering. Native copies through staged source and
  destination pointers; the scratch's typed field copies let VC6 choose a
  shorter sequence.
- Collision-side x bias, gravity update, smoke timer, and final roll update are
  covered, but still differ in x87 scheduling, comparison temporary width, and
  register selection. Do not force these with dummy locals or opaque casts
  without stronger original-source evidence.
