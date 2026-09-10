# initialize_turnoverdouble_path_template_pair

Current recovery: declared semantic-complete, with native differences still under
analysis. This is a partial recovery, not an exact match or a compiler ceiling.

2026-09-11 current measurement: **75.72% → 94.27%**,
683 → 682 candidate instructions / 680 native, with a
80-instruction exact prefix. All 46 aligned references are clean;
only 8 share the native instruction index and 8 share the byte
offset. `body_byte_exact` is false. Compiler, flags, shared headers, ABI, and
matcher rules are unchanged.

The retained source uses branch-local mesh vectors, separate UV dispatch, one curve counter, nested roll sine evaluation, an aggregate secondary offset, and physical delta traversal.

The native departure bound still differs: the candidate derives a separate loop counter. Curve preheader and scalar-store scheduling also remain different.

The [recovery report](../../path-builder-source-recovery-20260911.md) and
[complete receipt](../../path-builder-source-recovery-20260911.json) contain the
before/after sources, identities, remaining assembly diff, reference positions,
and compared/excluded ranges. The promotion is recorded in `experiments.jsonl`.
Earlier observations below remain historical; finite controls do not establish
source exhaustion.

Ownership recovery for `initialize_turnoverdouble_path_template_pair @ 0x427640`.

This target uses the same six-argument stack shape as turnover (`ret 0x18`),
but the interior curve performs a double roll and returns to the same lateral
side. The retained scratch scores 51.70% (616/680 candidate/target
instructions), with 43 masked operands clean, 0 unresolved, and 0 mismatch.
It owns the straight sample seeds, folded double-roll construction, transform
propagation, and 16-bit face header. The main remaining structural debt is the
target's 0x50 stack frame and native mesh/delta loop layout; the retained
candidate uses a 0x2c frame.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 9.81% (176/680
candidate/target instructions) to 23.98% (571/680), with masked operands
improving from 14 ok, 0 unresolved, 7 mismatch to 32 ok, 0 unresolved, 1
mismatch.

2026-07-03 rejected seed-X reload: applying turnover's secondary-X reload from
the primary center field reduces focused Wibo to 23.68% (570/680), so this
sibling keeps the original argument-based seed helper spelling.

2026-07-03 retained mesh-face loop: replacing the direct `a`/`b` face writes
with the two-iteration `face_index` loop moves focused Wibo from 23.98% (571/680)
to 27.60% (581/680). Masked operands improve from 32 ok, 0 unresolved,
1 mismatch to 34 ok, 0 unresolved, 1 mismatch; the remaining mismatch is still
the sine/cosine pairing in the curved interior.

2026-07-04 cosine-center probe rejected: replacing the center-X expression
`sine(slalom_angle + 1.5707964f) * left` with the semantic equivalent
`cosine(slalom_angle) * left` regressed focused Wibo from 27.60% (581/680) to
25.76% (578/680). Masked operands worsened from 34 ok, 0 unresolved,
1 mismatch to 31 ok, 0 unresolved, 2 mismatch, adding a target `sine` vs
candidate `cosine` pairing before the existing target `cosine` vs candidate
`sine` residual. Keep the phase-shifted sine spelling until the surrounding
curved-call schedule changes.

2026-07-13 terminal ownership: as in `turnover`, the delta loop retains its
local sample pointers, while the two terminal writes belong directly to the
`Path` sample arrays. Replacing `last_primary` and `last_secondary` pointer
aliases with direct count-relative array stores moves focused Wibo from 27.60%
(581/680) to 28.53% (589/680). The masked audit remains 34 ok, 0 unresolved,
1 mismatch; the sole residual is still the curved sine/cosine call pairing.

2026-07-15 sibling ownership cascade: replacing the helper-shaped six-sample
lead-in and two-sample lead-out with direct primary/secondary array ownership,
separate logical Z counters, and the target's do-loop bounds recovers the same
owner split as `turnover`. The floating curve count is retained, the incoming
`length` slot owns the derived double-roll radius, and the lateral curve center
loads the already-written first primary sample field.

The curved body now uses separate curve and sample indices, preserves the
native phase-shifted sine and folded roll angles, follows the target's trig call
schedule, constructs forward/right bases directly, and copies only the primary
transform before applying the secondary up-vector offset. Focused Wibo moves
from 28.53% (589/680) to 51.70% (616/680), and the prior sine/cosine audit
mismatch clears: all 43 masked operands resolve cleanly. The face loop now
clears `header_word`, matching the target's 16-bit store.

