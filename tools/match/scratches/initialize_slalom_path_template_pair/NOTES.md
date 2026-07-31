# `initialize_slalom_path_template_pair` starter

This is an honest semantic starter for the path-template initializer at
`0x41f760`.

It models the slalom setup with four flat entrance samples, four flat exit
samples, the recovered sine lateral displacement with squared center falloff,
roll from previous center-X, delta vectors, strip mesh construction, and
finalization.

The source is intentionally a low/partial starting point. Residuals are expected
around VC6 register allocation and mesh-loop scheduling.

2026-07-03 ABI cleanup: the constructor callsite passes six stack arguments and
the native tail is `ret 0x18`. Updating the scratch and shared declaration from
the stale four-argument prototype moves focused Wibo from 19.22% (615/696) to
19.37% (615/696), with masked operands unchanged at 19 ok, 0 unresolved, 3
mismatch.

2026-07-03 falloff shape: the native sinusoidal center expression materializes
two absolute-distance temporaries before multiplying `(1.0f - a) * (1.0f - b)`.
Splitting the folded scratch expression moves focused Wibo from 19.37%
(615/696) to 20.68% (629/696), with masked operands improving from 19 ok,
0 unresolved, 3 mismatch to 24 ok, 0 unresolved, 1 mismatch.

2026-07-03 orientation guard: the recovered source shape always calls
`rotate_matrix_world_z(roll)` after building the fixed-up frame; the zero-roll
case is left to the helper. Removing the scratch-local guard moves focused Wibo
from 20.68% (629/696) to 20.84% (619/696), with masked operands unchanged at
24 ok, 0 unresolved, 1 mismatch.

2026-07-03 lead-out bound spelling: native keeps the first trailing straight
sample index as `curve_count + 4` and derives the total segment count from that
local. Spelling those as `lead_out_start` and `total_segments` moves focused
Wibo from 20.84% (619/696) to 20.97% (620/696), with masked operands unchanged
at 24 ok, 0 unresolved, 1 mismatch.

2026-07-03 fixed-loop expansion: expanding only the four lead-in and four
lead-out fixed sample loops from the generic helper moves focused Wibo from
20.97% (620/696) to 21.46% (618/696), with masked operands unchanged at
24 ok, 0 unresolved, 1 mismatch. Splitting the probe showed why this stays
limited to the fixed loops: lead-in alone reached 21.14%, lead-out alone
regressed the audit to 22 ok, 0 unresolved, 1 mismatch at 20.84%, curved-body
only regressed to 20.84% with 23 ok, 0 unresolved, 1 mismatch, and expanding
all three loops reached only 21.33% while reducing the audit to 23 ok,
0 unresolved, 1 mismatch.

2026-07-04 mesh request-order probe rejected: swapping strip-mesh requests to
facequads-before-vertices stayed neutral at 21.46% (618/696), with masked
operands unchanged at 24 ok, 0 unresolved, 1 mismatch on the same
`cross_vectors` vs `rotate_matrix_world_z` orientation call pairing. The helper
keeps vertices-first order.

2026-07-04 retained orientation scheduling split: expanding the curved-body
orientation block enough to build both primary and secondary fixed-up frames
before rotating either frame moves focused Wibo from 21.46% (618/696) to
27.36% (620/696). Masked operands improve from 24 ok, 0 unresolved, 1 mismatch
to 28 ok, 0 unresolved, 1 mismatch. The remaining pairing is still an
orientation-schedule mismatch, now native `normalize_vector` against candidate
`rotate_matrix_world_z`, so the broader call-alignment debt remains explicit.

2026-07-15 mesh and departure ownership: the native retains the first trailing
sample index as a mutating four-sample `do/while`, acquires `facequads` before
`vertices`, advances face columns with a `do/while`, and materializes ordinary
row positions as `Vector3` values. The acquisition order is codegen-neutral;
the face-column lifetime reaches 27.40% (618/696), the aggregate reaches 28.31%
(625/696), and the departure lifetime reaches 28.46% (625/696), without adding
an audit problem.

2026-07-15 orientation ownership correction: the native completes and rotates
the primary frame before building the secondary frame, then recomputes the
roll from the primary lane for the secondary rotation. Recovering those two
independent roll lifetimes removes the remaining `normalize_vector` versus
`rotate_matrix_world_z` call mismatch. The retained focused result is 28.42%
(627/696), with 27 clean masked operands and no unresolved or mismatched
operands. This tiny score tradeoff is retained because it restores the observed
per-lane call order and clears the proof audit rather than optimizing only the
fuzzy alignment.

