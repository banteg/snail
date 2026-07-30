# initialize_toad_path_template_pair

Starter reconstruction for `initialize_toad_path_template_pair @ 0x42cbf0`.

Captures the branch-dependent lead/exit counts, fixed width `4`, 26-sample turn
arc, Z-rotation by the recovered turn angle, secondary offsets, delta
recomputation, strip mesh generation, and finalization.

The scratch is an honest partial. The remaining gaps are the exact local/stack
shape and mesh-tail scheduling.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 9.55% (175/663
candidate/target instructions) to 19.25% (594/663), with masked operands
improving from 5 ok, 0 unresolved, 8 mismatch to 16 ok, 0 unresolved, 3
mismatch.

2026-07-03 angle-order split: spelling the turn angle as a separate `0.5f`
multiply before applying the branch sign and quarter-turn scale moves focused
Wibo to 19.40% (595/663), with masked operands improving to 18 ok, 0
unresolved, 2 mismatch. A neutral-sample/writeback probe raised the operand
count but reduced fuzzy score to 19.26%, so it was left out.

2026-07-03 parameter-width pass: focused head diff showed the native
constructor reads the branch selector as a byte (`mov al, [esp+4]`), while the
scratch declared it as an `int`. Narrowing the shared declaration and scratch
signature to `char turn_left` moves focused Wibo to 19.71% (595/663), exposes a
1-instruction prefix, and leaves masked operands unchanged at 18 ok, 0
unresolved, 2 mismatch. The remaining focused residual is stack-frame and
interior orientation/copy scheduling, not call ABI width.

2026-07-03 sample-scalar retry after ABI cleanup: after narrowing the branch
selector to `char`, removing the scratch-only `lateral_source` writes from the
primary initializer and secondary copy now improves focused Wibo from 19.71%
(595/663) to 19.79% (590/663). The 1-instruction prefix and masked audit stay
at 18 ok, 0 unresolved, 2 mismatch, so this is a small source-shape win while
the interior orientation/copy scheduling residual remains.

2026-07-03 secondary-flat scalar probe: removing the remaining flat secondary
`lateral_source` copy improved the masked audit to 18 ok, 0 unresolved, 1
mismatch, but regressed focused Wibo to 19.70% (586/663). Left out to preserve
the retained 19.79% source shape until the flat seed loop is rebuilt more
substantially.

2026-07-03 retained mesh-face loop: replacing the direct `a`/`b` face writes
with the two-texture `face_index` loop moves focused Wibo from 19.79% (590/663)
to 25.97% (600/663). The 1-instruction prefix is preserved and masked operands
improve from 18 ok, 0 unresolved, 2 mismatch to 22 ok, 0 unresolved,
2 mismatch. The remaining audit debt stays in the interior orientation/copy
schedule.

2026-07-13 terminal ownership: replacing `primary_last` and `secondary_last`
aliases with direct count-relative stores through the two `Path` sample arrays
moves focused Wibo from 25.97% (600/663) to 27.69% (608/663). The
1-instruction prefix is preserved and the masked audit remains 22 ok,
0 unresolved, 2 mismatch; both pre-existing interior orientation residuals are
unchanged. The delta loop retains its local sample pointers.

2026-07-13 interior lane ownership: the native post-orientation copy is a
0x40-byte `TransformMatrix` copy, so `center_x`, rotation, lateral-scale, and
special scalars remain primary-owned. Removing those non-native secondary
copies moves focused Wibo from 27.69% (608/663) to 27.94% (597/663). The
1-instruction prefix and masked audit remain unchanged at 22 ok, 0 unresolved,
2 mismatch.

2026-07-15 lane and interior ownership: the native flat secondary samples own
only their transform and `delta_length`; their X comes from the primary
`center_x`, Y is the authored constant `0.49000001f`, and Z shares the loop's
converted logical index. Rebuilding both flat loops around those direct array
writes, then spelling the 26-sample interior in native order, recovers the
primary-only scalar initialization, identity-before-sine schedule, local-Z
rotation, 0x40-byte transform copy, and basis-up offset. Focused Wibo rises
from 27.94% (597/663) to 45.89% (601/663), while the masked audit improves from
22 ok / 2 mismatch to 27 ok / 0 mismatch. A direct-array rewrite of the delta
loop regressed to 41.35%, so its better local sample-pointer shape remains.

