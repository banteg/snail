# `handle_subgoldy_collisions` result

## Matcher summary

| Metric | Before | After |
|---|---:|---:|
| Match | 47.99% | **52.85%** |
| Target instructions | 673 | 673 |
| Candidate instructions | 648 | 659 |
| Exact common prefix | 0 / 673 | **8 / 673** |
| Stack frame | `0x5c` | **`0x74`** |
| Masked operands | 77 ok, 0 unresolved, 1 mismatch | **86 ok, 0 unresolved, 0 mismatch** |

The accepted slug-local rewrite improves the focused score by **4.86 percentage points**. It also removes the masked call alignment error that previously paired target `kill_slug_hazard` with candidate `begin_post_follow_carryover`.

## Accepted source-shape changes

- Made the first-hit path the fallthrough side of `!control_override_active`, leaving the repeat-hit path in the `else`; this matches the native physical block order while preserving behavior.
- Staged the initial slug-hit velocity through a semantic `Vec3` before assigning `Player::velocity`.
- Staged the three half-distance firework offsets through a semantic `Vec3` before assembling `burst_position`.
- Kept the typed `SaltHazardSlot` and `SlugHazardRuntime` access paths; the
  later ownership pass names their fixed pools on `SubgameRuntime` and closes
  the salt slot's `collision_armed` byte from its spawner and this consumer.

Together, the two semantic vectors recover the native `sub esp, 0x74` frame. Reversing the equivalent inner condition aligns the first-hit, repeat-hit, and kill blocks closely enough to clear the masked operand audit.

## Rejected and superseded trials

- Branch-order change alone: `51.63%`, target/candidate `673/648`, prefix `0`, masks `86/0/0`. Clean gain, but superseded by the accepted staged form.
- Typed staging without the branch-order change: `48.80%`, target/candidate `673/659`, prefix `8`, masks `77/0/1`. It recovered the frame but retained the slug call-alignment mismatch.
- Two-float burst aggregate in place of the `Vec3`: `45.40%`, target/candidate `673/653`, prefix `0`, masks `76/0/1`; the frame collapsed below `0x74`.
- Scalar delta/probe rewrite: `51.06%`, target/candidate `673/643`, prefix `0`, masks `86/0/0`; it shortened the frame and regressed the score.
- Declaration-order permutations and a `register` active-state local were codegen-neutral.
- A raw salt byte-stride variant reached `53.46%` (`673/655`, prefix `8`, masks `86/0/0`), and adding a separate pickup-Y conditional reached `53.93%` (`673/651`, prefix `8`, masks `86/0/0`). These were not carried because they broadened the patch into independent salt and pickup slices; this result intentionally keeps the accepted change confined to slug first-hit/repeat-hit shape.

## Next region to attack

Region 4 remains the largest debt: target `[176:644]` versus candidate `[174:630]`, `48.70%`, delta `-12`. The next focused probe should preserve typed pool access while recovering the early sweep stack/register shape: native delta slots at `esp+0x30..0x38`, salt probe at `esp+0x48..0x50`, and the long-lived active-state value in `ebp`. Avoid reintroducing a masked slug-call mismatch.

## Final audit

- Fixed toolchain: `msvc6.5 /O2 /G5 /W3`.
- Final matcher command: `tools/match/match.sh tools/match/scratches/handle_subgoldy_collisions --regions --max-regions 20 --region-context 6`.
- Final matcher output: `52.85%`, target `673`, candidate `659`, prefix `8`, masks `86/0/0`.
- No inline assembly, naked functions, volatile padding, fake globals/constants, dummy externs, stack padding, or normalizer-specific tricks.