2026-07-15 curved initializer expansion rejection: moving the curved sample's
Z conversion into an expanded direct initializer regressed the clean result to
28.29% (626/696) and 26 clean operands. The inline helper remains until the
surrounding sample-pointer lifetime explains that schedule.

2026-07-17 live owner-ABI closure: the native tail is `retn 0x18`, the iOS
counterpart is `cRPath::BuildSlalom(int, int, bool, char*, char*)`, and the
Windows caller supplies the additional final cap-texture argument. Binary
Ninja's stale five-parameter view had also made the width unsigned, shifted the
first texture onto the mode slot, retained a user-authored `char*` at stack
`+0x14`, and omitted `+0x18`. The guarded recreation now owns the exact
`Path*` receiver and six stack arguments through `cap_texture`; direct readback
confirms signed width and storages `+4..+24`. This is analysis-only: focused
Wibo remains 28.42% (627/696), with 27 clean masked operands and no unresolved
or mismatched operands.

## 2026-07-20 sample and mesh lifetimes

The native orientation loop retains each preceding sample's `basis_forward`,
reloads the current `PathTemplateSample` for the cross product, and finishes
with exact terminal `delta_dir_to_next` owners. The mesh loop keeps one complete
primary sample and reuses one complete `ObjectFaceQuad` record across the
front/back branch.

A transactional preview produced direct vector, sample, vertex, texture, and UV
fields with zero negative `__offset` expressions. The earlier current-sample,
roll-source, and previous-row temporaries remain deliberately untyped. Matcher
source and bytes remain unchanged at 28.42% (627/696 instructions, 27 clean
masked operands); this is ownership recovery only.

## 2026-07-26 shared-face UV completion

The native two-pass face loop keeps one `ObjectFaceQuad*` cursor across its
winding branch, but each arm completes the record independently. The front and
back paths write their own `face->uv[3].v` at `0x420072` and `0x420115`
before rejoining the loop. Recovering that branch-local completion raises
focused matching from 28.42% to 30.79%, grows the candidate from 627 to 629
instructions, and expands the clean operand audit from 27 to 29.

This source boundary is not transferred blindly to the adjacent Sweep/Snake
builders, whose analysis owns two separate face records. Moving only their
final V stores regressed Sweep to 31.83% and Snake to 29.25%; splitting the
entire Sweep record without its still-unrecovered surrounding control shape
also regressed to 31.22%. All three probes were reverted.

## 2026-07-26 complete mesh-vector ownership

Raw native instructions at `0x41fe2d..0x41ff11` prove the same five-value
vertex graph independently visible in SlalomBig and SlalomDouble. The ordinary
branch owns a lateral-offset vector and generated position. The terminal branch
owns its own lateral offset, a raised endpoint, and a generated position. Each
branch materializes the destination vertex only after those values are complete.
The adjacent face lifetime remains the already-proven shared record.

Recovering that owner graph raises focused matching from 30.79% to **32.08%**
and grows the candidate from 629 to **657/696** instructions. It closes the
candidate `0x44` frame to the native `0x50` and establishes a one-instruction
exact prefix. The masked audit remains proof-clean at 26 accepted, 0 unresolved,
and 0 mismatched operands.

## 2026-07-26 mobile first-sample guard

The exact Android and iOS `cRPath::BuildSlalom(int, int, bool, char*, char*)`
corpora both branch on the curved-loop induction variable: iteration zero
resets the preceding sample frames, while later iterations normalize, cross,
and roll them. Expressing the Windows guard as `i == 0`, instead of deriving
the same condition from `sample_index <= 4`, raises focused matching from
32.08% to **32.15%** and shrinks the candidate from 657 to **654/696**
instructions. The exact prefix remains one instruction and the audit remains
clean at 34 accepted, 0 unresolved, and 0 mismatched operands, with 12
unaligned operands still marked unaudited.

The adjacent ARM spellings were tested independently and rejected on Windows:
folding the two falloff owners regressed to 30.79%, a lead-in `do/while`
reached only 32.10%, and spelling the lead-out bound directly regressed to
30.67%. Only the cross-port-supported induction guard is retained.

