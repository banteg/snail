# cRPathFollowGolb::Traverse @ 0x4217b0

Current recovery: semantic-complete; remaining differences require analysis.

Android and iOS `Path.o` independently export the exact authored method
`cRPathFollowGolb::Traverse(float, tVector&, tVector*)`, with one body on each
platform. Live Windows analysis confirms the same three-argument thiscall,
integer mode return, sole `cRSubGolb::AI` caller, and complete return-mode
switch.

The matcher now uses the authored method and reference parameter directly.
VC6 emits `?Traverse@cRPathFollowGolb@@QAEHMAAUtVector@@PAU2@@Z`; selecting
that exact COFF symbol is byte-neutral at 85.82% (421/425 instructions), with
a 32-instruction exact prefix and all seven relocations resolved cleanly.

Recovered behavior covers borrowed path traversal, both transform branches,
Golb flight-transform publication, lateral exit, and terminal launch. The historical four-instruction deficit was unresolved source recovery; the
2026-09-05 changes below recover it without changing compiler settings.

## 2026-09-05 traversal vector and nonlinear-output ownership

Current native-backed result: **99.29%, 425/425 instructions, prefix 96**, with
all seven reference operands clean. The live starting point was 86.52%,
421/425; the older 85.82% note above belongs to an earlier dependency state.

The terminal supertramp path constructs `(anchor + terminal position) +
forward offset`. Keeping those vector operations separate from the ordinary
path's `Vec3 base` recovers the four missing instructions. These are coupled
source changes: the terminal expression alone regressed before the ordinary
base owner was recovered. Caching the sample count, and deriving its final
index at the comparisons, then recovers the native EAX/EDI relationship.

The nonlinear transform has a separate output scalar. The previous source
passed the address of the interpolated input scalar back into the helper.
Giving that output a distinct local permits the compiler to share their stack
storage when appropriate and recovers the native layout of all surrounding
scalar and vector temporaries. The helper output is unused by this caller;
its input remains the same interpolated value. This is a source-lifetime
recovery, not an assertion that two separate stack slots exist in the binary.

The retained terminal offset uses component multiplication, while the ordinary
right offset uses the shared vector multiplication operator. A recorded
35-combination probe establishes their interaction with the recovered output
owner. The remaining differences are one x87 duplicate scheduled across an
integer LEA in the terminal path and two equivalent x87 instructions for the
ordinary right-offset Y product. Matrix/base declaration scopes, copy and
assignment definitions, const value returns, expression boundaries, and
component operand order did not close those differences. No diagnostic header
shadow, wider scalar, or operator override is retained. The residual remains
open; the former compiler attribution did not explain the recovered changes.

Three additional shared multiplication-result diagnostics test direct constructor return, named constructor return, and copy-then-scale. The constructor forms are byte-neutral at 99.29%; copy-then-scale regresses. The shared operator definition remains unchanged.

## 2026-09-05 ordinary basis snapshots

Six complete basis snapshots compare vector, const-vector, and three-scalar
owners before or after local displacement calculation. All regress from
99.29% to 98.82%, with the same prefix and seven clean references. No snapshot
is retained. The existing shared vector multiplication remains canonical;
this result does not settle the Y-product x87 operand schedule.

## 2026-09-05 continued 590-match investigation

Eight carry/displacement precision combinations do not improve 99.29%. Uncast double carry moves the first address calculation toward native but introduces other floating-point differences (98.59%); the remaining forms are neutral. All seven references remain clean. No source change is retained.

These receipts bound the tested forms and do not establish source exhaustion.


## 2026-09-05 diagnostic-export batch

Terminal-borrow probes compare the one-past sample owner with a last-sample pointer/reference, a transform pointer/reference, and borrowed forward/position vectors. Sample/transform borrows compile identically at 94.59% and lose the prefix at instruction 51; the forward borrow gives 98.82%, prefix 96. All seven references remain clean.

Two initial position-borrow probes accidentally collided with the existing `terminal_position` result variable. Record 29 has a digest-bound invalid-plan audit; both are replayed with `borrowed_terminal_position` in the corrected recipe. They compile identically at 98.82%, prefix 96, seven clean references. These compile errors are not negative source evidence. The baseline remains 99.29%, with the terminal LEA/x87 ordering and ordinary right-offset Y product unresolved.

The receipts bound these hypotheses only. No new exact match or unsupported ownership/return contract was inferred.

## 2026-09-07 scalar-vector input controls

`scalar-vector-operation-inputs-20260907.json` compares const scalar value
and reference inputs, plus free multiplication with a vector reference and
either scalar form. Each overlay preserves the component result body, vector
layout, and all out-of-line call contracts. All four forms are byte-neutral
in this caller. The five-function batch covers Golb traversal, slug explosion,
S-bend, and both exact fringe builders; no shared-header change is retained.
The recurring x87 operand choices remain open.

## 2026-09-07 shared vector width and array-loop controls

The six-function batch tests the two traversal methods, slug burst, S-bend,
and both exact fringe builders. Its double-value and const-double-reference
formals preserve the XYZ result body; its array-backed controls separate the
storage view from forward/reverse three-lane arithmetic loops. All retain the
12-byte vector layout and every out-of-line call contract. These are diagnostic
header shadows; no shared header is changed.

