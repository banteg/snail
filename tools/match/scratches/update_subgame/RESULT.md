# `update_subgame` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.19% | **78.22%** |
| Target instructions | 1033 | 1033 |
| Candidate instructions | 1 | 1033 |
| Common prefix | 0 / 1033 | **9 / 1033** |
| Masked operands | none | **116 clean, 0 unresolved, 2 mismatched** |

The final candidate has the same 1033-instruction length as the target. Both switch jump-table operands are content-audited and classified as real mismatches. There are no unresolved masked operands or mismatched call/data references.

The first remaining mismatch is:

```text
target[9]    ja Ld68
candidate[9] ja Ld6d
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
- Recovered `game + 0x3bb764` as one complete embedded `Player` ending exactly
  at the first runtime cell, and routed movement/control gates plus spawn
  arguments through that owner without changing codegen or the operand audit.
- Inverted the selected-level bridge so its handoff is the cold tail after the
  gameplay/HUD body, then preserved the native per-arm application-state
  snapshot; the resulting tail instructions and all call/data operands agree.
- Inlined the contextual projected-cell address in its three ring arms,
  removing an invented long-lived pointer and recovering the native repeated
  address formation and shared last-Z store without growing the frame.
- Materialized the time-trial record owner after the projected-cell lifetime
  correction; it now recovers the native base add and in-place timer-address
  reuse without disturbing the `0x3c` frame.
- Kept authored tile-33 garbage spawning separate from the gated procedural
  tiles, recovering the native argument-setup block and shared spawn tail.

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
| Member-style time-trial formatter call | 67.53% | 1046 | Kept |
| Cold selected-level bridge tail | 68.94% | 1047 | Kept; removed the 23-instruction early-body displacement |
| Per-arm application-state snapshot | 69.45% | 1049 | Kept; 111 clean operands |
| Inline projected-cell addresses | 70.97% | 1027 | Kept; 115 clean operands |
| Time-trial record-base owner retest | 71.32% | 1028 | Kept; 116 clean operands |
| Split authored/procedural garbage arms | **78.22%** | **1033** | Final retained result; exact target instruction count |

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
- Keeping a named embedded-`Player*` across the pause/fade bridge scored
  70.53%, but displaced native register roles and introduced a false
  speedup-to-health call pairing in the masked audit, so it was rejected.
- Retesting the time-trial record local on the cold-tail layout, before the
  projected-cell lifetime correction, regressed from 68.94% to 67.95%; sharing
  ambient ring speed through a local regressed to 61.11% by growing the frame
  to `0x40`. The record owner was later accepted after the allocation changed.
- No inline assembly, `volatile` clutter, fake globals, dummy externs, stack padding, or normalizer-specific tricks were retained.

## Next region to attack

Refine the remaining state-1 galaxy build/destroy scheduling, then revisit only the residual authored/ambient ring and HUD/handoff register schedules with source-backed shapes that preserve the `0x3c` frame.