## 2026-07-27 paired-mobile boolean ABI

The exact Android and iOS `cRPath::BuildSlalom(int, int, bool, char*, char*)`
symbols prove that the third input is a boolean. Both mobile bodies stop after
building the sample/delta data and calling `CalcLengthZ`; Windows owns the
cap-texture and mesh-building tail. Binary Ninja preview, apply, readback, and
lifetime replay kept every recovered owner current.

The focused build remains honestly neutral at **32.15%**, **654/696**
candidate instructions, and a one-instruction exact prefix. Its masked audit
has 34 accepted and 12 unaudited operands with no unresolved or mismatched
operands. The already-retained logical first-curve guard agrees with both
mobile bodies; no new source expression was inferred from the ABI evidence.

## 2026-07-28 paired-mobile control ownership

The exact Android and iOS bodies independently preserve the four-sample
lead-in/out loops, the logical curve induction variable, the curve phase, and
the two absolute center-distance values used by the squared falloff. Those
cross-port bodies establish the authored source graph; the Windows instructions
remain authoritative for exact stack/register lifetimes and for the
Windows-only cap-texture, strip-mesh, and UV tail.

Binary Ninja's shared stack homes had previously made the width argument appear
to own curve counters, mesh columns, mesh width, face columns, and UV values.
Guarded lifetime splits now include the relevant MLIL SSA Phi definitions, so
reads join the recovered lead, tail, curve, mesh, and face owners instead of
falling back to incoming arguments. A separate branch-local
`face_width_plus_one` register owner prevents the partial `ecx` width loads from
leaking into the two-pass `face_pass` induction variable.

Replay, readback, strict export, and decompile health checks produce zero
negative `__offset` expressions and reject the former false curve-to-mesh and
face-pass-to-width dependencies. This is analysis-only: focused matching stays
at **32.15%**, **654/696** candidate instructions, a one-instruction exact
prefix, and 34 accepted plus 12 unaudited operands with no unresolved or
mismatched operands.

## 2026-07-30 x87 compare-reference alignment

The audit now pairs ordered same-width `fcom`/`fcomp` reads of the same
canonical constant while keeping compare operations separate from ordinary
loads. No source or instruction match changed: the focused result remains
32.15%, 654/696 instructions, and prefix 1/696. Two compare pairs move the
receipt from 36 clean plus 8 unaudited entries to 38 clean plus 4 unaudited,
with no unresolved or mismatched references.

## 2026-07-30 signed first-curve guard and stride bound

The native curved loop carries a separate sample-stride lifetime beginning at
`4 * sizeof(PathAttachmentSample)` and advances it by `0xa8`, while the
candidate recomputes `(i + 4) * 0xa8`. Coupled integer indices canonicalize to
the current code or lose 2–7 weighted bytes. Explicit primary/secondary sample
cursors are substantially wrong: the complete cursor form drops to 20.76%,
even though its altered alignment happens to audit all 40 references.

Direct curved-initializer variants confirm that native delays the `(i + 4)`
float conversion until after the primary identity and position-X stores, but
that spelling recovers only one weighted byte and costs an instruction at the
old frontier. Combining it with coupled indices regresses. Natural `for`,
`while`, and `do/while` controls compile identically.

The first-curve predicate does provide one clean Windows win. Because the curve
induction starts at zero and only increments, `i <= 0` is semantically
equivalent to the paired-mobile `i == 0` owner. It also matches the native
signed first-iteration branch more closely, adds one candidate instruction
toward the native count, and recovers seven weighted bytes without changing
the prefix or audit. The retained frontier is therefore **32.42%**,
**655/696** instructions, prefix **1/696**, with 38 audited and four unaudited
references.

Nine recorded sweeps cover 46 variants. After retaining the signed guard, three
consecutive non-improving sweeps formally stall the remaining stride/call
alignment. Further work needs a broader recovered curve-loop lifetime, not raw
byte arithmetic or another local initializer/guard spelling.

## 2026-07-30 authored terminal-delta subtraction

The paired SlalomBig recovery proves that each primary and secondary terminal
delta is authored through `Vector3::operator-`, not a component constructor.
An exhaustive two-site sweep raises focused matching from 32.42% to **32.72%**
by 7.59 weighted bytes. The candidate remains 655/696 instructions with prefix
1/696 and the same 38 clean plus 4 unaudited references. Either site alone
gains half as much; the paired form is the unique best result.

