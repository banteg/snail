# initialize_snake_path_template_pair

Honest starter scratch for `initialize_snake_path_template_pair @ 0x423580`.

The callsite passes six stack arguments and the native epilogue is `ret 0x18`.
The first float-like slot is preserved even though the recovered constructor
body uses the width and texture slots. The scratch models the six straight
lead-in nodes, three lead-out nodes, the raised snake body, fixed-right
orientation, delta generation, mesh quads, and `calc_path_length_z`.

Residuals are expected; this is intentionally semantic starter source rather
than an instruction-scheduled near match.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 8.90% (112/652
candidate/target instructions) to 13.74% (542/652), with masked operands
improving from 8 ok, 0 unresolved, 5 mismatch to 23 ok, 0 unresolved, 4
mismatch.

2026-07-03 Phase B pass: reloading primary and secondary sample X from the
primary `center_x` field instead of the constant argument moves focused Wibo to
13.98% (535/652), with masked operands unchanged at 23 ok, 0 unresolved, 4
mismatch.

2026-07-03 width-local lifetime: the width-derived `right` value is only used by
the right lead-out and raised body samples, not the six zero lead-in samples.
Delaying that local until after the lead-in seed loop moves focused Wibo from
13.98% (535/652) to 14.49% (535/652), with masked operands improving from
23 ok, 0 unresolved, 4 mismatch to 25 ok, 0 unresolved, 4 mismatch.

2026-07-03 Z-index helper spelling: keep the sample helper argument as an
integer index and perform the int-to-float Z conversion inside the inlined
helper after the primary identity call. Focused Wibo moves from 14.49%
(535/652) to 14.53% (532/652), with masked operands unchanged at 25 ok,
0 unresolved, 4 mismatch.

2026-07-03 orientation-bound probe rejected: extending the identity-orientation
branch from `current_index <= first_index` to `current_index <= first_index + 1`
did not change focused Wibo (14.53%, 532/652) or the masked audit (25 ok,
0 unresolved, 4 mismatch). The native `set_matrix_rotation_identity` vs
candidate `normalize_vector` pairings therefore remain treated as alignment
drift rather than a retained semantic change.

2026-07-03 middle-loop expansion: expanding the curved body sample setup out of
the generic pair helper matches the native ordering better. The center reloads
the seeded right-side sample, primary Y is computed after primary identity, and
secondary Y recomputes the cosine-derived height after secondary identity.
Focused Wibo moves from 14.53% (532/652) to 15.50% (535/652), with masked
operands improving from 25 ok, 0 unresolved, 4 mismatch to 29 ok, 0 unresolved,
3 mismatch. Retesting the `current_index <= first_index + 1` orientation-bound
probe against this expanded body stayed exactly neutral at 15.50%, so the
original bound remains retained.

Rejected: expanding the six lead-in samples and three lead-out samples from the
generic pair helper regressed focused Wibo from 15.50% (535/652) to 15.41%
(542/652), with the masked audit unchanged at 29 ok, 0 unresolved, 3 mismatch.
The lead/tail helper shape stays retained despite the decompiler's flattened
loops.

Rejected: spelling the curved body with a separate zero-based logical counter
for angle/Z, like the decompiler, regressed focused Wibo from 15.50% (535/652)
to 15.46% (538/652). The masked audit stayed at 29 ok, 0 unresolved,
3 mismatch, so the `i - 6` angle spelling remains retained for now.

Rejected: swapping the strip-mesh allocation calls to request facequads before
vertices stayed neutral at 15.50% (535/652), with masked operands unchanged at
29 ok, 0 unresolved, 3 mismatch. It only flipped the mesh call mismatch from
target vertices vs candidate facequads to target facequads vs candidate
vertices, matching the earlier `sweep` rejection pattern.

