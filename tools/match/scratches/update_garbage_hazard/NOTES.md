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

- Current matcher result: 75.56% (`tools/match/match.sh
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
- 2026-06-13 source-shaping follow-up: typed `Vec3` sprite copies, native-side
  branch spelling for collision/sign classification, a local staged burst
  velocity, and a local gravity step improve the scratch from 55.45% to
  66.96%. These are all source-plausible forms of the recovered behavior.
- 2026-06-13 source-shaping follow-up 2: state 3 now stages the velocity and
  body pointers before integrating the live position, uses a real `next_x`
  temporary for the x add, and keeps the native-like struct copy back to the
  sprite. State 1 uses explicit sprite-position field copies. This improves the
  scratch from 66.96% to 74.67% without changing recovered behavior.
- 2026-06-13 source-shaping follow-up 3: the post-bias signed x push is now
  staged as `sign * 0.2f`, then multiplied by the subgame rate, then added
  after clearing `unknown_a4`. This matches the native arithmetic/store order
  around `fild sign`, the two `fmul`s, the `unknown_a4 = 0` store, and the
  final `velocity.x` add. Current result: 75.56%, 226/224 instructions
  (`tools/match/match.sh tools/match/scratches/update_garbage_hazard --full`).
- 2026-06-13 source-shaping follow-up 4: the burst cadence setup now stages
  `rate * 0.0083333338f` in a source local, clears `smoke_timer`, then stores
  `burst_rate_step`. This keeps the focused matcher at 75.56%, 226/224
  instructions, but matches BN's native store order around the held x87 rate
  step instead of spelling the stores in source field order.
- A direct-memory side-bias rewrite was tested because native reloads
  `velocity.x` around the compare, but VC6 duplicated the state-2 left-side
  store and regressed the scratch to 72.09%; keep the current local
  `adjusted_x` form unless stronger source evidence appears.
- A direct state-1 `Vec3` struct copy was tested because native copies through
  source and destination pointers, but VC6 chose worse register ownership and
  regressed the scratch to 74.34%. A local `contact_radius` staging variable
  forced an x87 spill at the append call and regressed to 72.12%. A switch-value
  case-0 return and direct state-3 x-sum spelling were also tested and emitted
  identical code; leave them out of the source.
- 2026-06-13 follow-up rejection pass: commuting the state-2 x scale expression
  to `random_x * rate` emitted the same 75.56% code, so keep the existing
  spelling. Splitting the state-3 teardown into separate y and z checks delayed
  the player load but duplicated the destroy epilogue and regressed to 73.71%.
  An explicit state-1 source-position pointer alias was also score-neutral at
  75.56% and did not recover the native copy registers. Replacing the
  state-2 `Vec3 staged_velocity` temporary with three named scaled component
  locals regressed sharply to 66.52% and shrank the frame to `0x8`, so keep the
  struct staging.
- Remaining diff is dominated by VC6 source-shape/allocation issues, not
  uncovered behavior: native keeps a `0x1c` local frame while the candidate
  keeps a `0x14` frame, and the burst random/scaled velocity staging still uses
  different stack slots and x87 scheduling.
- The case-1 and case-3 position copies are semantically identical but still
  use different register/source ordering in parts of the sequence. Native
  copies through staged source and destination pointers; the scratch's typed
  copies let VC6 choose close but not identical registers in case 1.
- Collision-side x bias, gravity update, smoke timer, and final roll update are
  covered, but still differ in x87 scheduling, comparison temporary width, and
  register selection. Do not force these with dummy locals or opaque casts
  without stronger original-source evidence.
