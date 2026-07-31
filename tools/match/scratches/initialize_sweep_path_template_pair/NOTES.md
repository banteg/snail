# initialize_sweep_path_template_pair

Honest starter scratch for `initialize_sweep_path_template_pair @ 0x422c00`.

The constructor callsite passes six stack arguments and the native tail is
`ret 0x18`. The first float-like slot is preserved but not used by the
recovered body. The scratch builds the 30-node sweep with three lead-in nodes,
three lead-out nodes, cosine-shaped lateral motion, a shallow sine Y sweep,
sample deltas, strip mesh quads, and `calc_path_length_z`.

Residuals are expected. This is a semantic starter with local helper routines,
not an instruction-scheduled match attempt.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 7.04% (115/652
candidate/target instructions) to 13.71% (544/652), with masked operands
improving from 4 ok, 0 unresolved, 6 mismatch to 24 ok, 0 unresolved, 1
mismatch.

2026-07-03 Phase B pass: reloading primary and secondary sample X from the
primary `center_x` field instead of the constant argument moves focused Wibo to
13.88% (544/652), with masked operands unchanged at 24 ok, 0 unresolved, 1
mismatch. A loop split with delayed sine-derived Y/Z stores was rejected: it
nudged the score only to 13.74% (556/652) while worsening the masked audit to
21 ok, 0 unresolved, 2 mismatch.

2026-07-03 width-local lifetime: the right-side constant is not needed until
after the three left lead-in samples. Delaying the `right` local until after
that seed loop moves focused Wibo from 13.88% (544/652) to 14.30% (537/652),
with masked operands improving from 24 ok, 0 unresolved, 1 mismatch to 26 ok,
0 unresolved, 1 mismatch.

Rejected: applying the snake-style integer Z-index helper spelling regressed
focused Wibo to 14.17% (534/652) and worsened the masked audit to 22 ok,
0 unresolved, 4 mismatch, so sweep keeps the float-Z helper argument.

Rejected: swapping the strip-mesh allocation calls to request facequads before
vertices stayed at 14.30% (537/652) and simply flipped the single masked
mismatch from target `request_object_vertices` vs candidate
`request_object_facequads` to the reverse pairing. The retained order remains
vertices before facequads.

2026-07-03 direct sample loops: expanding the three lead-in samples, three
lead-out samples, and curved body from the generic pair helper follows the
decompiler shape. The lead-in/tail loops keep the index float conversion after
primary identity, the curved body reloads the seeded primary `center_x`, and
secondary Y derives from the written primary Y. Focused Wibo moves from 14.30%
(537/652) to 14.85% (533/652), with masked operands improving from 26 ok,
0 unresolved, 1 mismatch to 27 ok, 0 unresolved, 1 mismatch.

Rejected: spelling the curved body with a separate zero-based logical counter
for angle/Z, like the decompiler, regressed focused Wibo from 14.85% (533/652)
to 14.81% (536/652). The masked audit stayed at 27 ok, 0 unresolved,
1 mismatch, so the `i - 3` angle spelling remains retained for now.

2026-07-03 facequad inner loop: spelling mesh face emission as the native
two-iteration `face_index` loop, with a single `face->uv[3].v` tail store,
moves focused Wibo from 14.85% (533/652) to 25.04% (546/652). The candidate
stack frame grows from 0x44 to 0x48 and masked operands improve from 27 ok,
0 unresolved, 1 mismatch to 32 ok, 0 unresolved, 1 mismatch. The remaining
masked mismatch is still the `request_object_vertices` /
`request_object_facequads` alignment pairing, not a retained request-order
change.

Rejected: the `p`/`snake` orientation scheduling expansion does not transfer to
`sweep`. Expanding both lane orientations inline regressed focused Wibo from
25.04% (546/652) to 20.02% (547/652), and reduced masked operands from
32 ok, 0 unresolved, 1 mismatch to 29 ok, 0 unresolved, 1 mismatch. The compact
helper calls stay retained.

2026-07-04 mesh-vertex staging probe rejected: unlike `start` and `supertramp`,
routing the vertex row calculation through a local `Vector3 generated_position`
regressed focused Wibo from 25.04% (546/652) to 17.26% (553/652). It did clear
the masked audit from 32 ok, 0 unresolved, 1 mismatch to 25 ok, 0 unresolved,
0 mismatch, but the score loss is too large for the Phase B ratchet. Keep the
direct component stores in the sweep vertex loop.

2026-07-13 delta ownership: the native body owns both sample arrays and their
delta loop directly; the scratch-local `compute_terminal_deltas(Path*)` helper
kept `Path` behind an alias for the whole region. Expanding the loop against
`primary_samples` and `secondary_samples` moves focused Wibo from 25.04%
(546/652) to 27.14% (549/652), with the masked audit unchanged at 32 ok,
0 unresolved, 1 mismatch.

