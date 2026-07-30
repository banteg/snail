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

## 2026-07-30 orientation subtraction bound

Two exhaustive sweeps cover the paired shared helpers and the paired inline
primary/secondary orientation expressions. All six isolated and paired
variants compile byte-identically. Slalom therefore retains the component
constructors at **32.72%**, 655/696 instructions, prefix 1/696, with 38 clean
and 4 unaudited references.
