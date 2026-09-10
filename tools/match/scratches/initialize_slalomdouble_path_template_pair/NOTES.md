# initialize_slalomdouble_path_template_pair

Current recovery: semantic-complete (`analysis` residual). The 2026-09-11
source recovery reaches **99.7072%**, with **683/683 instructions** and **45
clean references at identical instruction and byte positions**. Both formerly
unaudited first-curve calls are resolved. It is still a partial match:
`body_byte_exact` is false.

The fixed 70-sample body retains four samples at each end and 62 curve
samples. Phase-local physical cursors, bank-reference initialization helpers,
branch-local mesh vectors, and the lead-in Z conversion schedule recover all
but one departure-loop receiver setup. Native code copies the sample offset
into ECX early and adds the secondary bank later; the candidate loads the bank
into ECX and adds the offset. The remaining two normalized instructions differ.

See [the recovery report](../../slalomdouble-source-recovery-20260911.md) and
its replayable source/reference receipt. The notes below are historical;
their earlier scores and reference residuals are superseded by this result.

Honest starter scratch for `initialize_slalomdouble_path_template_pair @ 0x425050`.

The constructor callsite uses the same six-argument stack shape as the slalom
family and the native epilogue is `ret 0x18`. The runtime kind written by this
public constructor is `0x20`, matching the current decompile. The scratch builds
the fixed 70-sample double-slalom body with four straight samples at each end,
sinusoidal lateral motion, raised Y motion, orientation, deltas, strip mesh, and
`calc_path_length_z`.

Residuals are expected. This is a semantic starter, not a tuned byte match.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 10.59% (129/683
candidate/target instructions) to 22.28% (574/683), with masked operands
improving from 12 ok, 0 unresolved, 5 mismatch to 31 ok, 0 unresolved, 1
mismatch.

2026-07-03 falloff shape: split the double-slalom center falloff into the two
native absolute-distance temporaries before the sine/scale multiply. Focused
Wibo moves from 22.28% (574/683) to 22.66% (588/683), with masked operands
improving from 31 ok, 0 unresolved, 1 mismatch to 32 ok, 0 unresolved, 1
mismatch.

2026-07-03 orientation guard: native source shape always dispatches the previous
sample through `rotate_matrix_world_z(roll_angle)` after the up/cross-vector
orientation frame. Removing the zero-roll guard moves focused Wibo from 22.66%
(588/683) to 22.84% (578/683), with masked operands unchanged at 32 ok,
0 unresolved, 1 mismatch.

2026-07-03 fixed-sample initializer spelling: reload primary and secondary X
from the stored primary `center_x` field, then delay the integer-to-float Z
conversion until inside the inlined sample initializer after the primary
identity call. Focused Wibo moves from 22.84% (578/683) to 23.14% (570/683);
the masked audit keeps the same single call mismatch but has one fewer audited
ok (31 ok, 0 unresolved, 1 mismatch).

Rejected: spelling the fixed trailing straight samples with `lead_out_start =
66` and `total_segments = lead_out_start + 4` regressed focused Wibo to 22.61%
(582/683) and worsened the masked audit to 30 ok, 0 unresolved, 2 mismatch, so
the fixed `70` / `66` constants stay in the scratch.

2026-07-03 retained mesh-face loop: replacing the direct `a`/`b` face writes
with the two-iteration `face_index` loop moves focused Wibo from 23.14% (570/683)
to 26.92% (580/683). Masked operands change from 31 ok, 0 unresolved,
1 mismatch to 32 ok, 0 unresolved, 3 mismatch; the extra residuals are in the
interior orientation call pairings.

Rejected: the `slalom` orientation scheduling split does not transfer here.
Expanding both lane orientations before either roll call reduced masked
residuals from 32 ok, 0 unresolved, 3 mismatch to 30 ok, 0 unresolved,
1 mismatch, but regressed focused Wibo from 26.92% (580/683) to 25.08%
(577/683). The compact helper calls stay as the better current score baseline.