Addressing each terminal sample directly as `samples[segment_count - 1]`,
instead of extending a shared `terminal_index` lifetime, then moves focused
Wibo to 32.70% (559/652) and clears the masked audit to 34 ok, 0 unresolved,
0 mismatch. This recovers a real `Path` ownership boundary and the native
count-relative terminal addressing; it is not a register or scheduling shim.

2026-07-15 mesh and departure ownership: unlike the rejected aggregate probe,
the native scalar mesh spelling separates the extrapolated terminal row from
ordinary rows. That moves focused Wibo from 32.70% (559/652) to 32.87%
(565/652). The native face-column `do/while` reaches 33.09% (563/652), and a
mutating three-sample lead-out reaches 33.17% (566/652), with all 34 masked
operands still clean.

2026-07-15 center and curve-counter ownership: both fixed edge loops recompute
their center from `width_cells` inside each iteration, rather than retaining
shared `left` and `right` values across matrix calls. Recovering both lifetimes
reaches 33.28% (562/652). The curved body now also retains the native
zero-based 24-sample logical counter separately from sample indices 3..26.
That target-backed induction variable leaves the final focused result at
33.20% (565/652), with 34 clean masked operands and no unresolved or mismatched
operands. The small fuzzy tradeoff is retained as an ownership clarification,
not compensated with a synthetic scheduling hint.

2026-07-17 live owner-ABI closure: the native tail at `0x42356c` is
`retn 0x18`, the iOS counterpart is
`cRPath::BuildSweep(float, int, bool, char*, char*)`, and the Windows caller
supplies the additional final cap-texture argument. Binary Ninja's stale view
returned `int32_t`, owned a `PathTemplate*`, and exposed only `int32_t, char*,
char*`; analyzer-only candidates occupied `+0x10/+0x14`, while `+0x18` was
absent. The guarded recreation now owns the exact void `Path*` contract and all
six stack arguments. Post-restart readback confirms authored parameter storages
`+4..+24`. This is analysis-only: focused Wibo remains 33.20% (565/652), with
34 clean masked operands and no unresolved or mismatched operands.

2026-07-20 live lifetime closure: transactional MLIL preview identifies nine
clean borrowed owners without changing the native source hypothesis: the
preceding primary/secondary forward vectors, both current-sample reloads, both
terminal deltas, the current mesh sample, and the two complete facequad
records. Their guarded replay resolves direct `Vec3`, `PathTemplateSample`, and
`ObjectFaceQuad` fields throughout the exported decompile. The initial sample
cursor and previous-row cursor remain automatic because typing their negative
byte-relative addressing made the output less exact. This is analysis-only:
focused Wibo remains 33.20% (565/652), with 34 clean masked operands and no
unresolved or mismatched operands.

## 2026-07-26 coupled mesh ownership

Raw native instructions at `0x42323c..0x423310` prove the complete mesh value
graph that earlier isolated aggregate probes missed. The ordinary branch owns
a lateral offset, generated position, and late destination vertex. The
terminal branch separately owns a lateral offset, raised endpoint, generated
position, and late destination vertex. Native decompilation also exposes
independent first and second face records, each including its final UV write.

Replaying the complete dependent owner set raises focused matching from 33.20%
to **35.67%**, grows the candidate from 565 to **615/652** instructions, moves
the prefix from 0 to **5**, and recovers the exact native `0x54` frame. The
masked audit remains clean at 33 accepted, 0 unresolved, 0 mismatched operands.
The native equal-texture parity branches remain deliberately absent: adding
them would not recover behavior or ownership.

## 2026-07-27 paired-mobile ownership refinement

The exact Android and iOS `cRPath::BuildSweep(float, int, bool, char*, char*)`
symbols prove the boolean ABI. Their paired bodies branch on the logical curve
induction owner at zero, so the derived `current_index <= 3` guard is now
spelled `curve_index == 0`. That raises focused matching from **35.67%** to
**35.86%** and shrinks the candidate from 615 to **614/652** instructions,
while preserving the five-instruction exact prefix and a clean 37-operand
masked audit.

Both mobile bodies stop after sample/delta construction and `CalcLengthZ`;
Windows owns the cap-texture and mesh-building tail. Binary Ninja preview,
apply, readback, and lifetime replay kept every recovered owner current.

## 2026-07-28 complete control and mesh lifetime replay