| Control | Match | Candidate instructions | Prefix | References ok / mismatch / unaudited |
| --- | ---: | ---: | ---: | --- |
| double | 99.29% | 425 | 96 | 7 / 0 / 0 |
| const-double-ref | 98.82% | 425 | 96 | 7 / 0 / 0 |
| array-owner-explicit-components | 99.29% | 425 | 96 | 7 / 0 / 0 |
| array-owner-forward-loop | 96.71% | 427 | 96 | 7 / 0 / 0 |
| array-owner-reverse-loop | 77.43% | 430 | 2 | 7 / 0 / 0 |

The storage-only array view is neutral; both arithmetic loops regress every
member. Wider shared formals regress both exact fringe controls, so the slug
instruction-count gain cannot justify changing the shared operator. Only the
slug's independently tested local-result follow-up is retained; this canonical
source remains unchanged. The receipts preserve the full compiled identities
and reference debt rather than interpreting an unchanged score as exact code.

## 2026-09-25 x87 operand order of `basis_right * local_x`

Rule: [x87-order.md](../../c2/x87-order.md). VC6 loads the first-sorted
operand.

- The inlined products compare the scale copy (local slot 0x1eb) with the
  scalarized `transform.basis_right` fields (slots 0x14d, 0x14f, 0x151).
  Scale sorts first in all three lanes, so every lane is `fld st(0)`/`fmul`.
- Native loads the field only in Y. That needs field X < scale < field Y:
  slot 0x14e, which isn't allocatable here, or a temporary with id mod 1024
  equal to 0xa7.
- Controls:
  - inline `(input_position->x - center_x)`: 5/5 structural;
  - explicit components: 5/5;
  - a copied `right` vector: 5/5;
  - `double local_x`: unchanged 3/3.

No source change.

## 2026-09-25 scheduler trace: the launch `fld st(0)` needs one IL_FROUND

Unchanged at **99.29%**; the fix below is not retained. `schedtrace.py
traverse_path_follow_golb --line 34`, window 6: the dup `fld st(0)` of
`carry` is ready at c15, three cycles after `carry`'s `fadd`. It issues
before `lea eax, [eax+eax*2]`, which becomes ready at c16 (AGI latency 2).
Native has the `lea` first. That is exactly the schedule you get when one
`IL_FROUND` sits between the `fadd` and the dup: the FROUND takes c15, then at
c16 the `lea` (height 91) beats the dup (height 88).

The FROUND needs the sum to be a single-use definition. For example:

```cpp
float travel = delta + launch_template->width_or_scale;
float carry = travel;
```

This gives **99.53%**, prefix 96 → 327, with identical code. The remaining
change is the x87 operand form at 327 (`fld [esp+0x48]; fmul st(1)` versus our
`fld st(0); fmul [esp+0x48]`). The copy local is not a plausible authored
form, so it is not retained.

| Variant | Result |
| --- | --- |
| `carry = delta; carry += w` | +1 tuple before the `fadd`; no effect |
| a named width | +1 tuple before the `fadd`; no effect |
| `basis_forward * carry` (operator) | code changes, 97.88–98.82% |
| a `double` carry | code changes, 97.88–98.82% |

`update_track_attachment_follow_state` window 16 has the identical shape
(lines 254–257), and the same single-use sum would fix its first region.

## 2026-09-26: parenthesized carry supplies the FROUND

**99.29% → 99.53%**, prefix 96 → 327, 425/425 instructions.

**Change.** `float carry = (delta + launch_template->width_or_scale);`

**Why it works.** C1XX emits an IL_FROUND after a parenthesized non-leaf float expression (crimson-88; see
scheduler.md, "Codeless tuples"). That is exactly the one codeless tuple the window needed. Earlier it
could only be reached with a rejected copy local (`float travel = …; float carry = travel;`).

**Remaining.** The Y-lane x87 operand order of `transform.basis_right * local_x`. Native loads the field
first; ours loads the scale. This is the slot-id tie described in x87-order.md.

## 2026-09-26: scale-operand rank decoded (crimson-88 Q12), not adopted

The Y-lane order depends on symbol record creation order. The scale operand is `local_x` itself; the
inliner substitutes it, so there is no inline copy.

**crimson's 100%-normalized overlay** (`scale-operand-rank.md`):
- `transform.basis_right *= lateral_scale;` in both branches;
- component-wise products with `(local_x = input_position->x - center_x)` inside the X lane.

**Not adopted:**
- it needs an assignment inside an expression;
- it is still not byte-exact: `state=audit`, with `fdiv [eax+esi+0x8c]` SIB base/index swaps at +0x254,
  +0x28a, +0x2c0 (already present in the base) and +0x46c.

The retained 99.53% source also carries those three SIB swaps.

## 2026-09-26: redundant template reload removed (fixes 3 SIB bytes)

The second `current_template = template_record;` after the loop is deleted. The normalized listing is
unchanged (99.53%), but the three `fdiv [..+0x8c]` SIB bytes (+0x254, +0x28a, +0x2c0) become native's.

**Mechanism** (crimson-88, `sib-operand-order.md`).
- The reassignment killed the CSE of `current_template + 0x5c`, so each load became an unCSE'd address
  expression. Expressions always sort first, so the bank was the base.
- Without it, the bank address is CSE temp 0x303. The load is then a leaf with hash 0xc007, which is below
  the offset temp's 0xc240, so the offset is the base, as in native.

**Remaining:** only the Y-lane operand rank.
- In the y2 variant (component lanes, each using `(input_position->x - center_x)`), the scale is CSE
  temp 0x4ab and the fields are 0x1e8/0x1ec. Native's order would need the temp at slot mod 1024 = 0xf5,
  or the field records to straddle 2·0xab = 0x156.
- Without an assignment inside an expression, this is id-tuning only. Not pursued.