2026-07-04 fixed-loop expansion retest rejected: expanding the four lead-in
fixed samples from `initialize_pair_sample` compiled to the same focused Wibo
result as the retained helper loop: 26.92% (580/683), with masked operands
unchanged at 32 ok, 0 unresolved, 3 mismatch. Expanding only the four trailing
fixed samples was also binary-neutral at the same score and audit. Keep both
fixed loops in the compact helper form until a broader register-ownership
change gives the expansion a different alignment context.

2026-07-04 mesh request-order probe rejected: swapping strip-mesh requests to
facequads-before-vertices regressed focused Wibo from 26.92% (580/683) to
26.13% (580/683). Masked operands worsened from 32 ok, 0 unresolved,
3 mismatch to 30 ok, 0 unresolved, 5 mismatch, adding explicit vertices vs
facequads allocation call pairings alongside the existing orientation residuals.
The helper keeps vertices-first order.

2026-07-13 terminal ownership: removing the `last_primary` and
`last_secondary` pointer aliases while retaining the constructor-specific
delta loop moves focused Wibo from 26.92% (580/683) to 29.90% (588/683).
The masked audit remains 32 ok, 0 unresolved, 3 mismatch; all three residuals
are the pre-existing interior orientation pairings. The terminal stores belong
directly to the two count-relative `Path` sample arrays.

2026-07-15 curved-body ownership: the native double-slalom keeps a zero-based
logical curve counter separate from its sample cursor. Its sample constructor
also owns the primary field stores and identity before calling `cosine` for Y,
then initializes the secondary transform from the written primary position.
Recovering those lifetimes and computing both delta streams directly in the
`Path` owner moves the retained focused result through 29.96% and 32.89%.
Splitting terminal and ordinary vertex rows then reaches 33.05%; expanding the
curved initializer in its target call order reaches 33.31%.

2026-07-15 orientation ownership: unlike the single outer guard used by the
related Slalom source, this target has an independent guard for each lane. Each
non-initial lane builds and normalizes its own frame, performs its cross, and
only then derives the roll from the primary previous sample. The secondary
lane recomputes that primary-owned roll after completing its own cross. This
source order supersedes the older grouped-frame rejection above, reaches
33.98% (606/683), and clears all three call residuals for 33 ok, 0 unresolved,
0 mismatch. The face header is now cleared through the shared 16-bit
`header_word` owner; that field clarification is codegen-neutral.

Rejected in the current context: forcing the four trailing fixed samples into
an explicit subtract-bound `do/while` regressed 30.03% (589/683) to 29.80%
(599/683), and rewriting the already post-tested face-column loop explicitly
regressed 33.05% (606/683) to 32.27%. Neither changed the operand audit, so the
smaller equivalent loop spellings remain instead of tuning control flow.

2026-07-17 live owner-ABI closure: the native tail is `retn 0x18`, the iOS
counterpart is `cRPath::BuildSlalomDouble(int, int, bool, char*, char*)`, and
the Windows caller supplies the additional final cap-texture argument. Binary
Ninja's stale view returned `int32_t`, owned a `PathTemplate*`, and exposed only
three stack parameters; a user-authored `char*` survived at `+0x10`, `+0x14`
was merely automatic, and the final `+0x18` slot was absent. The guarded
recreation now owns the exact void `Path*` contract and all six stack arguments.
Post-restart readback confirms authored parameter storages `+4..+24`. This is
analysis-only: focused Wibo remains 33.98% (606/683), with 33 clean masked
operands and no unresolved or mismatched operands.

