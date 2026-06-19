# `update_subgame` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.19% | **67.53%** |
| Target instructions | 1033 | 1033 |
| Candidate instructions | 1 | 1046 |
| Common prefix | 0 / 1033 | **9 / 1033** |
| Masked operands | none | **108 clean, 0 unresolved, 2 mismatched** |

The final candidate is thirteen instructions longer than the target. Both switch jump-table operands are now content-audited and classified as real mismatches. There are no unresolved masked operands.

The first remaining mismatch is:

```text
target[9]    ja Ld68
candidate[9] ja Le80
```

The branch serves the same out-of-range/common-camera role; the label identity differs because the remaining body layout is not yet exact.

## Accepted source-shape changes

- Reconstructed states `0`, `1`, `2`, `3`, `4`, and `7`, including pause fallthrough, replay setup, build/destroy handoffs, and the shared camera tail.
- Added the selected-level overlay, timer, tutorial, voice, resume, pause, and click-start gates.
- Typed the `0xf4` active-row and `0x54` track-cell layouts and implemented their two intrusive-list insertion paths.
- Added semantic parcel, fringe, pickup, speedup, jetpack, garbage, salt, slug, and ring lanes.
- Preserved a slot-base overlay so VC6 emits the native `+0x3bfac8` cell addressing form.
- Reloaded the fringe object after the skirt-color call, recovering the exact `0x3c` frame and native nonvolatile-register roles.
- Used nested tile-`29`/`30` control flow, signed `% 8`, matcher-confirmed RNG comparison ordering, and a shared tile-35 last-Z update.
- Duplicated the challenge-setup success path instead of sharing the later case-7 zero-level build label; this recovers the native ordering around `result == 1`.
- Modeled `format_time_trial_string` as a member-style call through a scratch-local receiver at `game + 0xff25e0`. The real callee is still the `ret 4` formatter, but the native callsites seed `ecx` before the call.

## Measured progression

| Trial | Match | Candidate instructions | Outcome |
|---|---:|---:|---|
| Starter `ret` | 0.19% | 1 | Baseline |
| Initial semantic front end | 28.67% | 411 | Kept as bootstrap |
| Reordered front state machine | 32.13% | 461 | Kept |
| Partial runtime-row body | 37.66% | 677 | Superseded |
| First full row body | 41.56% | — | Superseded |
| RNG operand-order cleanup | 47.90% | 1017 | Cleaned calls, but frame remained `0x40` |
| Recomputed row expression | 48.29% | 1017 | Better score; still spilled row state |
| Slot-base cell overlay | 49.25% | 1022 | Kept; corrected native address formation |
| Fringe reload/register recovery | 63.06% | 1057 | Kept; exact `0x3c` frame and 9-insn prefix |
| Nested tile `29`/`30` block | 65.00% | 1053 | Kept |
| Signed `% 8` selector | 65.36% | 1057 | Kept |
| Shared tile-35 last-Z write | 66.38% | 1043 | Kept |
| Duplicated challenge success path | 67.34% | 1043 | Kept |
| Member-style time-trial formatter call | **67.53%** | **1046** | Final retained result |

## Rejected trials

- Moving the bridge handoff to a distant shared label changed localized regions but did not improve the total score.
- Broadly merging every ring branch into one shared exit dropped the match to 54.33%; the source-level convergence was too aggressive and disrupted register/control-flow allocation.
- Sharing only the projected-ring assignment dropped the match to 65.41%.
- Sharing the ambient-ring assignment dropped the match to 64.24%.
- Replacing signed `% 8` with `& 7` removed the native signed modulo sequence.
- Declaration-order, narrower-scope, `register`, repeated-row-expression, and indexed fringe-loop experiments did not recover the frame/register allocation.
- Raw pause-fade assignment experiments did not alter the relevant scheduling.
- Moving the selected-level handoff to a tail `goto` label still emitted the same 67.53% layout, so it was reverted as neutral source churn.
- Materializing a `record = game + record_offset` local recovered the native add/reuse address sequence in the time-trial record branch, but regressed surrounding tail layout to 66.63%.
- No inline assembly, `volatile` clutter, fake globals, dummy externs, stack padding, or normalizer-specific tricks were retained.

## Next region to attack

First refine the remaining state-1 galaxy build/destroy exits. Then align the early state-2 bridge scheduling and the late HUD/camera return topology. After those front/tail regions are stable, revisit projected and ambient ring exits in smaller, matcher-guided steps rather than globally factoring them.