2026-07-17 owner and ABI closure: the Windows body ends in `ret 0x10`, and all
four asset-constructor callsites push the turn selector plus three textures
after `this`. The previous Binary Ninja prototype left the fourth texture as an
unpromoted stack local, kept the receiver on the legacy partial `PathTemplate`,
and inferred an `int32_t` result from register residue. Guarded recreation now
records `void __thiscall(Path* self, char turn_left, char* texture_a, char*
texture_b, char* vertical_texture)`, and the tracked caller renders the complete
ABI including `Objects/Path/VeryDark.tga`. The matcher source already carried
that honest declaration, so focused Wibo remains **45.89%** (601/663), with its
1-instruction prefix and clean 27-operand masked audit unchanged.

## 2026-07-20 live lifetime ownership

A guarded Binary Ninja transaction now preserves eight complete live owners:
the interior primary right vector, secondary position, both terminal deltas,
the mesh sample and vertex, and both face records. Their accesses render
through `Vec3`, `PathTemplateSample`, and `ObjectFaceQuad` with zero residual
`__offset` expressions. Focused matching remains 45.89% (601/663), with its
1-instruction prefix and 27 clean masked operands.

## 2026-07-25 mesh-vector ownership

Raw native assembly at `0x42d222..0x42d2ff` proves that the row-terminal test
belongs inside the vertex column loop. Ordinary rows materialize one complete
generated-position vector. The terminal row separately owns a previous-sample
lateral-offset vector and a generated-position vector whose Z lane includes
`+1.0f`, matching the same source boundary recovered in SBend, Invert, and
Turnunder.

Recovering that proven source shape moves the candidate instruction count from
601 to 628 against the 663-instruction target. It regresses the global fuzzy
alignment from 45.89% to 44.15% and leaves 25 rather than 27 aligned masked
operands; all remaining masks are clean, with no unresolved or mismatched
operands. The ownership correction is retained despite the score regression:
the affected native region directly proves the aggregate temporaries, while
the lost alignment is downstream compiler scheduling rather than contrary
source evidence.

## 2026-07-26 complete mesh-vector ownership

The completed family model identifies the two owners missing from the first
Toad rewrite. Native `0x42d231..0x42d2ff` first materializes an ordinary-row
lateral-offset vector before the generated position. The terminal branch
separately owns an endpoint reached from the previous sample through the
current row cursor, with its Z lane extended by `1.0f`.

Adding those owners resolves the earlier scheduling regression: focused
matching rises from 44.15% (628/663) to 47.92% (635/663), restores the masked
audit from 25 to 27 clean operands with no unresolved or mismatched masks, and
recovers the exact native `0x54` frame. The exact prefix expands from one to 15
instructions. The face initializer now also names the owning 16-bit
`header_word` proven by the native word clear; that field-width correction is
score-neutral.

## 2026-07-26 portable selector type

Android and iOS independently export the exact mangled
`cRPath::BuildToad(bool, char*, char*)` symbol. That resolves the Windows
selector's previously known one-byte storage width from generic `char` to the
authored `bool turn_left` type. The Windows-only fourth stack argument remains
`vertical_texture`: native `ret 0x10` cleanup and all four world-initializer
callsites prove it, while the mobile builders stop before the Windows strip-mesh
tail and therefore expose only the portable two-texture surface.

The matcher declaration, authoritative analysis header, and Binary Ninja/IDA
replay specifications now agree on the boolean selector. VC6 emits the same
47.92% candidate (635/663), with its 15-instruction prefix and 33 clean masked
operands, so this is an ownership correction rather than a score claim.

## 2026-07-28 mobile-authored phase and control ownership