2026-07-20 live lifetime closure: transactional MLIL preview recovers the
preceding primary/secondary forward vectors, both current-sample reloads, both
terminal deltas, the current mesh sample, and the complete facequad record
reused by the native two-variant mesh branch. All eight owners render direct
`Vec3`, `PathTemplateSample`, or `ObjectFaceQuad` fields without introducing an
`__offset` expression. The earlier sample and rotation cursors and the
previous-row mesh cursor remain automatic because typing their byte-relative
addresses did not improve ownership. This is analysis-only: focused Wibo
remains 33.98% (606/683), with 33 clean masked operands and no unresolved or
mismatched operands.

## 2026-07-26 shared-face UV completion

The double-slalom face builder also computes one cursor before its winding
branch and completes each record inside the selected arm. Native stores at
`0x425940` and `0x4259e6` prove that both arms own `face->uv[3].v`.
Recovering those writes raises focused matching from 33.98% to 36.41%, grows
the candidate from 606 to 608 instructions, and expands the clean operand audit
from 33 to 35 with no unresolved or mismatched operands.

## 2026-07-26 complete mesh-vector ownership

Raw native instructions at `0x425704..0x4257e1` prove that Double Slalom shares
the slalom family's five-value vertex graph. Ordinary rows own a lateral offset
and generated position. The terminal row separately owns a lateral offset,
raised endpoint, and generated position, then materializes its destination
vertex. The face builder remains one shared record, as independently proved by
the UV completion above.

Recovering the complete graph raises focused matching from 36.41% to **39.22%**
and grows the candidate from 608 to **643/683** instructions. It recovers the
exact native `0x54` frame and a five-instruction exact prefix. The masked audit
remains clean at 34 accepted, 0 unresolved, and 0 mismatched operands.

## 2026-07-27 paired-mobile ownership refinement

The exact Android and iOS
`cRPath::BuildSlalomDouble(int, int, bool, char*, char*)` symbols prove the
boolean ABI. Their paired bodies branch on the logical curve induction owner
at zero in each lane, so both derived `i <= 4` guards are now independently
spelled `curve_index == 0`. This raises focused matching from **39.22%** to
**39.55%** and shrinks the candidate from 643 to **642/683** instructions,
while preserving the five-instruction exact prefix. The masked audit has 40
accepted and 10 unaudited operands with no unresolved or mismatched operands.

Both mobile bodies stop after sample/delta construction and `CalcLengthZ`;
Windows owns the cap-texture and mesh-building tail. Binary Ninja preview,
apply, readback, and lifetime replay kept every recovered owner current.

The exact body pair also corrects the shared enum identity. Windows writes kind
`0x20`, while Android and iOS write their platform-specific SlalomDouble kind
`0x28`. The stale Windows label `DIP` came from this function's superseded
pre-mobile name; the canonical label is now
`PATH_TEMPLATE_KIND_SLALOMDOUBLE`. This ownership change is analysis-only and
does not alter the accepted 39.55% matcher source.

## 2026-07-28 complete control and mesh lifetime replay

The paired Android and iOS bodies independently preserve the four-sample lead
and tail loops, the 62-sample curve induction, and its phase and folded-distance
graph. Exact Windows MLIL definitions split those logical owners without
transferring mobile addresses. Windows-only instructions separately prove the
mesh, UV, face-pass, and ECX/EDX width-reload lifetimes.

One batched preview/apply/readback transaction verified 23 split-lifetime groups
plus two bounded stack scalars. An idempotent live replay completed in 17.14
seconds with every owner already current. A strict paired Binary Ninja/IDA
export reported zero lane mismatches and 1,142/1,142 passing health checks.

This is analysis-only. Focused matching remains **39.55%** at **642/683**
instructions with a five-instruction exact prefix, 40 accepted operands, 10
unaudited operands, and no unresolved or mismatched operands. No matcher source
was changed.

## 2026-07-30 x87 compare-reference alignment

The compare-family audit now pairs the two ordered same-width
`fcom`/`fcomp` zero-constant reads while refusing to pair compare operations
with ordinary loads. This is proof-only: focused matching remains 39.55%,
642/683 instructions, and prefix 5/683. The current receipt has 44 clean plus
2 unaudited entries, down from 42 clean plus 6 unaudited, with no unresolved
or mismatched references.