As with `turnover`, keep `compute_terminal_deltas` and the semantic strip-mesh
helper boundary until their native loop owners can be recovered together.
Target-shaped mesh transplants in the sibling recovered frame pressure but
reduced whole-function agreement, so this target does not repeat those
lower-signal rewrites.

## 2026-07-17 live constructor ABI closure

The restarted Binary Ninja session confirms the native `retn 0x18` contract:
`Path* self`, `float length`, integer width and side-exit mode, two surface
textures, and the Windows-only cap texture. This agrees with the portable iOS
`cRPath::BuildTurnoverDouble(float, int, bool, char*, char*)` prefix. The stale
database prototype stopped after two textures and mislabeled the final known
stack slot, leaving the cap texture absent.

Guarded recreation and post-write readback now report the exact seven-parameter
prototype with no pending operation. The refreshed caller passes all six stack
operands through `path_pairs[0x26].primary`, and the callee exposes `Path`
fields plus void finalizer flow. This is analysis-only: focused matching remains
51.70% (616/680) with 43 clean masked operands.

## 2026-07-20 live lifetime ownership

A guarded transaction proves nine complete live owners: the primary seed and
mesh samples, primary up vector, secondary position, both terminal deltas, mesh
vertex, and the two face records. Their fields now render directly through
`PathTemplateSample`, `Vec3`, and `ObjectFaceQuad`, with no `__offset`
expressions. A tenth candidate, the pre-biased curved-sample cursor, was
rejected because typing it created three backward `__offset` accesses. Focused
matching remains 51.70% (616/680) with 43 clean masked operands.

## 2026-07-26 mesh-vector ownership

Raw native assembly at `0x427ca8..0x427d76` confirms the same four aggregate
owners recovered in Turnover. Both vertex branches first own a lateral-offset
vector and then a generated position. The terminal branch reaches the previous
sample through the current row cursor and separately materializes an endpoint
whose Z lane is extended by `1.0f`.

Recovering that shared source shape changes focused matching from 51.70%
(616/680) to 50.79% (655/680), improves the masked audit from 43 to 44 clean
operands, and leaves no unresolved or mismatched masks. The candidate now has
the native `0x50` frame and a 15-instruction exact prefix; the prior scalar
writer used a `0x2c` frame and had no exact prefix. As in Turnover, the small
fuzzy regression is retained because the native owner graph, row cursor,
instruction count, frame, and prefix all move toward the target together.

## 2026-07-27 paired mobile boolean ownership

Exact Android and iOS symbols agree on
`cRPath::BuildTurnoverDouble(float, int, bool, char*, char*)`, proving
`bool side_exit` rather than an integer mode. Both portable bodies end at
`CalcLengthZ`; Windows keeps its additional cap texture and local mesh builder.
The shared declaration, replay tooling, and live Binary Ninja prototype now
encode that platform split. The scalar refinement is byte-neutral: focused
matching remains 50.79% (655/680), with a 15-instruction prefix and 46 clean
masked operands.

## 2026-07-28 paired-mobile control ownership

The exact Android and iOS bodies independently preserve the six-sample lead,
two-sample tail, curved body beginning at sample 6, separate curve/sample and
delta/sample cursors, count-derived radius, transform-only secondary copy, and
final `CalcLengthZ` traversal. They also distinguish the two-turn centerline
phase from the folded four-turn roll. Windows SSA independently proves the
corresponding native stack definitions: `curve_count`, `curve_count_f`, the
`curve_count + 8` total, logical indices, byte offsets, `curve_phase`, and
`roll_angle`. Binary Ninja inlines the phase expression in HLIL, but its MLIL
stack lifetime remains distinct. Mobile evidence supplies source shape only;
the Windows ABI, storage, and mesh tail remain authoritative and unchanged.

The guarded replay now persists those conflict-free lifetimes and is
idempotent on a second run. The refreshed Binary Ninja decompile renders the
surviving owners without `__offset` artifacts. IDA 9.4 also replaces the stale
tracked five-argument `PathTemplate*`/`int32_t` export with the recovered
seven-argument `Path*`/`void` Windows signature and current object/mesh types.
This analysis-only recovery leaves focused matching at 50.79% (655/680), with
a 15-instruction prefix and 46 clean masked operands.