Both mobile `cRPath::BuildToad` bodies preserve the authored curved-section
phase as `k * 6.2831855f / 26.0f` and the turn angle as
`(1 - cos(phase)) * 0.5f * turn_sign * 3.1415927f * 0.5f`. Restoring that
hierarchy in the Windows scratch is byte-identical: VC6 folds it to the same
`0.241660982f` and `1.57079637f` operands, retaining the honest 47.92% result,
635/663 instructions, 15-instruction prefix, and all 33 masked operands clean.

The two ports also corroborate the Windows branch-selected lead count, tail
count, starting X, and turn sign. Binary Ninja had inferred the lead-count
stack lifetime as `PathTemplateSample*`, which turned integer additions into
false matrix-field expressions. The guarded replay now pins those four scalar
owners, splits the void `get_path_nodes` call clobber away from the later
lead-count bound, and separately splits the genuine primary-sample-bank reload
used by the curved secondary-position offset. Readback keeps `get_path_nodes`
void, exposes `lead_count`, `tail_count`, `start_x`, `turn_sign`, and
`lead_count_bound` as scalars, and retains `primary_sample_bank` as a borrowed
`PathTemplateSample*` only for its real lifetime. No mobile layout or
Windows-only mesh-tail statement is transferred.

## 2026-07-30 terminal-delta array-owner bound

The exact terminal-delta helper shape also appears in the Twister family, so
the same one-site plan exhaustively tests direct arrays, separately scoped
pointer pairs, and separately scoped references. The two scoped forms compile
byte-identically to the retained source. Direct arrays lose 68.41 weighted
bytes and fall from 47.92% to **45.09%**, while moving the candidate from 635
to 641 instructions; the 15-instruction prefix and all 33 references remain
clean. Toad therefore retains its loop-wide pointer owners.

## 2026-07-30 secondary terminal-delta expression ownership

Keeping the proven loop-wide pointer owners while applying
`Vector3::operator-` only to the secondary delta adds 66.15 weighted bytes and
raises focused matching from 47.92% to **50.65%**. The candidate moves from
635 to 636 instructions against 663; prefix 15/663 and all 33 clean references
are unchanged. Applying the operator only to primary gains 51.01 bytes, while
applying it to both gains 47.37 bytes.

The source asymmetry is retained narrowly rather than generalized. Android and
iOS independently corroborate the two component subtractions but cannot expose
the inlined C++ spelling. On Windows, localized diffing shows the secondary
operator improves the delta-loop region itself: the former 37-instruction
mismatch splits into a better 32-instruction region and a 50%-matching tail.
Scoped and unscoped pointer forms emit the same bytes, while all three
direct-array/operator interactions repeat the prior 68.41-byte regression.

## 2026-07-30 orientation subtraction bound

The primary current/previous orientation operator loses 59.46 weighted bytes
and falls to 48.20%, while preserving the 15-instruction prefix and all 33
clean references. Toad keeps the expanded component constructor and the
independently retained secondary terminal-delta operator.

## 2026-07-30 mesh arithmetic ownership

Native `0x42d217..0x42d2ff` keeps the column-relative lateral value on the x87
stack across both vertex branches. Each branch materializes a lateral-offset
vector, and the terminal branch separately owns its raised endpoint and
generated position. Recovering the x87 owner as a `double` local adds 14.04
weighted bytes. The paired authored `Vector3::operator*` boundaries add 12.16,
and the terminal `Vector3::operator+` adds another 22.42; the ordinary add is
byte-neutral.

The retained result moves from 50.65% to **52.66%**:

```text
target: 663 insns, candidate: 632 insns
prefix: 15/663 target insns
masked operands: 33 ok, 0 unresolved, 0 mismatch
```

This is a 48.62 weighted-byte gain with four fewer candidate instructions.
The count gap grows, but the removed spill/reload instructions agree with the
native x87 lifetime, so the source correction is retained.

The surrounding native mesh and face schedule was then bounded explicitly:

- late branch-local vertex declarations, per-column sample ownership, and
  their interaction lose 26 to 32 weighted bytes;
- separate face records with complete branch-local UV writes lose 46 bytes,
  and adding both native parity branches loses 50;
- adding only the back-face parity branch gains 8.01 bytes, but the symmetric
  pair loses 57.05, so the unsupported one-sided metric result is rejected;