2026-07-03 facequad inner loop: applying the same retained mesh spelling as
`sweep` emits the native two-iteration `face_index` loop and shared
`face->uv[3].v` tail store. Focused Wibo moves from 15.50% (535/652) to
21.33% (548/652), and masked operands improve from 29 ok, 0 unresolved,
3 mismatch to 33 ok, 0 unresolved, 3 mismatch. The two orientation
identity-vs-normalize pairings and the mesh request alignment pairing remain
honest residuals.

2026-07-03 half-angle cleanup: spelling the curved-body center expression as
`cosine(angle * 0.5f)` instead of materializing a `half_angle` local is focused
score neutral at 21.33% (548/652), with masked operands unchanged at 33 ok,
0 unresolved, 3 mismatch. The cleanup is retained as decompiler-shaped source
only; the same orientation and mesh-request residuals remain.

2026-07-04 retained orientation scheduling expansion: expanding the curved-body
orientation helper calls in place keeps the first curved sample's identity
branch paired across both lanes, then builds both right-vector orientation
frames inline. Focused Wibo moves from 21.33% (548/652) to 22.15% (549/652),
and masked operands improve from 33 ok, 0 unresolved, 3 mismatch to 35 ok,
0 unresolved, 1 mismatch. The remaining mismatch is only the mesh allocation
call pairing.

2026-07-04 mesh-vertex staging probe rejected: applying the `start` and
`supertramp` local `Vector3 generated_position` vertex-row staging to `snake`
regressed focused Wibo from 21.33% (548/652) to 20.55% (555/652). Masked
operands dropped from 33 ok, 0 unresolved, 3 mismatch to 31 ok, 0 unresolved,
3 mismatch, so `snake` keeps direct vertex component stores.

2026-07-04 post-orientation mesh request-order retest rejected: after the
retained orientation scheduling expansion, swapping strip-mesh allocation to
facequads-before-vertices stayed neutral at 22.15% (549/652) with masked
operands unchanged at 35 ok, 0 unresolved, 1 mismatch. The single mismatch
only flipped from target vertices vs candidate facequads to target facequads vs
candidate vertices, so the helper keeps vertices-first order.

2026-07-13 delta ownership: independently of `sweep`, the native `snake` body
also owns the primary and secondary delta loop directly. Removing the
scratch-local `compute_terminal_deltas(Path*)` alias, indexing both arrays from
the method owner, and addressing terminal samples directly as
`samples[segment_count - 1]` moves focused Wibo from 22.15% (549/652) to
30.15% (562/652). The masked audit improves from 35 ok, 0 unresolved,
1 mismatch to 37 ok, 0 unresolved, 0 mismatch. This is shared `Path` source
shape confirmed by a second target, not a copied register-lifetime trick.

2026-07-15 mesh ownership: the native vertex builder has distinct terminal-row
and ordinary-row scalar branches. Splitting the collapsed sample selection and
terminal Z ternary moves focused Wibo from 30.15% (562/652) to 30.33%
(568/652). Replacing the guarded face-column `for` with the native mutating
`do/while` then reaches 30.54% (566/652). Both changes preserve the clean
37 ok, 0 unresolved, 0 mismatch audit.

2026-07-15 induction ownership: the three departure samples recompute
`4.0 - width * 0.5` in their loop, and the native loop owns separate sample and
logical curve induction. Recomputing the departure center reaches 30.59%, and
the mutating departure `do/while` reaches 30.68%. Recovering the separate
zero-based curve counter finishes at 30.61% (570/652), a small fuzzy tradeoff
for source shape directly supported by both decompilers. Expanding the lead-in
and departure setup out of the obsolete scratch-local pair helper is codegen
neutral at that final score and makes the constructor's ownership explicit.
The masked audit remains 37 ok, 0 unresolved, 0 mismatch.

Rejected: changing the six-sample lead-in from its constant-bound `for` to an
explicit mutating `do/while` regressed focused Wibo from 30.61% (570/652) to
30.51% (574/652) without changing the clean audit. The compiler already emits
the required post-tested machine loop, so the smaller source form remains.