## 2026-07-30 lane-local identity-call schedule bound

As in SlalomBig, the final two audit entries are an unpaired native/candidate
`set_matrix_rotation_identity` call. Native places both first-curve lane calls
adjacent. The paired mobile bodies preserve lane-local logical
`curve_index == 0` guards, and the retained Windows source follows that owner
graph.

Six sweeps cover pair-level zero/nonzero and sample-index guards, a shared
boolean/integer predicate, equivalent lane-local condition spellings,
branch-free non-first helpers, and the sibling guarded-lane helper. Moving the
branch outside both lanes audits all 45 references but reaches at most 31.70%,
far below the retained 39.55%. Helper factoring is either byte-identical or
regresses as low as 37.29%.

One asymmetric legacy spelling, changing only the primary guard to `i <= 4`,
raises the score by five weighted bytes to 39.73%. It also removes one
candidate instruction, leaves both references unaudited, and conflicts with
the independently proven paired-mobile logical owner. This metric-only
tradeoff is recorded but not retained.

The ledger contains 40 variants. The honest frontier remains 39.55%, 642/683
instructions, prefix 5/683, with 44 audited and two unaudited references.

## 2026-07-30 authored terminal-delta subtraction

The Slalom family recovery proves the same paired `Vector3::operator-` boundary
in this constructor. The exhaustive two-site sweep adds 7.66 weighted bytes
and raises focused matching from 39.55% to **39.85%**. Candidate and target
counts remain 642/683, prefix stays 5/683, and the receipt remains 44 clean
plus 2 unaudited references. Both single-site forms improve by half as much.

## 2026-07-30 orientation subtraction bound

The paired inline primary and secondary orientation expressions were tested
alone and together. All three authored-operator variants are byte-identical,
so the retained frontier remains **39.85%**, 642/683 instructions, prefix
5/683, with 44 clean and 2 unaudited references.

## 2026-07-30 mesh arithmetic ownership

Native instructions at `0x425704..0x4257e1` preserve one x87 lateral value
across the already-recovered five-vector branch graph. `double lateral` gains
3.06 weighted bytes, and the ordinary `Vector3::operator+` gains 3.84. The
terminal addition initially loses 2.31, so it is not transferred prematurely.

Both `Vector3::operator*` expressions then improve independently and gain 23.04
weighted bytes together. On that recovered scale baseline, the terminal
addition changes from a regression to a 7.68-byte gain and is retained.

The complete interaction raises focused matching from 39.85% (642/683) to
**41.33%** (638/683), a total gain of 37.62 weighted bytes. The
five-instruction prefix and the 44 clean plus 2 unaudited reference receipt
remain unchanged. The four-instruction shortening is confined to the directly
proven native arithmetic owners.

## 2026-07-30 sample-array ownership bound

The native fixed and curved sample constructors repeatedly reload both arrays
from the `Path` owner, so the four-sample lead, four-sample departure, and
62-sample curve initializer were expanded into direct indexed ownership. An
exhaustive seven-variant sweep tests every isolated and combined phase.

None improves the retained compilation context. The best combination,
departure plus curve, loses 4 weighted bytes; the other forms lose 12–44.
Matching remains **41.33%**, 638/683 instructions, prefix 5/683, with 44 clean
plus 2 unaudited references. The target's array reloads therefore need a
broader register-lifetime recovery, not another local pointer-to-index rewrite.

## 2026-07-30 shared-orientation closure bound

The later Slalom and SlalomBig recoveries showed that sample-array rewrites can
depend on replacing both lane-local orientation guards and pointer owners with
one shared first-curve branch. SlalomDouble was therefore re-evaluated on that
broader native-backed boundary rather than inheriting the sibling win.

