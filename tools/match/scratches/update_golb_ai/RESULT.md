# `update_golb_ai` result

## Matcher summary

| Metric | Before | After |
|---|---:|---:|
| Match | 49.85% | **57.21%** |
| Target instructions | 694 | 694 |
| Candidate instructions | 646 | **631** |
| Common prefix | 9 / 694 | 9 / 694 |
| Masked operands | 52 ok, 0 unresolved, 1 mismatch | **57 ok, 0 unresolved, 0 mismatch** |

The accepted pass improves the match by **7.36 percentage points**, removes
15 candidate instructions, and clears the packaged baseline's masked call
mismatch at target instruction 549.

## Accepted changes

- Declared `Player::add_subgoldy_score` as a member call, recovering the native
  player-owned `thiscall` shape.
- Declared a local `SlugHazardRuntime::hit_slug_hazard` member call for the two
  slug-contact modes.
- Reused the existing `new_output` pointer as the collision-position owner for
  garbage, slug, splash, and wall probes and for direct impact presentation.
- Reconstructed the collision scheduler as a sentinel garbage loop: a null
  exit enters the slug sweep, a garbage hit falls through to impact/splash and
  return, and the no-hit slug path branches to the wall probe.
- Kept `get_track_grid_cell_at_world_position` in its existing free-call shape;
  changing it to a member call did not pass the clean-mask criterion.

## Rejected trials

| Trial | Match | Candidate | Mask audit | Reason rejected |
|---|---:|---:|---:|---|
| Player + slug member ABI only | 54.40% | 637 | 4 mismatches | Better score, dirtier call alignment. |
| Track lookup member ABI only | 49.29% | 641 | 54 / 0 / 0 | Clean, but below baseline score. |
| `new_output` + slug + track ABI | 60.73% | 630 | 2 mismatches | Best headline score, not a clean audit. |
| `new_output` + player ABI | 60.39% | 634 | 2 mismatches | Dirty masked calls. |
| Explicit label variant | 60.73% | 630 | 2 mismatches | Same dirty result as the strongest trial. |
| Slug-kind `switch` variant | 60.12% | 630 | 2 mismatches | Worse and still dirty. |
| Accepted scheduler + track member ABI | 59.09% | 626 | 1 mismatch | Higher score, but reintroduced a mismatch. |
| Accepted scheduler, no player member ABI, track member ABI | 56.75% | 631 | 58 / 0 / 0 | Clean, but below the accepted score. |

Masked-audit triples are `ok / unresolved / mismatch` where written
numerically.

## Next region to attack

Homing blend target instructions `[158:211]`, approximately native
`0x414a45`–`0x414aa3`: recover the y/z retained-velocity owner and final
rescale-store scheduling without forcing the velocity pointer into the wrong
register. After that, revisit path-output copy staging around target
instructions `[28:50]`.

## Final audit

- Fixed toolchain: `msvc6.5 /O2 /G5 /W3`.
- No inline assembly, naked functions, volatile padding, fake globals,
  synthetic constants, dummy externs, or stack-padding tricks.
- No shared headers or unrelated scratches changed.
- Final matcher output: `57.21%`, target `694`, candidate `631`, prefix `9`,
  masks `57 ok, 0 unresolved, 0 mismatch`.
