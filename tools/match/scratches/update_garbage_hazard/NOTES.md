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
- every live/default path refreshes `Sprite::facing_angle` (`+0x7c`) from
  player roll plus the slot offset, with the `player+0x384` addend path.

Residuals:

- Current matcher result: 80.00% (`tools/match/match.sh
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
- 2026-06-13 source-shaping follow-up: typed vector sprite copies, native-side
  branch spelling for collision/sign classification, a local staged burst
  velocity, and a local gravity step improve the scratch from 55.45% to
  66.96%. These are all source-plausible forms of the recovered behavior.
- 2026-06-13 source-shaping follow-up 2: state 3 now stages the velocity and
  body pointers while integrating the live position, uses a real `next_x`
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
- 2026-06-13 source-shaping follow-up 5: state 3 now computes
  `velocity.x + world_position.x` before declaring the movement/body pointer
  locals. This matches the native ordering where the x add happens before the
  `lea` setup for the vector pointers and improves the scratch from 75.56% to
  77.16%, 227/224 instructions. The remaining operand order is still reversed
  (`fld world; fadd velocity` instead of `fld velocity; fadd world`), but the
  broad block layout is closer.
- 2026-06-13 source-shaping follow-up 6: the state-3 teardown check now uses
  `player->interaction_max_z` directly in the short-circuit condition and
  declares the smoke-call `owner` local after the destroy checks. This delays
  the `player` load until after the y `< -10` test, matching the native
  short-circuit shape without duplicating the destroy epilogue, and improves
  the scratch from 77.16% to 77.61%, 227/224 instructions.
- A direct-memory side-bias rewrite was tested because native reloads
  `velocity.x` around the compare, but VC6 duplicated the state-2 left-side
  store and regressed the scratch to 72.09%; keep the current local
  `adjusted_x` form unless stronger source evidence appears.
- A direct state-1 vector struct copy was tested because native copies through
  source and destination pointers, but VC6 chose worse register ownership and
  regressed the scratch to 74.34%. A local `contact_radius` staging variable
  forced an x87 spill at the append call and regressed to 72.12%. A switch-value
  case-0 return was also tested and emitted identical code; leave it out of the
  source.
- 2026-06-13 follow-up rejection pass: commuting the state-2 x scale expression
  to `random_x * rate` emitted the same 75.56% code, so keep the existing
  spelling. Splitting the state-3 teardown into separate y and z checks delayed
  the player load but duplicated the destroy epilogue and regressed to 73.71%.
  An explicit state-1 source-position pointer alias was also score-neutral at
  75.56% and did not recover the native copy registers. Replacing the
  state-2 `Vector3 staged_velocity` temporary with three named scaled component
  locals regressed sharply to 66.52% and shrank the frame to `0x8`, so keep the
  struct staging.
- 2026-06-13 follow-up rejection pass 2: reordering the switch labels so case 1
  physically preceded case 0 regressed the matcher to 68.00% by pulling the
  final roll-update tail into the case-1 path. Spelling the accepted state-3
  x-add as two statements (`next_x = velocity.x; next_x += world_position.x`)
  returned to the old 75.56% pointer-first sequence. Commuting the accepted
  single expression to `world_position.x + velocity.x` emitted the same 77.16%
  code, so keep the clearer velocity-plus-position spelling.
- 2026-06-13 follow-up rejection pass 3: changing the state-2 `rate` local
  from `double` to `float` moved the frame to `0x18` but regressed the x87
  staging from 77.61% to 70.95%, so keep the double-rate spelling. Reordering
  the case-1 sprite-position declarations and removing the `Sprite* visual`
  owner both emitted the same 77.61% code and were reverted as neutral churn.
  Flipping the side-bias absolute-value branch spelling also emitted identical
  code, so the remaining `fcomp`/reload residual is not solved by simple source
  branch shape.
- 2026-06-13 tooling follow-up: `snail match dump` verifies the native jump
  table sends state 0 to the epilogue at offset `0x302`, relying on the switch
  value in `eax` as the zero return. Recasting the scratch as a `void AI()`
  source shape regressed to 73.42%, so keep the current pointer-return scratch
  and treat the separate candidate state-0 epilogue as layout residual.
- 2026-06-13 tooling recheck: declaring the real state-2 `sign` local before
  the random draws did not recover the native `0x1c` frame or the
  `sign`/random/velocity stack-slot split; VC6 optimized it back to the same
  77.61% code. The frame gap needs stronger source evidence than local
  declaration order.
- 2026-06-13 matcher padding rebaseline: terminal object-padding normalization
  removes untargeted bytes after final `ret` instructions, so the same source
  now reports 78.73%, 218/224 instructions. This is a measurement correction,
  not a source-shape change.
- 2026-06-14 target-extent rebaseline: the native function returns at
  `0x43f508`, but the next curated symbol is `0x43f520`, so the default target
  extent included non-function bytes after the final `ret`. `scratch.conf` now
  caps the function at `0x43f509`, improving the honest measurement to 80.00%,
  218/217 instructions without changing source behavior.
- 2026-06-14 pin recheck: the localized diff still isolates the same residual
  classes after the extent fix: native uses a `0x1c` frame versus the
  candidate `0x14` frame, sends state 0 through the shared jump-table epilogue,
  and keeps different register/x87 ownership for the state-1 vector copy,
  state-2 random velocity staging, side-bias compare, and state-3 x add. The
  obvious source spellings for those areas are already rejected above, so treat
  this scratch as pinned unless new original-source or callsite evidence
  explains the frame/layout gap.
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
  register selection. Do not force these with dummy locals, raw offset macros,
  volatile, or opaque casts without stronger original-source evidence.
- 2026-06-16 Player consolidation: `heading_roll`, `nuke_effect_progress`, and
  `interaction_max_z` now come from shared `player.h`. The final `+0x384` /
  `+0x3a0` roll-add path is the same embedded follow-state active/orientation
  lane used by camera and attachment carryover, so it is intentionally spelled
  `follow_active` / `follow_orientation_b`, not garbage-specific field names.
  The focused score and masked audit remain 80.00%, `19 ok, 1 mismatch`.
- 2026-06-16 contact-target consolidation: this scratch now uses the shared
  `ContactTargetRegistry` from `contact_target.h`. `GarbageHazardSlot` carries
  the zero-offset `ContactTargetObject` prefix, with `list_flags +0x04`
  including the `0x1000` suppress bit consumed by
  `append_subgame_contact_target`. Focused result remains 80.00%, 218/217
  instructions, `19 ok, 1 mismatch`.
- 2026-06-16 BOD/contact inheritance consolidation: `GarbageHazardSlot` now
  inherits `BodNode`, and `BodNode` inherits `ContactTargetObject`. This keeps
  the contact append call source-typed through the shared prefix while making
  the destroy/list semantics agree with the other BOD-list users. Focused
  result remains 80.00%, 218/217 instructions, `19 ok, 1 mismatch`.
- 2026-06-16 renderable-prefix consolidation: `initialize_garbage_hazard` now
  uses the shared `GarbageHazardSlot` header and remains exact. The shared slot
  view records the renderable transform rows at `+0x38..+0x77`; the
  `world_position` consumed here is the transform position row at `+0x68`.
  Focused result remains 80.00%, 218/217 instructions, `19 ok, 1 mismatch`.
- 2026-06-20 larger garbage-family retry: focused Wibo still reports 80.00%,
  218/217 instructions, with 19 clean masked operands and the known jump-table
  relocation mismatch. Declaring the state-3 velocity pointer before the x
  integration and computing `movement->x + world_position.x` is codegen-neutral:
  VC6 still emits `fld world_position.x; fadd velocity.x`, not the native
  `fld velocity.x; fadd world_position.x`. Keep the current `next_x` spelling
  because the pointer-lifetime variant does not explain the operand-order or
  frame-size residual.

## 2026-06-20 oracle-frontier source-shape improvement

A focused source-shape pass improves the scratch from 80.00% to 93.55%. The
candidate now has the exact 217-instruction count, a 13/217 common prefix, and
22 clean masked operands with no unresolved operands or mismatches. The native
`0x1c` frame and shared state-0 jump-table epilogue are both recovered.

Accepted forms:

- the return accumulator also carries the switch value, allowing case 0 to
  branch to the final epilogue instead of emitting a duplicate early return;
- state 1 uses a typed `Vector3` copy through source/destination pointers;
- state 2 stages random x/y in a `Vector3`, retains random z as `double`, reads
  rate as `float`, and widens rate after the x calculation for the y/z x87
  schedule;
- collision side 1 uses a double-valued absolute-value ternary, while side 2
  keeps the direct memory ternary;
- state 3 declares position before movement and computes x through both
  pointers;
- functional casts on the staged y/z stores preserve the best code while
  removing C4244 warnings.

The remaining four regions are allocation/scheduling residuals: rotated
register ownership in the state-1 vector copy, EAX-versus-EDX ownership for the
contact radius push, one missing z-scale `fxch`, and the balancing extra store
in the positive side-bias epilogue. Raw pointer-walk vector copies
(80.18%-85.71%), separate switch-state temporaries (92.17%), named/precomputed
z products (84.60%-90.78%), and common-store side-bias rewrites (at most
87.04%) were all rejected. No shared header changes were required.

## 2026-06-20 larger frontier retry

Focused Wibo reverified the current frontier at 93.55%, 217/217 instructions,
13/217 prefix, and 22 clean masked operands. Retesting the state-1 copy with
destination-first pointer declarations and C++ references is codegen-neutral;
explicit x/y/z field copies regress to 85.91% and lose the clean jump-table
relocation. A `contact_radius` local still forces an x87 spill and regresses to
86.44%. Commuting the z-scale multiply is neutral and leaves the missing
`fxch`, while spelling the side-bias dispatch as a `switch` regresses to 87.10%
and reintroduces the jump-table relocation mismatch.

The related smoke emitters and the nearby near-proof scratches were also
rechecked for reusable source-shape leads; their remaining gaps are the same
documented scheduling artifacts, not new layout evidence. Keep this scratch
pinned at 93.55% unless a real original-source lifetime lead explains one of
the four local residuals above.

## 2026-06-21 garbage owner cleanup

`GarbageHazardSlot::game` is now shared as `SubgameRuntime*`, and the shared
runtime exposes the contact target registry at `+0x1270fd4`. This removes the
scratch-local generic `Game` shell without changing the pinned source shape.
Focused Wibo remains at 93.55%, 217/217 instructions, 13/217 prefix, and
22 clean masked operands.