Shared direct orientation alone resolves the final two unaudited calls and
moves the candidate from 638 to 653/683 instructions, but loses 65 weighted
bytes and falls to **38.77%**. From that new baseline, the existing three-phase
sample-owner sweep exhaustively retests all seven lead/departure/curve
combinations. The best, direct departure plus direct curve initialization,
recovers 24 weighted bytes to **39.70%**; the complete three-phase transfer
reaches only **38.14%** at 675/683 instructions.

No closure variant exceeds the retained **41.33%** frontier, and none extends
the five-instruction prefix. The original lane-local pointer owners therefore
remain in source with 44 clean plus 2 explicitly unaudited references. This
bounds the family transfer: SlalomDouble's fixed-count prologue and curved
height calculation create a different VC6 register schedule even though the
native semantic array graph is homologous.

## 2026-07-30 checkerboard texture control

Native instructions at `0x4258fd..0x425916` and `0x42599c..0x4259bc`
independently preserve the same odd-parity branch around each texture lookup
that is visible throughout the authored strip-mesh constructor family. Both
arms deliberately request the same texture; the control flow is nevertheless
part of the original VC6 compilation and is not reduced to one call.

The exhaustive two-site sweep tests each branch alone and the pair. The first
branch alone gains 25.84 weighted bytes at 644/683 instructions. The second
alone loses 37.62 bytes at 642/683. Restoring both together exposes the
interaction and gains **266.49 weighted bytes**, raising focused matching from
**41.33%** to **51.84%** at **648/683** instructions. Prefix remains 5/683 and
the reference receipt remains 44 clean plus 2 explicitly unaudited entries.
The exact native-backed pair is retained.

## 2026-07-30 post-checkerboard sample ownership

The checkerboard recovery materially changed the VC6 register schedule, so the
previously negative three-phase sample-owner sweep was replayed rather than
treated as a permanent family bound. The new interaction is decisive: direct
indexed ownership for the four lead samples, four departure samples, and all
62 curved samples together gains **120.65 weighted bytes** and expands the
candidate from 648 to **681/683** instructions. Focused matching rises from
**51.84%** to **56.60%**. The five-instruction prefix and the 44 clean plus 2
explicitly unaudited references remain unchanged.

No partial transfer explains the full gain. Lead plus curve reaches 54.97%,
departure plus curve 54.28%, lead plus departure 54.18%, and lead alone
52.46%; departure alone is nearly neutral at 51.75%, while curve alone falls
to 45.15%. The exhaustive seven-variant receipt therefore justifies retaining
all three direct phases as one compilation-context recovery.

Native instructions at `0x425091..0x425510` were then used to bound the next
owner hypotheses. Explicit byte cursors for the fixed lead and departure loops
lose 59 and 126 weighted bytes respectively, and lose 150 together. Rewriting
the departure guard as `i - 66 < 4`, `<= 3`, or `!= 4` loses 142–146 weighted
bytes. A whole curved-loop byte cursor falls slightly to **56.43%** at 678/683
instructions, and an explicit shared floating zero owner is byte-identical.
The sample-index guard alternatives also fall to 46.71% and 45.37%. These
bounds leave the compact direct-indexed source as the honest frontier rather
than forcing target register names through artificial cursor lifetimes.

## 2026-07-30 terminal-delta cursor bound

The terminal-delta block at `0x425516..0x4255e9` independently confirms the
same logical-plus-physical ownership recovered in the related constructors.
Native zeroes the logical counter in EBP before its positive guard, zeroes the
byte cursor in EDI only on entry, advances them by one and `0xa8`, and tests
the logical counter against a reloaded `segment_count - 1`.

The current direct-indexed guarded `do/while` already compiles to that exact
two-induction shape. Making the byte owner explicit inside the guard, moving
its initialization before the guard, and reversing pointer-addition order are
all byte-identical at **56.60%**, 681/683 instructions, prefix 5/683, with 44
clean plus 2 explicitly unaudited references. Materializing scoped current and
next sample pointers loses 86.24 weighted bytes and falls to **53.20%**.