Not modeled: the target contains parity tests in each face branch, but both
outcomes push the same texture argument (`texture_a` for the first face and
`texture_b` for the second). Synthesizing a source-level no-op conditional
would be fakematching rather than recovered semantics, so the scratch leaves
that scheduling artifact as an honest residual.

2026-07-17 live owner-ABI closure: the native tail at `0x423ef4` is
`retn 0x18`, the iOS counterpart is
`cRPath::BuildSnake(float, int, bool, char*, char*)`, and the Windows caller
supplies the additional final cap-texture argument. Binary Ninja's stale view
returned `int32_t`, owned a `PathTemplate*`, and exposed only `int32_t, char*,
char*`; an authored `arg4` survived at `+0x10`, `+0x14` was analyzer-owned, and
`+0x18` was absent. The guarded recreation now owns the exact void `Path*`
contract and all six stack arguments. Post-restart readback confirms authored
parameter storages `+4..+24`. This is analysis-only: focused Wibo remains
30.61% (570/652), with 37 clean masked operands and no unresolved or mismatched
operands.

2026-07-20 live lifetime closure: the separately previewed snake schedule
recovers nine clean borrowed owners: the preceding primary/secondary right
vectors, both current-sample reloads, both terminal deltas, the current mesh
sample, and two complete facequad records. The initial sample cursor and
previous-row cursor stay automatic because their negative byte-relative
addresses became less exact when typed. One existing decompiler presentation
residual remains honest: `primary_samples_4->__offset(0x1050).d` is the MLIL
read of `primary_samples[24].center_x`, because the 24-sample stride plus the
field offset is `24 * 0xa8 + 0x90 == 0x1050`; there is no distinct pointer
lifetime to rename or type. No synthetic array view is introduced.
This is analysis-only: focused Wibo remains 30.61% (570/652), with 37 clean
masked operands and no unresolved or mismatched operands.

## 2026-07-26 coupled mesh ownership

Snake's raw mesh block at `0x423bc4..0x423c98` is instruction-for-instruction
parallel to Sweep's. It proves separate ordinary lateral-offset and generated
position owners, plus terminal lateral-offset, raised-endpoint, and generated
position owners. Each branch materializes its destination vertex only after
those values are complete. Native decompilation also proves independent first
and second face records with complete UV tails.

Recovering that coupled set raises focused matching from 30.61% to **33.49%**,
grows the candidate from 570 to **620/652** instructions, moves the prefix from
0 to **5**, and recovers the exact native `0x54` frame. The masked audit remains
clean at 36 accepted, 0 unresolved, 0 mismatched operands. As with Sweep, the
equal-texture parity branches remain absent rather than being synthesized for
code shape.

## 2026-07-27 paired-mobile ownership refinement

The exact Android and iOS `cRPath::BuildSnake(float, int, bool, char*, char*)`
symbols prove the boolean ABI. Their paired bodies branch on the logical curve
induction owner at zero, so the derived `i <= 6` guard is now spelled
`curve_index == 0`. That raises focused matching from **33.49%** to **33.70%**
and shrinks the candidate from 620 to **618/652** instructions, while
preserving the five-instruction exact prefix and a clean 40-operand masked
audit.

Both mobile bodies stop after sample/delta construction and `CalcLengthZ`;
Windows owns the cap-texture and mesh-building tail. Binary Ninja preview,
apply, readback, and lifetime replay kept every recovered owner current.

## 2026-07-28 complete control and mesh lifetime replay

The paired Android and iOS bodies independently preserve the six-sample
lead-in, three-sample lead-out, 18-sample curve induction, and phase graph.
Exact Windows MLIL then separates those logical owners from the width argument
and proves the Windows-only mesh-column, UV, winding-pass, and repeated
EAX/ECX/EDX width-reload lifetimes.

