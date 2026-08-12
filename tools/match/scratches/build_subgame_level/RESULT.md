# `build_subgame_level` result

## Matcher command

```sh
tools/match/match.sh \
  tools/match/scratches/build_subgame_level \
  --regions --max-regions 20 --region-context 6
```

## Before and after

| Metric | Starter | Final scratch |
|---|---:|---:|
| Match | 0.36% | **85.95%** |
| Target instructions | 555 | 555 |
| Candidate instructions | 1 | **555** |
| Common prefix | 0 / 555 | **177 / 555** |
| Masked operands OK | 0 | **108** |
| Masked operands unresolved | 0 | **0** |
| Masked operand mismatches | 0 | **0** |

This is an 85.59 percentage-point improvement over the starter skeleton. The
first mismatch is:

```text
target[177]    jne L398
candidate[177] jne L396
```

The compiler-generated jump tables are content-audited and the current masked
operand pass is clean. The former unresolved completion-bonus `+0x4` operands
are resolved to the neighboring
`RuntimeConfig::default_challenge_speed_slider` field.

## Accepted source-shape changes

- Reconstructed the starfield/HUD gate and four-way music selection.
- Added all fixed reset and initialization calls through frontend level load.
- Recovered selected-record replay overrides and the normal mode-specific speed
  and difficulty paths.
- Preserved separate two-stage challenge scalar conversions to prevent MSVC
  constant folding.
- Added parcel-slot setup, optional widget hiding, and the exact track rebuild
  member call.
- Reconstructed landscape selection, activation, and starfield mirroring. The
  honest default arm retains the input in EDI; native's stack reload remains
  the first source-shape residual.
- Added the two early `ADDafter` row-controller insertions and improved their
  field initialization lifetimes. A short completion-`Banner` borrow now owns
  only the Player backlink and recovers the native post-mask store schedule.
- Added latch resets, mouse release, and Subgoldy initialization.
- Reconstructed the repeated active-list tail, voice-node attachment, mode-zero
  HUD update, pointer resets, and final subgame-rate calculation.
- Kept the masked-operand audit clean. The first state jump-table label drift
  is an ordinary control-flow difference, not a masked relocation mismatch.

## Rejected trials

- Algebraically combining challenge-scale expressions changed target constant
  sequencing.
- Preinitializing the landscape result lowered the score. The old incoming-index
  alias is now removed because the volatile stack reload is the stronger shape.
- Typed row overlays, chained zero stores, and completion-row permutations
  worsened scheduling or did not improve the score.
- Member/free inline helpers for repeated list insertion changed inlining,
  register allocation, and code size.
- Typed or persistent player-pointer variants did not reproduce the target's
  EDI player / EBP `0x200` register assignment.
- Direct per-switch-arm landscape activation reached 87.77% but grew to
  557/555 instructions and contradicts both mobile bodies' single post-switch
  activation, so it was rejected as a score-only tradeoff.
- Retesting player-node and membership-flag register hints on the improved row
  setup was still codegen-neutral or worse.

## Current residual

The random-landscape
default reload now has a complete ordinary-lifetime sweep plus an exact sibling
with the same irreducible VC6 topology. The completion pre-mask schedule is
unchanged by the dual-mobile cross-row Player lifetime, while all short
completion-position owners regress. The active-list tail's owner and inline
call spellings were already bounded. Do not retry these regions without new
original-source or compiler-provenance evidence; the prior sweep count does
not close the function.