## 2026-07-30 delta byte-cursor ownership

Windows `0x41fc3d..0x41fd10` carries a logical sample counter beside an
independent byte cursor advanced by `sizeof(PathAttachmentSample)` (`0xa8`).
The verified Android and iOS `BuildSlalom` bodies independently preserve the
same two-owner delta traversal. Replacing the derived array scale with one
shared physical cursor adds **3.70 weighted bytes**; moving that cursor's
lifetime ahead of the count guard adds another **3.70**. The retained result
moves from 58.87% to **59.16%**:

```text
target: 696 insns, candidate: 690 insns
prefix: 6/696 target insns
masked operands: 40 ok, 0 unresolved, 0 mismatch, 0 unaudited
```

The narrower control and role schedules are bounded on this frontier. Separate
logical-counter lifetimes lose 1.51 to 7.40 weighted bytes. Reconstructing the
mobile-looking guarded `do/while` with the existing shared `i` owner loses
212.71 to 216.41 bytes, while new-counter `do/while` forms lose 136.63 to
212.71. Slalom therefore keeps the ordinary `for` control, the proven
per-lane subtraction operators, and only the contributing physical cursor.

## 2026-07-30 orientation subtraction bound

Two exhaustive sweeps cover the paired shared helpers and the paired inline
primary/secondary orientation expressions. All six isolated and paired
variants compile byte-identically. Slalom therefore retains the component
constructors at **32.72%**, 655/696 instructions, prefix 1/696, with 38 clean
and 4 unaudited references.

## 2026-07-30 mesh arithmetic ownership

The previously proved branch mesh graph owns ordinary and terminal
right-vector/position pairs independently before each branch materializes its
late destination. A `double` lateral local, both `Vector3::operator*` scales,
and the terminal `Vector3::operator+` add recover that arithmetic boundary and
add 48.17 weighted bytes.

The ordinary add is byte-identical before and after the scale rewrites.
Split-float is neutral, the full double expression adds reference debt, and
volatile float collapses the prefix, so none is retained. Focused matching
rises from **32.72%** to **34.60%**, candidate instructions move from 655 to
651 against 696 target instructions, prefix stays 1/696, and the existing
curve-schedule receipt remains 38 clean plus 4 explicitly unaudited
references.

## 2026-07-30 fixed-sample ownership bound

The Snake and Sweep wins motivated an exhaustive transfer check for the four
fixed lead and departure samples. Direct primary/secondary array ownership was
tested in each phase alone and together. All three variants regress: the lead
form loses 5 weighted bytes, the departure form loses 48, and the combined
form loses 17.

The retained frontier therefore remains **34.60%**, 651/696 instructions,
prefix 1/696, with 38 clean plus 4 unaudited references. The recorded
three-variant sweep closes this local ownership spelling; the sibling result
does not transfer through Slalom's different register schedule.

## 2026-07-30 face-index ownership

The native face tail keeps the integer
`face_index + 2 * (face_row * width_cells + face_column)` owner common while
forming the `cRFaceQuad*` and clearing its header separately in each parity
arm. Recovering that exact split raises focused matching from **34.60%** to
**35.83%**, adds 32 fuzzy-match bytes, and moves the candidate from 651 to
655 instructions against 696 target instructions. Prefix remains 1/696 and
the receipt remains 38 clean plus 4 explicitly unaudited references.

The previous hoisted-pointer form is recorded as a reverse probe and loses the
same 32 fuzzy-match bytes. The integer-only owner is retained because it is
native-backed, materially improves the whole function, and adds no reference
debt.

## 2026-07-30 interacting fixed-sample and header ownership

The Windows prologue assigns width and kind before deriving
`lead_out_start = curve_count + 4`, clears the two mode flags, derives the total
segment count, and finally stores the unit width/scale. Keeping that Slalom-only
header order is byte-neutral by itself, but it improves the recovered fixed
sample owners once the face-index split establishes the native register
schedule.

On the 35.83% frontier, direct primary/secondary array ownership gains 229
weighted bytes in the four lead samples and 302 in the four departure samples.
The complete paired form is the unique best result at **50.84%**, adding 385
weighted bytes and moving the candidate from 655 to 673/696 instructions.
Prefix grows from 1 to 6 instructions without changing the 38 clean plus 4
unaudited reference receipt. Reverting only the header loses 11 weighted bytes;
mutating `lead_out_start` in place loses 15. These reverse probes keep the
native header and the separate departure cursor evidence-bounded.