One batched transaction previewed, applied, read back, and snapshotted 22 split
groups plus two bounded stack scalars for Snake, as part of the 44-group,
four-scalar Sweep/Snake replay. An idempotent pair replay completed in about
39 seconds. Strict paired Binary Ninja and IDA 9.4 export reports zero
mismatches and 1,142/1,142 passing health checks. The IDA refresh is retained
because it recovers the current `void Path*` seven-argument ABI and `Object*`
owner in place of the stale three-argument `PathTemplate*` view, rather than
merely changing temporary names.

This is analysis-only. Focused matching remains **33.70%** (618/652 candidate
instructions), with a five-instruction exact prefix and 40 accepted,
0 unresolved, 0 mismatched, and 0 unaudited operands. No source edit or
synthetic branch was introduced.

## 2026-07-30 authored terminal-delta subtraction

The exact SlalomDouble terminal-delta block transfers without adaptation.
Replacing both component constructors with the authored `Vector3::operator-`
form adds 7.67 weighted bytes and raises focused matching from 33.70% to
**34.02%**. The candidate remains 618/652 instructions, prefix 5/652, with all
40 references clean; either isolated operator gains half as much.

## 2026-07-30 orientation subtraction bound

Both inline orientation expressions were tested independently and together.
All three authored-operator variants compile byte-identically. Snake remains
**34.02%**, 618/652 instructions, prefix 5/652, with all 40 references clean.

## 2026-07-30 mesh arithmetic ownership

Snake's mesh target is instruction-for-instruction parallel to Sweep's and
preserves the same x87 lateral lifetime across its already-recovered
five-vector graph. `double lateral` gains 6.47 weighted bytes. Both position
additions improve independently and gain 9.03 together; both scale operators
then improve independently and gain 41.00 together.

The retained symmetric package raises focused matching from 34.02% (618/652)
to **36.33%** (614/652), a total gain of 56.49 weighted bytes. The
five-instruction prefix and all 40 masked references remain clean. As in
Sweep, the four-instruction shortening is accepted because the changes are
bounded to the directly proven native arithmetic owners.

## 2026-07-30 direct lead and departure sample ownership

Windows repeatedly reloads the primary and secondary sample arrays through a
byte-offset induction in both the six-sample lead and three-sample departure
phases. Android and iOS preserve the same owning arrays. The scratch-local
`primary` and `secondary` convenience pointers incorrectly collapsed those
loads and kept two sample bases live.

A complete seven-variant phase interaction sweep proves the direct indexed
form. Retaining it for the lead and departure phases raises focused matching
from **36.33%** (614/652) to **47.12%** (634/652), a gain of 263 weighted
bytes, with the five-instruction prefix and all 40 references clean. The same
form is negative in Snake's curve phase, both alone and in the winning
interaction, so the curve's recovered previous/current owners remain intact.

The native mesh tail also computes a flat face index before selecting the
winding branch. Three equivalent shared-index spellings were recorded, but
all produce the same marginal tradeoff: four additional weighted bytes while
removing five candidate instructions and moving farther from the
652-instruction target. That face-index form is not retained, and the equal-
texture parity branches remain deliberately absent.

## 2026-07-30 lead X and delta-count ownership

Native `0x423603..0x423649` writes literal zero to both lead-sample X
positions after their matrix calls. The scratch instead reloaded the earlier
`center_x` value across each call. Either isolated correction disrupts the
shared zero lifetime and regresses, but the dependency-complete pair removes
the four reload/store instructions absent from the target and gains 30.18
weighted bytes:

```text
match: 48.36% (was 47.12%)
target: 652 insns, candidate: 630 insns (was 634)
prefix: 5/652 target insns
masked operands: 40 ok, 0 unresolved, 0 mismatch, 0 unaudited
```

The delta-loop preheader at `0x4239d3..0x4239de` then materializes
`segment_count - 1`, tests that derived count, and enters only when it is
positive. Recovering that signed guard adds 25.66 more weighted bytes and one
candidate instruction:

```text
match: 49.42%
target: 652 insns, candidate: 631 insns
prefix: 5/652 target insns
masked operands: 40 ok, 0 unresolved, 0 mismatch, 0 unaudited
```