## 2026-07-30 terminal-delta array-owner bound

The exact terminal-delta helper shape shared with Twister permits the same
exhaustive direct-array, scoped-pointer, and scoped-reference owner sweep. Both
scoped forms are byte-identical to the retained source. Direct arrays lose
236.54 weighted bytes and fall from 50.79% to **41.16%**, while moving the
candidate from 655 to 661 instructions; the 15-instruction prefix and all 46
references remain clean. TurnoverDouble therefore retains its loop-wide
pointer owners.

## 2026-07-30 terminal-delta expression bound

Preserving pointer ownership does not make the authored-operator transfer
viable here. Secondary-only `Vector3::operator-` loses 4.61 weighted bytes,
primary-only loses 19.33, and the paired form loses 23.93. Combining either or
both operators with direct arrays loses at least 214.54 bytes. The retained
50.79%, 655/680-instruction source therefore keeps both component constructors.

## 2026-07-30 authored orientation subtraction

The shared orientation helper's operator form is byte-identical, while the
inline primary expression adds 18.41 weighted bytes. The retained narrow edit
raises focused matching from 50.79% to **51.54%** with 655/680 instructions,
prefix 15/680, and all 46 references unchanged. The helper-plus-inline form
emits the same bytes, so the neutral helper edit is not retained.

## 2026-07-30 mesh arithmetic ownership

Native instructions at `0x427c8e..0x427d76` preserve the same x87 lateral
value and branch-local vector aggregates as Turnover. Recovering `double
lateral` raises focused matching by 13.93 weighted bytes. On that baseline,
the two scale operators initially lose 4.65 together, while the terminal
position addition gains 5.62 and the ordinary addition is byte-neutral.

The terminal addition changes the scale interaction materially: both
`Vector3::operator*` expressions together then gain another 24.89 weighted
bytes, compared with +10.88 for the terminal scale alone and -5.62 for the
ordinary scale alone. The native evidence supports symmetric lateral-offset
ownership, so the paired form is retained. Rechecking the ordinary position
addition in that final state remains byte-neutral and it is not retained.

Together the scalar owner, paired scales, and terminal addition raise focused
matching from 51.54% (655/680) to **53.34%** (651/680), a gain of 44.43
weighted bytes. The 15-instruction prefix and all 46 masked references remain
clean. Moving the shared vertex owner into the two native-looking branch-local
positions loses 14.98 weighted bytes, so that source lifetime remains rejected.

## 2026-07-30 fixed-tail index ownership

Windows SSA and both verified mobile bodies expose one logical tail sample
index plus its compiler-derived `0xa8` byte offset. The scratch instead carried
a redundant Z counter alongside the sample index. An exhaustive 11-variant
owner/control sweep recovers the common owner and identifies the
mobile-backed `segment_count` endpoint as the contributing control form.

The retained single-index source gains 27.87 weighted bytes, raises focused
matching from **53.34%** (651/680) to **54.48%** (649/680), and extends the
exact prefix from 15 to **54/680** instructions. All 46 masked references
remain clean. The candidate becomes two instructions shorter, but the logical
owner, endpoint, and much longer exact prefix all agree with the independent
native and mobile evidence.

Using the sample index for Z alone gains 15.48 weighted bytes without extending
the prefix; the relative two-sample predicate loses 3.69. The corresponding
seven-variant lead-index sweep is also bounded: the complete single-index form
is byte-identical, while changing only its control owner loses 74.72 weighted
bytes. The neutral lead spelling is not retained.

## 2026-07-30 curved secondary-offset ownership

Native instructions at `0x427a4e..0x427a96` materialize all three products of
the primary `basis_up` vector and `0.49000001f` before updating the copied
secondary position. Recovering the authored `Vector3 secondary_offset`
therefore replaces the prior lane-at-a-time multiply/add source.

The aggregate raises focused matching from **54.48%** (649/680) to **55.26%**
(652/680), a gain of 19.13 weighted bytes. The exact prefix remains 54/680 and
all 46 references remain clean.

The sibling's source-level destination owner is intentionally not forced.
Adding an explicit `secondary_position` pointer to the aggregate loses 55.14
weighted bytes from the retained result; the pointer-only form loses 89.29,
and the scalar-direct form loses 19.13. Binary Ninja's typed destination can
therefore be explained as a compiler-derived address in this dependency
context, while the aggregate value is the bounded source-level recovery.