This interaction also explains the earlier fixed-sample rejection: the same
three variants all regressed before the face-index lifetime changed register
allocation. The prior negative sweep remains in the ledger rather than being
discarded.

## 2026-07-30 complete curved-sample ownership

The native curved body repeatedly reloads both sample arrays through the same
byte-offset owner for initialization and for the later orientation frame.
Direct array ownership in only the initializer regresses the 50.84% frontier to
49.20%. Direct ownership in only the orientation block falls to 42.70%, despite
auditing all 40 references. Together, however, they close the lifetime:
focused matching rises to **58.59%**, adds 199 weighted bytes, and moves the
candidate from 673 to **690/696** instructions.

The retained combination also resolves the four remaining unaudited operands,
leaving **40 clean references with no unresolved, mismatched, or unaudited
entries**. Prefix remains 6/696. Pointer-owner and curve-index variants were
rechecked on the new fixed-owner frontier and all regress; the direct
initializer/orientation pair is retained only as the complete native-backed
dependency.

## 2026-07-30 post-ownership curved byte cursor

The earlier cursor rejection was measured before the complete direct
initializer/orientation dependency was retained. On that new frontier, Windows
proves two independent loop owners: `ebx` is the logical curve counter, while
`edi` starts at `0x2a0` (`4 * 0xa8`) at `0x41f94e`. The latch increments the
counter at `0x41fc2a`, advances the sample byte offset by `0xa8` at `0x41fc2b`,
and tests the logical counter separately at `0x41fc31`.

Addressing both current sample arrays and their preceding orientation samples
through that byte cursor raises focused matching from **58.59%** to **58.87%**,
adding 7.40 weighted bytes. The candidate remains 690/696 instructions with
prefix 6/696 and all 40 references clean. Reverting only the cursor loses the
same 7.40 bytes.

An exhaustive 49-variant sweep covers cursor initialization, stride spelling,
advance order, and the now-codegen-neutral logical `sample_index` declaration.
Every variant is byte-identical. The material recovery is the address owner
itself, and the earlier pre-dependency negative result remains in the ledger.

## 2026-07-30 fixed-sample byte cursors rejected after curved ownership

Windows also exposes byte cursors in the two fixed-sample loops. The lead
cursor advances by `0xa8` at `0x41f850`, increments the logical height index at
`0x41f856`, and is bounded directly against `0x2a0` at `0x41f857`. The
departure cursor advances at `0x41f922`, increments its logical index at
`0x41f928`, and tests the relative logical bound at `0x41f929`-`0x41f92f`.

Those owners do not transfer through the recovered source schedule. On the
58.87% frontier, the departure cursor alone falls to **58.19%**. The native
lead cursor-control form falls to **57.29%**, while retaining logical loop
control falls further to **56.77%**. Pairing the native lead cursor with the
departure cursor produces **57.14%**, still 690/696 instructions with prefix
6/696 and all 40 references clean, but loses 44.40 weighted bytes.

The paired reverse probe records that complete interaction. No fixed cursor is
retained, and the scratch source is restored to the direct indexed fixed-owner
frontier.

## 2026-07-30 checkerboard texture-control bound

The native mesh tail preserves duplicated texture calls behind
`(face_column ^ face_row) & 1` in both branch-local face records. Sweep and
Snake's dependency-complete wins justified testing the same control only after
Slalom's face-index, direct sample, and curved-cursor owners were recovered.

All eight polarity and one-/two-site variants compile. The first parity branch
alone loses 67.03 weighted bytes. The second alone gains 14.34, but the
unsupported one-sided result is rejected. Restoring the symmetric native pair
loses **84.55 weighted bytes** and falls from **58.87% to 55.57%**. Candidate
instructions grow from 690 to 704/696; prefix remains 6/696 and all 40
references remain clean.

Truth-first and negated spellings are byte-identical. No parity branch is
retained on Slalom's current frontier; the native duplicated calls remain a
bounded allocation residual rather than a reason to keep an asymmetric or
regressive source.

## 2026-07-31 fixed-cursor and mesh-row interaction bound

Slalom's native mesh block independently carries the same nonnegative guard,
logical row, and `0xa8` sample cursor recovered in SlalomBig. Transferring that
complete owner to the final Slalom allocation loses **56.01 weighted bytes**,
adds four instructions, and leaves the six-instruction prefix unchanged.