The combined retained gain is 55.85 weighted bytes. An explicit lead byte
offset reproduces the already-proved dual induction but gains only 0.92
weighted bytes while removing another instruction, so that marginal source
expansion is rejected. Splitting the reused source sample index into separate
lead and curve declarations, independently and together, is byte-identical;
the existing compact spelling remains.

## 2026-07-30 curve ownership bound

Windows reloads both curve sample arrays through indexed expressions for the
initializer and orientation blocks, but transferring those expressions into
the scratch changes the enclosing register allocation destructively. A
complete direct initializer-and-orientation transfer reaches exactly 652/652
candidate instructions yet falls from **49.42%** to **44.48%**. Transferring
only the orientation owners is also negative at **45.74%** (638/652), a loss
of 89.62 weighted bytes.

The two lanes were then isolated to rule out a coupled allocation artifact:

```text
direct primary orientation:   41.93%, 636/652, -182 weighted bytes
direct secondary orientation: 42.20%, 637/652, -176 weighted bytes
```

All variants preserve the five-instruction prefix and the clean 40-reference
audit. Because each direct lane independently regresses, exact instruction
count in the complete transfer is not evidence of recovered ownership. The
retained previous/current pointer form remains the strongest measured source
at **49.42%**, 631/652 instructions.

## 2026-07-30 checkerboard texture control

The earlier classification of Snake's equal-texture parity tests as an
isolated scheduling artifact is superseded by the recovered path-constructor
family. LoopOut, Start, Screw, Hump, Dip, Invert, Twister, Supertramp, and
other independent Windows builders preserve the same checkerboard
`(column ^ row) & 1` generator branch even when both outcomes request the same
per-face texture. Snake's target contains the complete duplicated-call form at
`0x423dae..0x423e05` and `0x423e61..0x423eff`.

The exhaustive two-site sweep confirms that the two face branches are a
dependency-complete source unit. The first branch alone loses 5.54 weighted
bytes, while the second alone gains only 13.30. Restoring both adds **118.48
weighted bytes**, raises focused matching from **49.42% to 54.28%**, grows the
candidate from 631 to **645/652** instructions, and extends the exact prefix
from 5 to **21/652**. All 40 references remain clean.

Truth-first and negated polarity spellings compile byte-identically in every
pairing, so the canonical truth-first family form is retained. This recovers
the repeated source-family control flow visible in the binary; it does not
invent a semantic texture distinction between equal arms.

## 2026-07-30 lead cursor and curve-initializer ownership

The checkerboard recovery changes the surrounding allocation enough to make
the previously marginal lead byte cursor decisive. Advancing a byte offset by
`sizeof(PathTemplateSample)` while keeping `i` as the logical Z owner raises
focused matching from **54.28%** (645/652) to **55.25%** (644/652), gains
23.58 weighted bytes, and extends the exact prefix from 21 to **64/652**.

The curve has a narrower ownership split than the earlier all-or-nothing
transfer suggested. Its initializer repeatedly reloads the two sample arrays,
while its orientation block keeps the recovered previous/current sample
pointers live. Retaining direct indexed initializer stores with pointer-owned
orientation raises focused matching from **55.25%** (644/652) to **58.96%**
(654/652), a gain of 90.42 weighted bytes. The 64-instruction prefix and all
40 masked references remain clean.

Reverse sweeps from the final source make both dependencies explicit:

```text
direct lead index:          57.23%, 655/652, prefix 21, -42.10 weighted bytes
borrowed initializer pair:  55.25%, 644/652, prefix 64, -90.42 weighted bytes
direct orientation arrays:  48.29%, 665/652, prefix 6, -259.85 weighted bytes
```

An explicit byte cursor for the curve itself gained only about two weighted
bytes before the initializer recovery, removed two candidate instructions,
and did not improve the prefix or reference audit, so it was rejected. The
final retained form therefore models three distinct lifetimes: byte-relative
lead traversal, indexed curve initialization, and pointer-owned curve
orientation.