## 2026-07-30 fixed-sample byte ownership bound

Windows `0x4276ab..0x427777` and `0x427784..0x427870` preserve separate
logical indices and `0xa8` byte offsets for the six-sample lead and two-sample
tail. The scratch already recovers the logical owners, so both address
transfers were tested independently.

Repeated direct byte ownership in the lead loses 24.15 weighted bytes whether
the existing two logical indices are kept or merged. Using the logical index
instead of the byte offset as loop control loses 123.65 bytes and cuts the
exact prefix from 54 to 6 instructions. Both dedicated and reused logical tail
indices with direct byte addressing are byte-identical; making the tail byte
offset control the loop loses 4.44 bytes.

TurnoverDouble therefore remains **55.26%**, 652/680 instructions, prefix
54/680, with all 46 references clean. Its native offsets are compiler-derived
from the retained logical source in this allocation context.

## 2026-07-30 curved and tail byte ownership

Windows initializes the curved-sample address to `0x3f0` at `0x42788e` and
advances it independently by `0xa8` at `0x427a77`. Recovering that owner adds
52.73 weighted bytes and raises focused matching from **55.26%** to
**57.40%**, with 651/680 instructions, prefix 54/680, and all 46 references
clean. All 24 nearby cursor initialization and advance spellings are
byte-identical.

The changed allocation context also unlocks the separately proved tail byte
cursor. Retaining logical `i < segment_count` control while addressing both
sample arrays through `tail_sample_offset` adds another 13.22 weighted bytes.
The final retained result is **57.94%**, 649/680 instructions, prefix 54/680,
with all 46 references clean. A dedicated logical tail index emits identical
bytes.

Making the tail byte offset own loop control scores 18.34 bytes above the
curve-only baseline, but is rejected: native `0x427860..0x427870` increments
and tests the logical index separately from the byte cursor. Rechecking the
lead on the final baseline also remains negative by 11.10 to 122.07 weighted
bytes, so no lead cursor is retained.

## 2026-07-30 post-cursor face-control bound

The duplicated checkerboard texture calls were isolated from face-record
ownership and retested after the curved and tail cursor recoveries. The first
branch alone loses 5.34 weighted bytes. The second alone gains 7.26 but grows
the candidate by seven instructions, so the unsupported asymmetric result is
rejected.

Restoring both native parity branches loses **46.76 weighted bytes** and falls
from **57.94% to 56.04%**, while growing the candidate from 649 to 662/680
instructions. The 54-instruction prefix and all 46 references remain clean.
Unlike the dependency-complete Sweep and Snake results, TurnoverDouble's
shared face owner does not support the paired control transfer; the retained
source therefore remains unchanged.

## 2026-07-30 native tail relative-base ownership

Windows `0x427784..0x427870` keeps the logical tail index and `0xa8` byte
cursor separate, but its two-sample predicate also materializes
`-6 - curve_count` before the loop and combines that base with the incremented
logical index. Reintroducing the relative expression inline had previously
lost on the typed-address baseline; after the independent tail cursor recovery,
the precomputed semantic owner becomes productive.

Retaining `tail_control_base = -6 - curve_segments` with
`i + tail_control_base < 2` gains **21.54 weighted bytes**, raising focused
matching from **57.94%** (649/680) to **58.81%** (653/680). The exact prefix
remains 54/680 and all 46 masked references remain clean. All 19 commuted,
inclusive, split-definition, and equivalent subtraction spellings are
byte-identical to the winner or worse; the direct inline predicate loses
28.10 bytes and collapses the prefix to 15.

The remaining native-looking explicit condition temporary was bounded rather
than retained. It recovers the stack-held base and end-of-loop add locally but
falls to 56.86%; combining it with all seven primary/secondary field-owner
clusters reaches at most 57.63%. An inline temporary reaches 57.51%. A shared
lead/tail Z owner is byte-neutral and only moves the mismatching float slot
from `esp+0x1c` to `esp+0x10`, not native `esp+0x20`. These results isolate
the residual as a wider allocation dependency rather than another safe tail
semantic change.

## 2026-07-30 post-tail face-control closure