The paired Android and iOS bodies independently preserve the three-sample
lead-in, three-sample lead-out, 24-sample curve induction, and phase graph.
Exact Windows MLIL then separates those logical owners from the width argument
and proves the Windows-only mesh-column, UV, winding-pass, and repeated
EAX/ECX/EDX width-reload lifetimes.

One batched transaction previewed, applied, read back, and snapshotted 22 split
groups plus two bounded stack scalars for Sweep, as part of the 44-group,
four-scalar Sweep/Snake replay. An idempotent pair replay completed in about
39 seconds. Strict paired Binary Ninja and IDA 9.4 export reports zero
mismatches and 1,142/1,142 passing health checks. The IDA refresh is retained
because it recovers the current `void Path*` seven-argument ABI and `Object*`
owner in place of the stale three-argument `PathTemplate*` view, rather than
merely changing temporary names.

This is analysis-only. Focused matching remains **35.86%** (614/652 candidate
instructions), with a five-instruction exact prefix and 37 accepted,
0 unresolved, 0 mismatched, and 0 unaudited operands. No source edit or
synthetic branch was introduced.

## 2026-07-30 authored terminal-delta subtraction

The exact SlalomDouble terminal-delta block transfers without adaptation.
Replacing both component constructors with the authored `Vector3::operator-`
form adds 7.67 weighted bytes and raises focused matching from 35.86% to
**36.18%**. The candidate remains 614/652 instructions, prefix 5/652, with all
37 references clean; either isolated operator gains half as much.

## 2026-07-30 orientation subtraction bound

The previous/current orientation helper was tested with the authored operator
form and is byte-identical. Sweep remains **36.18%**, 614/652 instructions,
prefix 5/652, with all 37 references clean.

## 2026-07-30 mesh arithmetic ownership

The native x87 block at `0x423226..0x423310` keeps one lateral value across the
already-recovered five-vector branch graph. `double lateral` gains 6.63
weighted bytes. Both position additions improve independently and gain 9.11
together; both scale operators then improve independently and gain 40.91
together.

Retaining the complete symmetric arithmetic package raises focused matching
from 36.18% (614/652) to **38.51%** (610/652), a total gain of 56.65 weighted
bytes. The five-instruction prefix and all 37 masked references remain clean.
The candidate becomes four instructions shorter, but no control or vertex
lifetime changes: every edit is confined to the native x87/vector ownership
already proved for this mesh.

## 2026-07-30 direct sample-array ownership

Windows repeatedly reloads the primary and secondary sample arrays through
byte-offset inductions in the lead, departure, and curve phases. Android and
iOS retain the same two owning arrays. The scratch-local `primary` and
`secondary` convenience pointers incorrectly collapsed those loads and
extended two derived sample bases across each phase.

All seven phase combinations were compiled and recorded. Each direct phase
improves independently, and the complete three-phase package is the unique
winner: focused matching rises from **38.51%** (610/652) to **51.67%**
(637/652), a gain of 319 weighted bytes. The five-instruction prefix and all
37 masked references remain clean, with no unresolved, mismatched, or
unaudited operands.

## 2026-07-30 delta-count guard non-transfer

Snake's derived `segment_count - 1 > 0` delta guard does not transfer across
the otherwise parallel constructor family. All three equivalent derived-count
spellings destabilize Sweep's allocation, add four or five instructions, and
fall from **51.67%** to 41.89%..41.92%. The retained `segment_count > 1`
guard therefore remains independently measured rather than being normalized
to the Snake spelling.

## 2026-07-30 direct curved-orientation ownership

The earlier inline-orientation probe predated the dependency-complete direct
sample-array transfer and was no longer representative. Windows
`0x422eb9..0x423028` owns one shared first-curve branch and then independently
reloads both sample arrays for the preceding/current orientation work.
Replaying that complete block against the current baseline changes the result
in the opposite direction from the old probe:

```text
match: 55.19% (was 51.67%)
target: 652 insns, candidate: 649 insns (was 637)
prefix: 5/652 target insns
masked operands: 37 ok, 0 unresolved, 0 mismatch, 0 unaudited
```

This adds 85.47 weighted bytes. Mixed ownership confirms that the symmetric
transfer is dependency-complete: direct primary with pointer-owned secondary
falls to 44.51% (642/652), while pointer-owned primary with direct secondary
reaches 54.50% (647/652) but still trails the fully direct form.

The bounded first-sample guard grid leaves `curve_index == 0` strongest.
Logical negation is byte-identical; signed-zero forms lose one weighted byte;
and the equivalent sample-index forms lose 1..136 weighted bytes. The direct
block is retained because it matches the independently recovered Windows
owners and is the unique measured winner, not because it happens to leave the
candidate three instructions short of the target.

## 2026-07-30 checkerboard texture control

