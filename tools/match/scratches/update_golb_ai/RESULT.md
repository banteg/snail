# `update_golb_ai` follow-up result

## Matcher summary

| Metric | Before | After |
|---|---:|---:|
| Match | 57.21% | **69.45%** |
| Target instructions | 694 | 694 |
| Candidate instructions | 631 | **625** |
| Common prefix | 9 / 694 | 9 / 694 |
| Masked operands | 57 ok, 0 unresolved, 0 mismatch | **69 ok, 0 unresolved, 0 mismatch** |

The accepted pass improves the packaged baseline by **12.24 percentage
points**, removes 6 candidate instructions, and keeps the masked-operand audit
fully clean.

## Accepted changes

- Recovered the two track-cell lookups as `Game` member calls, matching their
  game-owned `thiscall` shape without changing a shared header.
- Recovered vapour emission as the existing
  `Vapour::add_vapour_point` member call.
- Kept homing y/z retained-velocity loads and final rescale stores on the
  already-live `movement` pointer while leaving the native-looking x accesses
  direct.
- Copied the post-homing position into `source_matrix.position` as one `Vec3`
  assignment rather than three scalar stores.
- Recovered the path-follow raw-position output case as an aggregate copy
  through named source/destination `Vec3*` pointers.
- Routed a non-laser garbage hit directly to a `garbage_hit` cleanup label.
  A null garbage-list exit now falls through to the slug sweep, whose no-hit
  path branches to `wall_probe`; this restores the native collision-block
  ordering without synthetic state or stack padding.

## Rejected trials

| Trial | Match | Candidate | Mask audit | Reason rejected |
|---|---:|---:|---:|---|
| Homing y/z owner recovery only | 57.81% | 631 | 57 / 0 / 0 | Clean gain, superseded by the combined pass. |
| Homing y/z plus aggregate position copy | 60.69% | 634 | 57 / 0 / 2 | Better score, but two masked mismatches. |
| Vapour member call plus homing | 60.02% | 629 | 59 / 0 / 1 | One masked mismatch. |
| Track member calls plus homing/aggregate copy | 59.56% | 629 | 57 / 0 / 0 | Clean gain, superseded by the combined pass. |
| Vapour + track members before collision relayout | 61.77% | 627 | 59 / 0 / 1 | One masked mismatch caused by downstream block ordering. |
| Post-loop collision `goto` variant | 69.19% | 627 | 69 / 0 / 0 | Clean, but lower score and two more instructions than accepted. |
| Late shared homing-return label | 44.93% | 637 | 57 / 0 / 4 | Large regression and four masked mismatches. |
| Path-copy staging through one y local | 56.34% | 630 | 56 / 0 / 1 | Regressed below baseline and dirtied the audit. |
| Raw-position scalar field stores | 59.89% | 625 | 66 / 0 / 2 | Regressed and dirtied switch/call alignment. |

Masked-audit triples are `ok / unresolved / mismatch`.

## Next region to attack

Target instructions `[31:48]`, the narrow path-follow raw-position output-copy
slice. The accepted build already aligns this region at 88.24% with equal
17-instruction spans; the remaining two changed instructions are a better
localized target than reopening the broad trail/collision blocks.

## Final audit

- Fixed toolchain: `msvc6.5 /O2 /G5 /W3`.
- No inline assembly, naked functions, volatile padding, fake globals,
  synthetic constants, dummy externs, or stack-frame padding.
- No shared headers or unrelated scratches changed.
- Final matcher output: `69.45%`, target `694`, candidate `625`, prefix `9`,
  masks `69 ok, 0 unresolved, 0 mismatch`.
