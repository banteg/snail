# Paired Dip Identity ownership

Starting from `413d443ed`, Dip improves **98.77862595% → 99.54198473%**.
Its instruction count remains **655/655**, its prefix remains **22**, and all
**37 references** remain clean. The canonical source changes only the ownership
of the two curve `Identity` calls and names the helpers for their new roles.
No full-function exactness or new exact-function credit is claimed.

| Target | Before | After | Result |
| --- | ---: | ---: | --- |
| Dip | 98.77862595% | 99.54198473% | Paired receiver sequences recovered |
| LoopTheLoopW | 99.86577181% | unchanged | Rotation schedule and two SIB bytes remain |
| LoopOut | 100% normalized | unchanged | One encoded SIB byte remains |
| HillValley | 97.60479042% | unchanged | Endpoint spill and receiver ownership remain open |

## Source evidence

The primary curve operation now owns `Identity` followed by its position writes.
Secondary `Identity` belongs to the caller, followed by a helper that writes the
secondary position. Both operations still borrow the live sample-bank members;
the index, angle, radius, shared Z value and call order are preserved.

| Primary Identity | Secondary Identity | Match | Instructions |
| --- | --- | ---: | ---: |
| Caller | Helper (baseline) | 98.77862595% | 655 |
| Position helper | Helper | 95.33995416% | 654 |
| Caller | Caller | 95.34706331% | 656 |
| Position helper | Caller (retained) | 99.54198473% | 655 |

The individual moves regress. Their combination recovers both native receivers:
primary uses `mov ecx,[esi+0x58]; add ecx,edi`; secondary uses
`mov edx,[esi+0x5c]; mov ecx,edi; add ecx,edx`. Inlining secondary position is
code-equivalent to moving just its Identity. Inlining primary position alone
does not recover the primary receiver. The compact helper form is retained.
This is evidence for a coupled source boundary, not proof of the original
helper names or unique original source.

## Independent byte proof

The [checker](check_dip_identity_owners_20260921.py) decodes the captured bytes
with Capstone and verifies:

- Native and both candidates have a 2,390-byte compared body plus ten identical
  padding bytes; there are no unexplained target bytes.
- Candidate bytes outside `[486,575)` are unchanged.
- The complete 27-instruction region `[486,580)`—native
  `[0x41e626,0x41e684)`—is byte-equal after four audited relocations. Instruction
  offsets and sizes also agree throughout this region.
- Three relocation fields move from `498/524/530` to `496/522/528`; their keys,
  types, addends and other metadata are unchanged. The other 34 stay in place.
- All 37 reference operands retain matching kind, operand slot and semantic key.
  Encoded candidate addends and native numeric targets are independently
  checked. References with both native instruction index and byte offset rise
  **30 → 33**.
- All **26 local branches** retain the exact native instruction bytes and
  destinations. Corrupting a receiver byte, an unrelated byte, or a reference
  target is rejected.

The remaining normalized differences are the early endpoint spill, header count
store/conversion schedule, and the phase-zero register source. Separately,
**17 SIB bytes** still exchange scale-one base/index roles: nine in curve
metadata/position and eight in orientation/delta code. The checker identifies
these literal differences rather than granting encoded exactness. The mesh
improvement from the previous batch is preserved.

## Bounded follow-up controls

The [receipt](dip-identity-owners-20260921.json) preserves **83 observations,
74 distinct sources**, the original source for every target, source edits and
hashes, build-input hashes, measurements, raw proof, and forward/reverse probes.
Five source-construction errors are explicitly retained and excluded from native
conclusions: four controls wrongly treated local `loop_wiggle` as a member, and
one placed the phase declaration in the mesh helper. Corrected controls compile.

- **Dip:** count expressions, endpoint-Z lifetimes, a borrowed endpoint index,
  phase/index forms and inlining the mesh operation do not improve the retained
  pair. The early spill survives both endpoint-only and lead-plus-endpoint helpers.
- **LoopOut:** a shared physical departure cursor regresses; a real departure
  span and advancing logical departure index reproduce the same raw bytes,
  including the outstanding SIB byte at body offset 745.
- **LoopTheLoopW:** grouping positions, orientation, or the complete curve sample
  into an operation that borrows both banks is neutral. A path-owned operation
  regresses earlier in the curve. Passing roll by value or reference does not
  resolve the rotation schedule.
- **HillValley:** the paired receiver recipe does not transfer. Caller, helper,
  bank-borrowing and endpoint-length lifetime controls are neutral or worse.
  Its similar early spill remains a separate ownership question.

These finite controls narrow the next experiments; they establish no compiler
ceiling or exhausted search.

## Reproduce and validate

```sh
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run \
  tools/match/check_dip_identity_owners_20260921.py
UV_CACHE_DIR=/private/tmp/snail-mail-uv-cache uv run \
  tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/dip-identity-owners-20260921.json \
  --function initialize_dip_path_template_pair \
  --batch retained-cleanup --label paired-identity-owners --replay
```

All 83 source recipes reconstruct; the retained native compile replays. The
official forward probe reports no tradeoffs, and the reverse probe reproduces
the original code fingerprint. All 785 scratch checks, the exact-reference
audit, extern lint, and 1,140 tests pass. The experiment ledger has 2,622 records,
zero strict errors, and 14 runnable active specifications. The refreshed public
report changes only Dip's semantic row; normalized and encoded exact counts
are unchanged.