- removing the joined final V write gains 28.16 bytes only by omitting required
  UV state; the semantically complete two-branch form loses 50.46 and is
  rejected;
- sharing the lead/tail induction owner is byte-neutral, and six symmetric
  branch-scalar assignment orders are neutral or worse.

The current frontier therefore preserves complete face semantics and closes
the evidence-backed mesh, face, and initial stack-home neighborhoods.

## 2026-07-30 sample-index and secondary-offset ownership

Windows SSA shows that one logical index slot drives the lead samples and is
then reset for the 26-sample curve. Reusing that source owner, with an ordinary
function-scope `int i`, adds **127.02 weighted bytes** and raises focused
matching from 52.66% to **57.92%** without changing the 632/663 instruction
count, 15-instruction prefix, or 33 clean references.

The tail is a distinct boundary. Native arithmetic renders an equivalent
`index - lead_count - 26 < tail_count` condition, but spelling that expression
directly loses 137 weighted bytes and one prefix instruction. Closing the
lead/tail lifetime dependency reduces the loss to 46 bytes but remains
negative; including the curve owner does not change that result. The retained
tail counter and compiler-derived logical index therefore remain. Six scalar
declaration orders and the earlier six assignment orders are byte-neutral or
worse, so the remaining early stack-home rotation is not forced in source.

Native `0x42cfcf..0x42d01f` computes all three basis-up offsets before mutating
the copied secondary position. Materializing those three X/Y/Z scalar owners
adds another **2.65 weighted bytes**, yielding the retained **58.02%** result
at 633/663 instructions, prefix 15/663, and 33 clean references. Aggregate
vector and pointer-owner forms lose 59 to 79 bytes. Three reordered scalar
schedules gain 5.91 bytes only by emitting Z/Y/X instead of the native X/Y/Z
order and shortening the candidate to 631 instructions; that metric artifact
is recorded but rejected.

On the new baseline, scoped delta references are byte-identical, per-loop bank
pointers lose 62 bytes, and direct arrays lose 136. Swapping facequad/vertex
source declarations is byte-identical. Retesting the native-looking
per-column sample plus late vertex destination loses 11 bytes, while either
half alone loses 12 to 17. No delta or mesh owner change is retained.

## 2026-07-30 curved sample byte ownership

Windows `0x42ce5c..0x42d02e` and both mobile bodies preserve a logical
26-sample curve counter beside one advancing `0xa8` byte cursor initialized
from `lead_count`. Replacing the derived array index with that direct cursor
adds 3.73 weighted bytes without changing any structural metric:

```text
match: 58.18% (was 58.02%)
target: 663 insns, candidate: 633 insns
prefix: 15/663 target insns
masked operands: 33 ok, 0 unresolved, 0 mismatch, 0 unaudited
```

The source keeps direct base-plus-offset casts because they reproduce the
native repeated address graph. Materializing scoped primary, previous, and
secondary pointers instead expands the stack frame, falls to 39.00%, shortens
the candidate to 619 instructions, and leaves a one-instruction prefix.

The adjacent fixed loops are closed on the new frontier. Windows
`0x42cc97..0x42cd57` and `0x42cd69..0x42ce52` also contain logical and byte
owners, but explicit lead addressing loses 138.12 weighted bytes and two
prefix instructions. Tail addressing loses 37.89 bytes with the retained
tail counter; switching to the native-looking absolute relative-bound index
loses 121.73 bytes and one prefix instruction. Both lead/tail interactions
remain negative, so those cursors are treated as compiler-derived and only the
contributing curve owner is retained.

## 2026-07-30 post-cursor texture-parity bound

The native duplicated texture branches at `0x42d41b..0x42d434` and
`0x42d4cd..0x42d4ea` were replayed after the sample-index, secondary-offset,
and curved byte-cursor recoveries materially changed the enclosing allocation.
The exhaustive two-site sweep still rejects the dependency-closed pair.