The relative-tail recovery changed the enclosing allocation after the previous
checkerboard bound, so both parity sites were replayed on the current 58.81%
frontier. The second branch alone reaches **59.10%** but adds seven candidate
instructions; the first branch falls to 58.59%, and the evidence-consistent
pair falls to 56.91%. The one-sided metric gain therefore remains an
unsupported partial control transfer rather than a retained recovery.

Raw Windows instructions at `0x427e32..0x427f8e` also prove that each face arm
materializes its own record pointer. The complete sibling face-owner plan was
replayed to test that missing interaction. Branch-local records without parity
reach only **57.86%** at 668/680 instructions and shorten the exact prefix from
54 to 36; adding both parity branches falls to **54.19%** at 682/680 with an
18-instruction prefix. On the branch-local baseline, the best one-sided parity
form reaches 58.47%, still below the retained source, while the complete pair
again reaches 54.19%.

All variants preserve 46 clean references. TurnoverDouble therefore remains
**58.81%**, 653/680 instructions, prefix 54/680, with its shared face source.
The branch-local native addresses are a bounded VC6 scheduling residual on
this dependency graph, not justification for forcing a lower-quality source
lifetime.

## 2026-07-31 mesh, face, and fixed-sample dependency closure

The earlier face and terminal-mesh bounds were allocation-specific rather than
final. Replaying the complete Windows mesh-row unit first supplies the missing
dependency: a non-negative segment guard, a `0xa8` sample byte cursor, nested
post-tested row/column loops, ordinary-first branch order, branch-local sample
and vertex owners, and the terminal row's `sample[-1]` read. That unit raises
focused matching from **58.81% to 64.82%**, a gain of 148 rounded weighted
bytes, while preserving the 54-instruction prefix and all 46 clean references.

On the recovered row allocation, a default terminal endpoint adds five more
rounded weighted bytes. Its explicit generated-position component constructor
loses seven alone but gains four more when paired with that endpoint owner.
The retained combination reaches **65.18%** at 661/680 instructions.

The new allocation also reverses the old face result. A common logical
`face_offset` with direct indexed record writes adds 74 rounded weighted bytes,
reaching **68.20%**. It moves the first mismatch from target instruction 54 to
36, but also fixes the formerly wrong `esp+0x20` float home and is backed by
the native common offset. Restoring both checkerboard parity branches then
adds another 103 rounded weighted bytes as a pair and reaches **72.38%**.
Neither branch works alone: the first loses 40 and the second loses 12.

The target's branch-local record pointers remain compiler-derived. Replaying
them after both parity branches loses 287 rounded weighted bytes and falls to
60.72%; either single arm is slightly worse. Four face-offset expressions,
both parity polarities, and indexed versus named UV fields are byte-identical.
The direct indexed owner plus paired parity control is therefore the complete
retained face unit.

Finally, the face allocation makes the native six-sample lead byte owner
productive. One logical `lead_index` plus a `lead_sample_offset` controlled
against `6 * sizeof(AttachmentSample)` adds 49 rounded weighted bytes and
extends the exact prefix from 36 to 71 instructions. Ordering the tail as
logical increment, current secondary delta write, then byte-cursor advance
adds 14 more and extends the prefix to 80. Android independently exposes the
same precomputed next index and current-record delta. Reusing that logical
index through the fixed tail and curve is byte-identical and matches the
portable owner.

Both Windows and Android compute the fixed-tail byte offset directly from
`curve_segments + 6`. Recovering that expression adds another seven rounded
weighted bytes. The retained frontier is:

```text
match: 75.28%
target: 680 insns, candidate: 683 insns
prefix: 80/680 target insns
masked operands: 46 ok, 0 unresolved, 0 mismatch, 0 unaudited
```

The remaining `esp+0x1c` tail-base lifetime is bounded without artificial
volatility or address escapes. Declaration permutations, split definitions,
four algebraic base forms, six inline/absolute predicates, and an explicit
condition temporary are neutral or lose up to 74 rounded weighted bytes.
Direct terminal-delta arrays lose 203; explicit logical-plus-byte delta
control loses nine; guarded logical control and scoped pointer/reference or
bank owners are byte-identical; both subtraction operators remain negative.
All 24 curve-cursor initialization/advance combinations are also identical.

The checked ledger now contains 54 records and 280 unique variants with no
malformed entries. The last three sweeps do not improve the retained result,
closing the current evidence-backed TurnoverDouble neighborhood.
