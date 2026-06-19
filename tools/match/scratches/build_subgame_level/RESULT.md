# `build_subgame_level` result

## Matcher command

```sh
tools/match/match-py313.sh \
  tools/match/scratches/build_subgame_level \
  --regions --max-regions 20 --region-context 6
```

## Before and after

| Metric | Starter | Final scratch |
|---|---:|---:|
| Match | 0.36% | **79.82%** |
| Target instructions | 555 | 555 |
| Candidate instructions | 1 | **555** |
| Common prefix | 0 / 555 | **177 / 555** |
| Masked operands OK | 0 | **100** |
| Masked operands unresolved | 0 | **2** |
| Masked operand mismatches | 0 | **0** |

This is a 79.46 percentage-point improvement over the starter skeleton. The
first mismatch is:

```text
target[177]    jne L398
candidate[177] jne L396
```

The two unresolved masked operands are the compiler-generated jump tables at
target instructions 23 and 185. Their candidate operands are local switch-table
symbols; no masked operand is classified as a mismatch.

## Accepted source-shape changes

- Reconstructed the starfield/HUD gate and four-way music selection.
- Added all fixed reset and initialization calls through frontend level load.
- Recovered selected-record replay overrides and the normal mode-specific speed
  and difficulty paths.
- Preserved separate two-stage challenge scalar conversions to prevent MSVC
  constant folding.
- Added parcel-slot setup, optional widget hiding, and the exact track rebuild
  member call.
- Reconstructed landscape selection, activation, and starfield mirroring.
- Added the two early `ADDafter` row-controller insertions and their field
  initialization.
- Added latch resets, mouse release, and Subgoldy initialization.
- Reconstructed the repeated active-list tail, voice-node attachment, mode-zero
  HUD update, pointer resets, and final subgame-rate calculation.
- Kept the candidate at exactly the target's 555 instructions with a clean
  masked-operand mismatch audit.

## Rejected trials

- Algebraically combining challenge-scale expressions changed target constant
  sequencing.
- Preinitializing the landscape result or removing its incoming-index alias
  lowered the score or changed instruction count.
- Typed row overlays, chained zero stores, and completion-row permutations
  worsened scheduling or did not improve the score.
- Member/free inline helpers for repeated list insertion changed inlining,
  register allocation, and code size.
- Typed or persistent player-pointer variants did not reproduce the target's
  EDI player / EBP `0x200` register assignment.
- A direct `flags |= 0x80` visible-body update reduced the candidate to 552
  instructions and scored lower.

## Next region to attack

First, recover the landscape switch default as a stack reload of `level_index`;
that should remove the two-byte label displacement beginning at instruction
177. Then focus on the active-list tail beginning near target instruction 297,
where preserving the player pointer in EDI and carrying the `0x200` membership
flag in EBP should unlock the repeated insertion regions.
