# create_golb

create_golb @ 0x415280 initializes one live Golb projectile slot from Goldy's
movement-flag family and emitter slot.

Recovered semantics covered by this scratch:

- clears the one-tick skip and slug-bounce bytes, then links the slot into the
  shared active body list unless it is already linked;
- classifies `player+0x338` movement flags into Golb kind `0`, `1`, or `2`;
- initializes the live matrix, state, owner pointer, and spawn position from
  `player+0x68..0x70` plus half extents at `player+0x58..0x60`;
- handles all movement-flag spawn-anchor families used by
  `update_movement_flag_emitters`: side offsets at `+0x4134/+0x414c/+0x4164`,
  attachment lanes at `+0x417c/+0x4188`, and the rocket lane at `+0x41ac`;
- for the `flags & 0x18` attachment family, repurposes the incoming selector as
  the optional vapour z-floor pointer at `player+0x4184` when the live-matrix
  forward-z lane at `player+0x60` is positive, otherwise passing null;
- seeds velocity from `player+0x418`, including the side-biased `+/-0.1`,
  `+/-0.5` x offsets, kind `1` velocity doubling, and kind `2` `0.8` scale;
- copies velocity to direction, sets per-kind lifetime step from game rate,
  and routes kind `0` through sprite allocation, kind `1` through vapour setup,
  and kind `2` through the exact `search_path_for_golb` helper;
- seeds the embedded follow state from `player+0x384` when the active player
  follow lane is available, otherwise clears it and installs the `-1.0f`
  path-entry z latch;
- stores the velocity magnitude into `path_factor`, copies the starting
  position to the previous-output vector, and dispatches through the slot
  vtable just like the native tail.

Residuals:

- Current matcher result: 36.08% (`tools/match/match.sh
  tools/match/scratches/create_golb --full`).
- The function is pinned: all native semantic lanes are represented, and the
  remaining source-shape leads have either been tested below or require new
  source/provenance evidence.
- Remaining diff is dominated by source-shape, especially the branchy
  movement-flag selector. Native keeps a compact fallthrough tree with several
  shared velocity-staging labels; the scratch uses clearer C++ branches.
- Native stages several vector copies through stack locals and callee-saved
  registers. The scratch writes most `Vec3` fields directly, so register choice
  and stack frame use differ even where the same fields are covered.
- The sprite path's position copy now uses whole-`Vec3` assignment, improving
  local pointer-copy shape. The same source shape was tested and rejected for
  the velocity-to-direction copy (27.21% -> 21.10%) and previous-output copy
  (27.21% -> 26.99%) in isolated trials. After the allocation-shape pass, the
  direction whole-copy was retested and rejected again because it regressed to
  15.92%, while the previous-output whole-copy improved the scratch from
  28.38% to 28.54%, 448/582 instructions.
- 2026-06-13 source-shaping follow-up: narrowing the `position`/`velocity`
  pointer lifetimes until after the list/kind setup improves the scratch from
  27.93% to 28.16%, 448/582 instructions. Splitting the `player+0x338` read
  into a kind-classification `kind_flags` read and a later movement-tree
  `movement_flags` read matches the native reload better and improves the
  scratch to 28.38%, 447/582 instructions. Re-testing the previous-output
  whole-copy on top of that accepted source shape improves the scratch to
  28.54%, 448/582 instructions.
- 2026-06-13 source-shaping follow-up 2: the `(movement_flags & 5)` selector
  now uses the native direct compare order with a shared movement-source copy
  label visible in BN's disassembly. A cleaner `if/else if` spelling improved
  the scratch to 28.57%, but still emitted a null-source guard; the shared-label
  spelling removes that guard and improves the scratch to 28.63%, 445/582
  instructions.
- 2026-06-15 type cleanup: `SpriteManager` and `Color4f` now come from the
  shared sprite header, including the float-shaped `store_color4f` callsite
  declaration. This is score-neutral at 28.63% and removes the final
  scratch-local `SpriteManager` copy.
- Rejected source-shape trials from the same pass: an explicit
  `player_position` source pointer for the initial spawn-position copy emitted
  the same score on its own; a whole-`Vec3` initial copy regressed to 28.10%;
  staging the half-extents as named locals regressed to 28.32%.
- 2026-06-13 rejection pass 2: staging only the y/z spawn half-extents as
  named locals regressed the current scratch from 28.63% to 28.57%, so keep
  the direct field adds. Repeatedly reloading the kind-0 sprite from the slot
  word instead of keeping the typed sprite pointer regressed to 20.96%.
  Rewriting the post-direction kind dispatch as a decrementing labeled tree
  regressed to 22.37%. A top-level `zero_byte` local for the initial byte
  clears emitted the same 28.63% code and was reverted as neutral churn.
- 2026-06-16 Sprite audit: the kind-0 sprite path now uses the shared `Sprite`
  fields for progress, gravity, color, `size_start`/`size_end`, position, and
  facing rotation. This keeps the local `Sprite*` shape called out above and
  improves the scratch from 28.63% to 30.93%, 446/582 instructions, with the
  same single masked-operand mismatch.
- 2026-06-17 Vapour consolidation: the kind-1 vapour path now uses the
  shared `vapour.h` method surface. `initialize_vapour` and
  `reset_vapour` pin flags `+0x04`, owner `+0x24`, point count/capacity,
  half-width bits at `+0x88`, optional z-floor/clamp pointer slot at `+0x8c`,
  and points `+0x90`; `create_golb` remains unchanged at 30.96%, 445/582
  instructions.
- The kind-specific setup lanes are complete, but vapour/list insertion, sprite
  color copy, and some path-search/list handling still differ in local ordering.
  Do not add dummy temporaries solely to force those byte layouts without
  stronger source evidence.
