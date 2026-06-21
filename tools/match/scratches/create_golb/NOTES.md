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

- Current matcher result: 34.79% (`tools/match/match.sh
  tools/match/scratches/create_golb --full`).
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
- 2026-06-17 VapourTrail consolidation: the kind-1 vapour path now uses the
  shared `vapour_trail.h` method surface. `initialize_vapour` and
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
  `VapourTrail::add_vapour_point` member call improves focused Wibo to
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