The prologue also gives EDI to the two fixed-sample byte cursors while keeping
`lead_out_start` in EBX, so the paired entrance/departure cursors were rebuilt
with their native increment order and tested together with the mesh row. The
fixed cursors alone lose 22.66 weighted bytes and three instructions. Closing
the fixed-plus-mesh dependency loses 67.64 bytes and produces 691/696
instructions, again without moving the prefix or reference receipt.

No owner is retained. Slalom remains **59.16%**, 690/696 instructions, prefix
6/696, with all 40 references clean. The target register-role swap is real,
but these complete instruction-backed owners do not reproduce it in isolation
or together on the current source schedule.

## 2026-07-31 direct face-offset transfer bounded

Replacing both face pointers with direct indexed records adds only one
weighted byte: **59.16%** to **59.21%**. It also removes one candidate
instruction, moving from 690 to 689 against the 696-instruction target, while
prefix 6/696 and all 40 references remain unchanged. The probe is recorded as
an immaterial instruction-count tradeoff and no source edit is retained.

## 2026-07-31 mesh-sample owner replay

Sharing the current sample across the ordinary and terminal mesh branches
falls from **59.16%** to **56.98%**, loses 56 weighted bytes, and grows the
candidate from 690 to 694 instructions against 696 native. Prefix 6/696 and
all 40 references remain unchanged, so the branch-local sample owners stay.

## 2026-07-31 mesh-column lifetime recovery

The native tail distinguishes the two phase transitions precisely. Its mesh
column owner runs through `0x41fe09..0x41ff22`; the terminal mesh arm exposes
the carried `i_3` storage at `0x41fee4`, and the face pass resets and advances
that same owner at `0x41ff49` and `0x42012a`. The face row instead starts a
fresh `ebx_1` owner at `0x41ff3d`.

Matching that asymmetry raises focused matching from **59.16%** to **60.61%**,
adding 37 weighted bytes. Reusing both row and column gains only 30, while
row-only reuse is byte-neutral, so only the independently supported column
lifetime is retained. Candidate/target size remains 690/696, prefix remains
6/696, and all 40 references remain clean.

## 2026-07-31 post-counter face-record cascade

The recovered mesh-column lifetime materially changes the face allocation, so
the earlier face-record alternatives were rerun rather than treated as
permanent. Direct indexed records now add 12.23 weighted bytes and reach
61.08%, but remain weaker than the record-owner recovery below.

Native code computes the current face address at `0x41ffce..0x41ffd3`, clears
its header at `0x41ffd6`, and enters the side branch at `0x41ffdb`. Giving the
front record an owner before that branch while retaining a fresh back-record
scope adds **92.22 weighted bytes** and raises focused matching from **60.61%**
to **64.20%**. The candidate shrinks from 690 to 684 instructions against 696
native, an explicit size tradeoff, while prefix 6/696 and all 40 clean
references remain unchanged.

The surrounding interactions make the scope specific:

- collapsing both sides onto the outer pointer falls to 44.49%;
- explicitly assigning that pointer again in the back arm reaches 63.77%,
  below the retained distinct back owner;
- hoisting the header with the front pointer reaches 64.01%, five weighted
  bytes below the retained branch-local header;
- direct records reach only 61.08%.

The native duplicated checkerboard texture controls were also rerun after the
owner cascade. A back-only branch gains six weighted bytes, but the front
branch loses 44 and the required symmetric pair loses 107. The unsupported
one-sided score is rejected; both texture calls stay semantically direct.

The ledger now contains 42 records, 33 mutation sweeps, nine probes, and 176
evaluated variants (167 unique). The retained owner is the only large,
instruction-backed gain in this post-counter interaction family.

## 2026-07-31 post-face cursor replay bound

The strongest earlier native-owner rejection was replayed once after the face
record changed whole-function allocation. It remains closed: paired
entrance/departure byte cursors lose 22 weighted bytes, the guarded logical
plus physical mesh row loses 140, and their complete interaction loses 151.
All three preserve prefix 6/696 and the 40-reference clean audit.

Slalom therefore stays at **64.20%**, 684/696 instructions. The fixed cursors
remain compiler-derived from direct indexed source, and the mesh row remains
separate from its physical sample induction on this final face-owner
allocation.
