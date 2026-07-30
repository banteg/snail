# `remove_subgame_bods` result

## Matcher summary

| Metric | Before | After |
|---|---:|---:|
| Match | 59.98% | **71.77%** |
| Target instructions | 501 | 501 |
| Candidate instructions | 496 | **505** |
| Exact common prefix | 6 / 501 | **6 / 501** |
| Masked operands | 59 ok, 0 unresolved, 2 mismatch | **70 ok, 0 unresolved, 0 mismatch, 0 unaudited** |

The mobile-assisted lifecycle recovery and bounded row-loop pass improve the
focused score by **11.79 percentage points** while clearing all reference
debt.

## Accepted ownership and source-shape changes

- Recovered all conditional lifecycle scopes from the complete Android and
  iOS `cRSubGame::RemoveBods()` bodies. Health, speedup, JetPack, Player-bank,
  and ClickStart state changes now occur only inside their native linked-body
  guards; ring state resets remain unconditional after optional unlinking.
- Kept the fixed row, cell, pickup, hazard, ring, Player, and projectile banks
  under their complete `cRSubGame` owners while traversing intrusive
  `BodNode::list_next` lanes where required by Windows code generation.
- Routed every inline active-list removal through the shared
  `BodList::remove_bod` owner and retained the three native out-of-line
  `recycle_bod_to_free_list` calls.
- Recovered the scoped embedded `cRSubGoldy` owner for presentation-bank
  teardown, movement-mode reset, and the folded one-byte teardown hook.
- Retained a row-end pointer for each eight-cell lane. This is a normal
  pointer traversal over the contiguous `cRSubLoc[8]` row and improves the
  focused score from 70.58% to 71.77% without changing the 505-instruction
  candidate extent or introducing reference debt.

## Rejected probes

- Four index/count variants derived from the mobile loops were neutral or
  regressed. The pointer-end form was the sole winner in that sweep.
- A named `cRSubGame*` spanning the track-cache boundary and final Player tail
  was codegen-neutral. It did not recover the native post-row EBX receiver.
- Hoisting the lane counter to the enclosing block was neutral with the
  pointer-end baseline and reverted to the 70.58% countdown allocation when
  combined with the native countdown body.
- Nine declaration, initialization, literal-count, and `for`/`do` countdown
  spellings all collapsed to the same 70.58% output. None exchanged the
  candidate's EBX cell cursor and EDI lane control.

The experiment ledger contains 19 unique variants: one better, six neutral,
and twelve worse, with no repeats or metric-only tradeoffs. Three consecutive
non-improving sweeps mark this source region stalled.

## Remaining region

Native keeps the opening cell cursor in EDI and uses EBX for the inner
eight-cell countdown. The candidate keeps the cell cursor in EBX and its
row-end pointer in EDI. After the row/cache phase, native reloads `this` into
EBX and uses high-byte linked-flag tests; the candidate reloads `this` into ESI
and spends EBX on a reusable `0x200` mask. That allocation difference
cascades through the pickup, hazard, ring, and Player removal blocks and
accounts for the four-instruction candidate surplus.

Resume only with new source or ownership evidence for the opening row
lifetime. Register forcing, byte-lane casts, volatile padding, or dummy locals
would be fakematching.

## Final audit

- Fixed toolchain: `msvc6.5 /O2 /G5 /W3`.
- Final matcher result: `71.77%`, target `501`, candidate `505`, prefix
  `6/501`, masks `70/0/0/0`.
- No inline assembly, naked functions, volatile padding, fake
  globals/constants, dummy externs, stack padding, or normalizer-specific
  tricks.
