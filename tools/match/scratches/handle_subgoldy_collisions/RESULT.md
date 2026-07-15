# `handle_subgoldy_collisions` result

## Matcher summary

| Metric | Before | After |
|---|---:|---:|
| Match | 53.93% | **54.23%** |
| Target instructions | 673 | 673 |
| Candidate instructions | 651 | **651** |
| Exact common prefix | 8 / 673 | **8 / 673** |
| Stack frame | `0x74` | **`0x74`** |
| Masked operands | 86 ok, 0 unresolved, 0 mismatch | **88 ok, 0 unresolved, 0 mismatch** |

The latest source-type pass improves the focused score by **0.30 percentage
points** without changing instruction count. It preserves the frame and common
prefix while adding two clean masked operands to the earlier collision pass.

## Accepted source-shape changes

- Made the first-hit path the fallthrough side of `!control_override_active`, leaving the repeat-hit path in the `else`; this matches the native physical block order while preserving behavior.
- Assigned the initial slug-hit velocity directly from the recovered
  `Vector3(0, 0.2, -0.2) * subgame_rate` expression. VC6 materializes the
  native-size aggregate temporary without a scratch-only named owner.
- Staged the three half-distance firework offsets through a semantic `Vec3` before assembling `burst_position`.
- Kept the typed `SlugHazardRuntime` access path. The later ownership pass names
  both fixed pools on `SubgameRuntime` and closes the salt slot's
  `collision_armed` byte from its spawner and this consumer.
- Recovered the native salt sweep's game-base byte cursor while retaining the
  exact canonical owner in `SubgameRuntime::salt_hazards` and the shared
  `SaltManager` / `Salt` definitions. This is an honest source-shape choice,
  not an unknown-layout workaround.
- Assigned `pickup_y` in both arms of the health/speedup sign conditional before
  the `0.4f` gate. This emits the native x87 absolute-Y shape and removes four
  instructions from each repeated pickup block.
- Replaced the parcel HUD's raw widget-buffer addition with
  `FrontendWidget::text_buffer`; Binary Ninja and the shared layout agree on
  `+0x2cc`, and the change is codegen-neutral.
- Recovered both sound-variant RNG multiplications as `float`. Their target
  instructions are `fmul dword`, and the independently exact slug AI uses the
  same integer-to-float conversion before scaling.

Together, the two semantic vectors recover the native `sub esp, 0x74` frame. Reversing the equivalent inner condition aligns the first-hit, repeat-hit, and kill blocks closely enough to clear the masked operand audit.

## Rejected and superseded trials

- Branch-order change alone: `51.63%`, target/candidate `673/648`, prefix `0`, masks `86/0/0`. Clean gain, but superseded by the accepted staged form.
- Typed staging without the branch-order change: `48.80%`, target/candidate `673/659`, prefix `8`, masks `77/0/1`. It recovered the frame but retained the slug call-alignment mismatch.
- Two-float burst aggregate in place of the `Vec3`: `45.40%`, target/candidate `673/653`, prefix `0`, masks `76/0/1`; the frame collapsed below `0x74`.
- Scalar delta/probe rewrite: `51.06%`, target/candidate `673/643`, prefix `0`, masks `86/0/0`; it shortened the frame and regressed the score.
- Declaration-order permutations and a `register` active-state local were codegen-neutral.
- A raw salt byte-stride variant reached `53.46%` (`673/655`, prefix `8`, masks
  `86/0/0`), and adding a separate pickup-Y conditional reached `53.93%`
  (`673/651`, prefix `8`, masks `86/0/0`). They were initially held back to
  keep the slug-local commit scoped and are now the accepted collision slice.
- Mutating `probe_b.y` in place for the absolute-Y test regressed to `52.26%`
  and reduced the clean masked operands to `82 ok` with two constant
  mismatches; rejected.
- Rewriting the slug sweep around a game-base raw byte cursor regressed from
  `54.23%` to `52.57%` and reduced the clean operand count from `88` to `87`;
  the canonical typed `Slug*` walk remains.

## Next region to attack

Region 4 remains the largest debt: target `[176:644]` versus candidate
`[173:622]`, `49.51%`, delta `-19`. The next focused probe should recover the
early sweep stack/register schedule and native long-lived active-state value in
`ebp` without undoing the now-proven pool ownership or reintroducing a masked
slug-call mismatch.

## Final audit

- Fixed toolchain: `msvc6.5 /O2 /G5 /W3`.
- Final matcher command: `tools/match/match.sh tools/match/scratches/handle_subgoldy_collisions --regions --max-regions 20 --region-context 6`.
- Final matcher output: `54.23%`, target `673`, candidate `651`, prefix `8`, masks `88/0/0`.
- No inline assembly, naked functions, volatile padding, fake globals/constants, dummy externs, stack padding, or normalizer-specific tricks.