The front branch alone loses 5.41 weighted bytes at 638/663 instructions. The
back branch alone gains 7.29 bytes at 640/663, but remains an unsupported
asymmetric half-transfer. Restoring both native branches loses 43.54 weighted
bytes and falls from **58.18%** to **56.38%** at 646/663 instructions. Prefix
remains 15/663 and all 33 references stay clean.

No parity branch is retained. This supersedes the earlier pre-cursor
measurement while reaching the same source conclusion: the current face
record schedule lacks a wider dependency needed to reproduce the authored
pair, and the metric-only back branch is not accepted on its own.

## 2026-07-30 delta physical-cursor transfer bound

Windows `0x42d034..0x42d107` carries a logical delta counter beside an
independent `0xa8` byte cursor, the same broad machine shape that contributed
in Snake. Replaying that ownership after Toad's curved byte cursor recovery
does not transfer. The guarded pointer-owner form loses **64.50 weighted
bytes** and reaches 55.51% at 634/663 instructions; the repeated direct-owner
form loses **139.28 bytes** and reaches 52.42% at 638/663.

Both variants preserve Toad's proven component-wise primary subtraction,
authored secondary `Vector3::operator-`, 15-instruction prefix, and all 33
clean references. The retained direct-index delta loop therefore remains at
**58.18%**, 633/663 instructions. Native dual induction is sufficient evidence
to test the source owner, but this negative transfer shows that Snake's cursor
win depends on its surrounding allocation rather than a family-wide spelling.

## 2026-07-31 native mesh-row and branch-scalar ownership

Native `0x42d1f2..0x42d322` carries a logical mesh row beside an independent
`0xa8` sample cursor. It enters through a nonnegative segment guard, enters
each column range through its own nonnegative guard, and advances both owners
after the post-tested column loop. Replaying that complete control unit while
preserving Toad's proven double lateral value and vector operators adds
**45.17 weighted bytes** and grows the candidate from 633 to 636 instructions.
Reverting only the row owner loses the same 45.17 bytes, with no prefix or
reference tradeoff.

That global-allocation change makes the previously neutral branch-assignment
order material. Native's true arm at `0x42cc1d..0x42cc31` writes `start_x`,
`turn_sign`, `lead_count`, then `tail_count`; the current Binary Ninja replay
independently renders that same order. Retaining it adds another **14.90
weighted bytes** and extends the exact prefix from 15 to 16 instructions.
Six declaration orders remain byte-identical, so only the instruction-backed
assignment schedule is retained.

Together the two owners move Toad from **58.18% to 60.66%**:

```text
target: 663 insns, candidate: 636 insns
prefix: 16/663 target insns
masked operands: 33 ok, 0 unresolved, 0 mismatch, 0 unaudited
```

The adjacent mesh frontier is bounded on the resulting allocation. Swapping
facequad and vertex acquisition or adding an explicit mesh-object owner is
byte-identical. Eight terminal-endpoint materializations all regress; the
closest default-construction form loses 2.23 weighted bytes. Replaying the
complete positive-guarded, post-tested face-loop control shortens the
candidate by one instruction but loses 2.61 weighted bytes. These owners are
not retained.

Three dependency-closed tail replays were also rejected before this
milestone: a shared absolute index with the native positive guard reached
52.40%, a guarded local counter plus explicit `0xa8` cursor reached 57.72%,
and a guarded absolute index plus cursor reached 52.60%. The remaining
turn-sign stack-home difference therefore is not evidence for transferring
any of those incomplete tail spellings.

## 2026-07-31 post-row texture-parity recovery

The native duplicated texture branches at `0x42d41b..0x42d434` and
`0x42d4cd..0x42d4ea` were replayed again after the mesh-row owner and
branch-assignment schedule changed the enclosing allocation. Unlike the
post-cursor result, all three variants now improve: the front branch adds
12.10 weighted bytes, the back branch adds 5.82, and the complete symmetric
pair adds **18.94**.

The retained pair raises Toad from 60.66% to **61.44%**:

```text
target: 663 insns, candidate: 652 insns
prefix: 16/663 target insns
masked operands: 33 ok, 0 unresolved, 0 mismatch, 0 unaudited
```