Snake's dependency-complete checkerboard recovery justified revisiting the
same omitted source-family unit here. Sweep's target preserves duplicated
per-face texture calls behind `(column ^ row) & 1` at
`0x423426..0x42347d` and `0x4234d9..0x423577`. As in Snake and the broader
constructor family, both outcomes request the same texture for their winding
pass.

All eight one- and two-site variants compile. The first branch alone loses
7.55 weighted bytes, while the second alone gains only 10.89. Restoring the
dependency-complete pair adds **151.84 weighted bytes** and raises focused
matching from **55.19% to 61.44%**. The candidate grows from 649 to
**663/652** instructions and the exact prefix moves from 5 to **6/652**; all
37 references remain clean. Truth-first and negated spellings are
byte-identical, so the canonical truth-first family form is retained.

The eleven-instruction excess is recorded rather than optimized by score.
The adjacent target does compute one flat face index before the winding
branch, but all five natural grouped, expanded, multiplied, and shifted source
spellings behave identically. Using that owner for the first face is
byte-neutral; using it for both faces shrinks the candidate to 653
instructions but loses 159.74 weighted bytes and falls to **54.87%**. This
bounded result rejects instruction-count chasing while preserving the
stronger source-backed control recovery.

## 2026-07-30 curve and departure byte cursors

The checkerboard and direct-array cascade invalidated the earlier logical
curve-index result. Windows keeps a physical `0x1f8..0x11b8` cursor advancing
by `0xa8` independently from the 24-step curve counter. Replaying that complete
address owner raises focused matching from **61.44% to 66.92%**, shrinks the
candidate from 663 to 657 instructions, and moves the exact prefix from 6 to
24 instructions. All 37 references remain clean.

Using the physical cursor for the first-orientation test is another
dependency-complete gain. The source-equivalent equality spelling
`i == 3 * sizeof(PathTemplateSample)` is strongest at **70.38%** and adds
84 weighted bytes; the monotonic `<=` forms rendered by the decompiler reach
68.70%, while `< next sample` reaches 68.55%. Constant and `sizeof` equality
spellings are byte-identical.

The distinct `0x11b8` departure cursor then adds 57 weighted bytes and reaches
**72.73%**. It removes one instruction without extending the logical
departure-index lifetime into sample addressing. The analogous lead cursor
recovers 21 more exact prefix instructions but falls to 72.02% on this
pre-orientation-operator baseline; mixing a physical primary lead cursor with
a logical secondary index falls further to 68.65%. Both lead forms are
therefore bounded rather than retained.

The complete retained cursor cascade is also recorded as a reverse probe
against the pre-milestone source:

```text
baseline: 73.19%, 657/652 instructions, prefix 24
revert:   61.44%, 663/652 instructions, prefix 6
delta:    +285 weighted bytes, +11.74 percentage points
```

## 2026-07-30 cursor-dependent orientation subtraction

The authored `Vector3::operator-` replay that was byte-identical before cursor
recovery becomes positive afterward. Both primary and secondary lanes must use
the operator form together: reverting either lane or both lanes loses the same
11 weighted bytes. Retaining the symmetric pair raises the final result from
72.73% to **73.19%**, with 657/652 instructions, prefix 24, and all 37
references clean.

Explicit previous/current sample pointers do not transfer from Snake. They
collapse the score to 55.09%, shorten the candidate to 655 instructions, and
leave two cross-product calls unaudited. Sweep therefore keeps the independent
array reloads proved by its own Windows body.

## 2026-07-30 post-cursor bounds

The surrounding stale controls were replayed after the complete cursor
cascade:

- all three derived delta-count guards fall to 64.74%..64.79%;
- every first-face flat-index spelling remains byte-identical, while applying
  the shared index to both faces falls to 57.98%;
- an explicit mesh-row byte cursor reaches 72.48%, and the complete guarded
  cursor control reaches 72.94%, both below the retained indexed loop;
- a shared mesh-sample pointer falls to 68.97%, while moving the row
  initialization to its native decompiler order is byte-identical;
- distinct logical face-column and UV-column owners fall to 72.12%.

These probes bound the adjacent control and mesh lifetimes without retaining
instruction-count or decompiler-shape regressions.

## 2026-07-31 direct face-offset record ownership

The common face scalar becomes productive only when every record field is
written directly through `facequads[face_offset]`. That source boundary raises
focused matching from **73.19%** to **80.18%** and moves candidate size from
657 to 650 instructions against the 652-instruction target. Prefix remains
24/652 and all 37 references remain clean.

This supersedes the earlier pointer-based flat-index rejection while leaving
the bounded row, UV, and cursor lifetimes unchanged.