- 2026-06-18 vector alias cleanup: the scratch-local `Vec3` view now aliases the
  shared `Vector3` type, including the existing `vector_magnitude` method
  surface. Focused Wibo remained `30.96%`, `445/582`, with `31 ok` masked
  operands and the known mismatch.
- 2026-06-19 movement-tree layout: inverting the top-level `(movement_flags & 5)`
  source branch keeps the non-`&5` movement families as the fallthrough path and
  moves the `&5` anchor-copy body out-of-line, matching the native tree shape
  better without changing spawn semantics. Focused Wibo improves to `31.71%`,
  `446/582`, and the masked operand audit is now clean at `33 ok`, `0 mismatch`.
- 2026-06-20 GolbShot type split: the scratch now consumes `include/golb.h` for
  the `GolbShot::create_golb(Player*, int, int)` declaration. The final slot-0
  callback is still spelled through a local `GolbShotPrimaryBodyView`, matching
  the renderable BOD vtable installed at offset zero by `initialize_golb_shot`.
  Focused Wibo stays `31.71%`, `446/582`, with `33 ok` masked operands.
- 2026-06-21 helper surface pass: replacing the stale free
  `add_vapour_point(vapour, matrix)` call with the recovered
  `Vapour::add_vapour_point` member call improves focused Wibo to
  `31.94%`, `445/582`, with `33 ok` masked operands. This matches the native
  kind-1 vapour call surface (`ecx = self + 0x80`, one matrix argument) and
  removes the extra caller stack cleanup from the old free-function spelling.
- 2026-06-21 kind-2 path-hit pass: the `self + 0x118` node is now exposed as a
  local word slice for its active-list flags/links, the stale local
  `GolbPathSampleBank` shim is replaced by the shared `GolbPathBank` member
  call, and the path-search hit copies the three coordinate words through a
  `Vec3` view rooted at `sample + 4`. Focused Wibo improves to `34.79%`,
  `447/582`, with `35 ok` masked operands. Rejected neighbors: using the real
  `GolbPathBank` call alone was score-neutral, using the coordinate `Vec3` copy
  without the node word slice regressed to `28.18%` with a mask mismatch, and
  applying the same word-slice treatment to the kind-1 vapour node either
  stayed lower or regressed combined variants.
- 2026-07-10 attachment z-floor and ownership pass: Windows instructions
  `0x415565..0x4155b9` and the independent iOS
  `cRSubGolb::Create(cRSubGoldy*, int, int)` implementation in `Golb.o` both
  show that the `flags & 0x18` lane overwrites the incoming selector with an
  optional `float*`; the iOS `cRVapour::ReSet(float*)` symbol
  (`__ZN8cRVapour5ReSetEPf`) independently pins the callee type. When the
  live-matrix forward-z lane at `player+0x60` is
  positive it points at `player+0x4184`, the z component of the first
  `player+0x417c` attachment anchor; otherwise it is null. This value is later
  passed to `Vapour::reset_vapour` as its z-floor/clamp pointer. The
  scratch no longer mistakes selector values `1` and `2` for raw pointers.
  Narrowing the owner lifetime, using the owned `GolbShot::velocity` fields,
  and preserving the typed player owner through sprite allocation improves the
  focused result to `36.15%`, `458/582`, with `35 ok` masked operands. The
  follow-state tail now copies the typed owner record, including the whole
  output-position vector and its z latch, matching the native ownership and
  aggregate-copy evidence; that clarification is retained at `36.08%`,
  `460/582`, despite the `0.07` point SequenceMatcher movement.
- The primary live-body insertion now uses the shared `BodNode` ownership
  already proven by exact initialization and teardown scratches. This and the
  promoted `float*` vapour z-floor type are codegen-neutral for `create_golb`;
  `reset_vapour` remains exact at `7/7` instructions.
- The remaining stable `GolbShot` owners are now used directly for kind/state,
  source matrix, position/direction/previous output, lifetime, game, sprite
  body, emitter identity, and path factor. `+0x274` is explicitly a union of
  the sprite-facing `object_ref` and the caller-facing integer emitter index.
  This promotion is also codegen-neutral at `36.08%`, so no byte-shaping was
  introduced to obtain it.
- Rejected 2026-07-10 neighbors: narrowing only the player pointer regressed to
  `30.37%`; staging every velocity assignment through `Vec3` temporaries
  regressed to `34.59%` with a masked-operand mismatch; doing so only in the
  attachment lane regressed to `29.44%` with a mismatch; moving the position
  declaration earlier was score-neutral but hoisted its address before the
  native lifetime begins.
- 2026-07-11 contact-target correction: exact search and register helpers prove
  that the kind-2 lookup reads the subgame's `EnemyManager`, not a
  Golb-specific sample bank. The hit is now a `ContactTargetEntry*`; its object
  pointer is retained at `GolbShot +0x198`, kind zero reserves that object with
  flag `0x1000`, and its position is copied into the homing target. This keeps
  the existing honest `36.08%`, `460/582`, with 35 clean masked operands.

## 2026-07-13 void AI-dispatch contract

- The sole Windows caller, `update_movement_flag_emitters`, discards EAX. The
  independent iOS `cRSubGolb::Create(cRSubGoldy*, int, int)` body also ends by
  invoking the actor's slot-zero AI callback and returns without establishing
  a result value.
- `GolbShot::create_golb` is therefore `void`. Its scratch-local
  return-valued virtual shell is replaced by the shared, cast-only
  `BodAiDispatch` ABI view; this does not add a second vptr to `GolbShot`.
- Focused Windows output is byte-shape neutral at 36.08%, 460/582
  instructions, prefix 1/582, with all 35 masked operands clean.