The candidate grows by 16 instructions, closing most of the previous
27-instruction count deficit without a prefix or reference tradeoff. The
tracked source hash exactly matches the recorded winning overlay. This
supersedes the earlier negative parity bound: the native pair depends on the
recovered mesh-row lifetime and is now retained as a complete authored
control unit.

## 2026-07-31 face-record and curve-position ownership

With the parity pair present, the target's two branch-local face records and
complete branch-local UV writes become a major contributing dependency.
Keeping the old index expression adds 35.31 weighted bytes and reaches 62.90%,
but recovering the target's
`face_index + 2 * (row * width_cells + column)` association adds **95.93
weighted bytes** and extends the exact prefix from 16 to 89 instructions.

The retained face unit raises Toad from 61.44% to **65.41%** at 664/663
instructions, prefix 89/663, and 33 clean references. The tracked source hash
exactly matches the recorded winner. A fresh UV-only sweep confirms why the
whole dependency matters: moving both final V writes into their branches
without the face owners loses 16.28 bytes, while deleting the required joined
write gains 5.96 bytes only by omitting state and is rejected.

The target also carries one secondary-position pointer across the curve's
three offset additions. Recovering that scoped owner adds another **8.44
weighted bytes**, reaching the retained **65.76%** result:

```text
target: 663 insns, candidate: 660 insns
prefix: 89/663 target insns
masked operands: 33 ok, 0 unresolved, 0 mismatch, 0 unaudited
```

The pointer shortens the candidate by four instructions and moves its count
three below the target, but the removed repeated address formation agrees
with native `secondary_position` ownership. The source hash again exactly
matches the recorded overlay, so the evidence-backed owner is retained
despite the instruction-count warning.

## 2026-07-31 post-face frontier bounds

The 89-instruction prefix ends at the positive tail guard. That made the
native-looking absolute-index control worth replaying on the new allocation,
but the complete family remains negative:

- local absolute bounds lose 175 to 292 weighted bytes and collapse the
  prefix to 13 or 14 instructions;
- sharing the recovered function-scope `i` loses 175 to 254 bytes with the
  same prefix collapse;
- the guarded post-tested absolute-index unit loses 267 bytes;
- explicit tail cursors lose 33 to 125 bytes, and the lead cursor loses 131.

The current local tail counter therefore remains. Swapping to the native
facequad-before-vertex declaration order loses 95 bytes, while adding an
object owner in the existing order is byte-neutral. Both parity predicate
orientations are byte-neutral at both face sites.

Finally, the explicit delta cursor now raises aggregate matching by 78.93
bytes to 69.02%, but moves the first mismatch from target offset `0x173` back
to `0xa1`, cuts the exact prefix from 89 to 38 instructions, grows the
candidate from 660 to 667 instructions, and therefore carries three canonical
tradeoffs. Passing the recovered caller index into the inlined delta helper is
byte-neutral and leaves that cursor result unchanged; the scoped-pointer
cursor loses 4.86 bytes. The direct-cursor score is recorded but rejected
until a source-backed dependency can preserve the proven prefix.

## 2026-07-31 dependency-complete cursor interaction bound

The fixed lead and tail cursors were previously replayed only as single-site
changes after the face-record recovery. A complete 23-variant sweep now covers
every one-, two-, and three-site interaction among the lead cursor, three tail
cursor/control shapes, and both delta cursor shapes.

No interaction preserves the proven frontier. The exact guarded tail replay
with the native absolute logical index and independent `0xa8` byte cursor
loses **199.68 weighted bytes** and collapses the exact prefix from 89 to 14
instructions. Adding it to the direct delta cursor still loses 62.14 bytes
against the retained source. The closest complete fixed-loop interaction uses
the local tail counter: lead plus tail plus the direct delta cursor gains only
**12.10 weighted bytes**, but moves the first mismatch from target offset
`0x173` to `0x26` and cuts the prefix from 89 to 13 instructions.

The delta cursor alone remains the sweep's aggregate-score leader at the
already-recorded 69.02% tradeoff result; every added fixed-loop owner reduces
that score. No cursor interaction is retained. This closes the Toad
lead/tail/delta ownership dependency on the current face and curve allocation.