This closes the remaining local delta spelling without retaining redundant
source machinery. The persistent EBX-zero/EDI-cursor role used by native is a
whole-constructor allocation difference: the candidate uses the opposite two
registers from its prologue through all sample phases. Local cursor spelling
cannot resolve that swap, so no register-forcing or synthetic dependency is
introduced.

## 2026-07-31 direct face-offset record ownership

The face loop's single pointer is replaced by a semantic integer offset and
direct array-record writes. Focused matching rises from **56.60%** to
**57.50%**, and candidate size moves from 681 to 684 instructions against the
683-instruction target. Prefix remains 5/683; the existing 44 clean and two
unaudited references are unchanged. The gain is isolated to normal source
ownership and does not attempt to force the constructor-wide register swap.

## 2026-07-31 direct vertex-index ownership

Hoisting the common mesh-vertex index above the ordinary/terminal branch adds
9.57 weighted bytes and raises focused matching from **57.50%** to **57.88%**.
It also closes the instruction-count residual from 684 to **682/683** while
preserving prefix 5/683 and the existing 44 clean plus two explicitly
unaudited references.

This is the only other positive member of the broader direct-index probe
besides P. The retained integer owner expresses the shared array address
without introducing a byte cursor or register-forcing dependency.

## 2026-07-31 post-vertex sample interaction bound

Extending one current-sample pointer across both mesh branches adds 15.49
weighted bytes and reaches **58.49%**, but shortens the candidate from 682 to
678 instructions against 683 native. Windows instead forms the current or
preceding address inside each branch at `0x425711` and `0x425766`; naming the
shared array base while retaining those branch-local records is byte-neutral.

The count-tradeoff form also depends on the newly retained direct vertex
index. Pairing its shared sample with the old branch-local vertex pointers
falls to **54.07%** at 682/683 instructions. Direct sample records fall to
53.08%, and swapping vertex/facequad acquisition is byte-neutral. The current
57.88%, 682/683 source remains the best dependency-complete, instruction-backed
frontier.

## 2026-07-31 post-owner shared-orientation replay

The shared-orientation closure was replayed after the checkerboard pair, all
three direct sample phases, direct face offset, and direct vertex index had
materially changed the constructor's register schedule. This tests the same
kind of dependency cascade that unlocked the related Snake constructor rather
than treating the earlier 41.33% context as permanent.

The cascade does change the old result, but it does not reverse it. A shared
logical first-curve branch with direct indexed orientation closes both
remaining call references and reaches **51.38%** at 691/683 instructions,
well below the retained **57.88%** at 682/683. Spelling the shared guard from
the native physical sample boundary as `i <= 4` improves that alternative to
**53.09%**, 692/683, and extends the exact prefix from five to six
instructions, but still loses 121 weighted bytes against the retained source.

Reversing the physical predicate to put the non-first orientation on the
fallthrough path emits the target's `cmp offset, 0x2a0; jle identity` control
shape, yet falls further to **44.22%** at the same 692/683 instructions. All
three shared forms audit 45 clean references with no residuals. The two
lane-local call residuals are therefore an explicit proof tradeoff, not enough
reason to replace the substantially closer lane-local owner graph.

## 2026-09-05 terminal vector family replay

The complete terminal-position expression raises the current shared-header
baseline from **57.88% to 58.08%**, with 684/683 candidate/native
instructions and prefix 5. Reference audit: 44 ok, 0 unresolved, 0 mismatch, 2 unaudited.

The retained endpoint is previous position + Vector3(0,0,1), followed by
the existing lateral offset. This recovers the native aggregate temporary
lifetime without changing shared vector definitions or reference rules. The full
function remains partial; earlier percentages above belong to prior source
or dependency epochs. Existing reference debt, where present, is unchanged.
