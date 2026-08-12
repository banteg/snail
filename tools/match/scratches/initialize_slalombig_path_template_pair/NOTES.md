# initialize_slalombig_path_template_pair

Current recovery: semantic-complete (`compiler` residual). The verified
Android/iOS builder bodies establish the portable sample/control graph; the
live Windows body and scratch additionally cover the native mesh/face tail.
All references are clean, and the remaining differences are code layout.

Honest starter scratch for `initialize_slalombig_path_template_pair @ 0x4221f0`.

Recovered from the IDA/Binja decompiles and the constructor callsite in
`initialize_game_assets_and_world`: the native cleanup is `ret 0x18`, so the
scratch keeps six explicit arguments after `this`.

The implementation initializes the `SLALOMBIG` path-template record, allocates
primary/secondary samples, builds the four straight lead-in and lead-out nodes,
fills the sinusoidal interior slalom body, derives per-sample orientation and
segment deltas, emits the strip mesh, and calls `calc_path_length_z`.

Residuals are expected. The scratch uses small semantic helpers for the repeated
sample/orientation/mesh idioms instead of attempting instruction scheduling.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 7.98% (131/696
candidate/target instructions) to 19.35% (575/696), with masked operands
improving from 6 ok, 0 unresolved, 5 mismatch to 18 ok, 0 unresolved, 3
mismatch.

2026-07-03 falloff shape: split the slalom body center falloff into the two
native absolute-distance temporaries. Focused Wibo moves from 19.35% (575/696)
to 20.39% (589/696), with masked operands improving from 18 ok, 0 unresolved,
3 mismatch to 23 ok, 0 unresolved, 2 mismatch.

2026-07-03 lead-out bound spelling: native materializes the first trailing
straight sample as `curve_segments + 4`, then derives the total segment count
from that local. Spelling `lead_out_start` and `total_segments` in the scratch
moves focused Wibo from 20.39% (589/696) to 20.44% (586/696), with masked
operands unchanged at 23 ok, 0 unresolved, 2 mismatch.

2026-07-03 retained mesh-face loop: replacing the direct `a`/`b` face writes
with the two-iteration `face_index` loop moves focused Wibo from 20.44% (586/696)
to 21.71% (594/696). Masked operands improve from 23 ok, 0 unresolved,
2 mismatch to 25 ok, 0 unresolved, 1 mismatch; the remaining mismatch is the
interior orientation call pairing.

2026-07-03 lead-in fixed-loop expansion: expanding only the four lead-in fixed
samples from the generic helper moves focused Wibo from 21.71% (594/696) to
21.76% (600/696), with masked operands unchanged at 25 ok, 0 unresolved,
1 mismatch. The sibling slalom full fixed-loop spelling does not transfer
wholesale: expanding both fixed loops regresses to 21.62% (599/696), and
lead-out-only regresses to 21.22% (595/696) with the masked audit dropping to
23 ok, 0 unresolved, 1 mismatch.

2026-07-04 mesh request-order probe rejected: swapping strip-mesh requests to
facequads-before-vertices regressed focused Wibo from 21.76% (600/696) to
20.99% (600/696). Masked operands worsened from 25 ok, 0 unresolved,
1 mismatch to 23 ok, 0 unresolved, 3 mismatch, adding explicit vertices vs
facequads allocation call pairings alongside the existing orientation call
pairing. The helper keeps vertices-first order.

2026-07-04 slalom orientation-split transfer rejected: expanding the curved-body
orientation block so both lanes build fixed-up frames before either roll call
cleared the masked audit to 26 ok, 0 unresolved, 0 mismatch, but regressed
focused Wibo from 21.76% (600/696) to 18.68% (589/696). Unlike `slalom`, this
target keeps the compact `orient_previous_with_up` helper calls.

2026-07-13 terminal ownership: fully expanding the delta helper into the method
regressed focused Wibo slightly to 21.70% (613/696) and reduced masked operands
to 22 ok, 0 unresolved, 1 mismatch, so the local delta-loop pointers remain.
Changing only the terminal stores to address the two `Path` sample arrays
directly moves focused Wibo from 21.76% (600/696) to 24.69% (608/696), with
the masked audit unchanged at 25 ok, 0 unresolved, 1 mismatch. This confirms
terminal-array ownership independently of the constructor-specific loop shape.

2026-07-15 mesh ownership recovery: the native acquires `facequads` before
`vertices` and emits the extrapolated terminal row separately from ordinary
rows. Preserving acquisition order is codegen-neutral; separating the row
branches and materializing the ordinary position as a `Vector3` raises focused
Wibo from 24.69% (608/696) to 25.82% (621/696), without changing the one
orientation mismatch.

2026-07-15 departure and roll-source ownership: the four trailing samples now
advance a mutating departure index, reaching 25.84% (620/696). More
importantly, `orient_previous_with_up` now owns a pointer to the primary
previous sample and computes its roll only after completing each lane's frame.
That keeps the compact helper favored by this target while reproducing the
native primary-frame/primary-roll then secondary-frame/secondary-roll order.
Focused Wibo reaches 28.64% (617/696), with 27 clean masked operands and no
unresolved or mismatched operands.

2026-07-15 rejected follow-ups: moving the width guard and face-column
`do/while` into explicit source regressed the post-mesh result from 25.82% to
25.36% without improving the audit. Expanding the curved pair initializer after
the roll-source recovery regressed the clean result from 28.64% to 27.46%
(615/696). Both compact forms remain until their surrounding lifetimes provide
stronger evidence.

2026-07-17 live owner-ABI closure: the native tail is `retn 0x18`, the iOS
counterpart is `cRPath::BuildSlalomBig(int, int, bool, char*, char*)`, and the
Windows caller supplies the additional final cap-texture argument. Binary
Ninja's stale view returned `int32_t`, owned a `PathTemplate*`, exposed only
four stack parameters, retained a user-authored `char*` at `+0x14`, and omitted
the final `+0x18` slot. The guarded recreation now owns the exact void `Path*`
contract and all six stack arguments. Post-restart readback confirms authored
parameter storages `+4..+24`. This is analysis-only: focused Wibo remains
28.64% (617/696), with 27 clean masked operands and no unresolved or mismatched
operands.

## 2026-07-20 sample and mesh lifetimes

The native function has the same size and exact MLIL variable identities as
the smaller slalom constructor. Their shared replay records the preceding
`basis_forward` vectors, current-sample reloads, terminal deltas, one complete
mesh sample, and the reusable front/back `ObjectFaceQuad` record.

The replay first checks all canonical owner widths and fields, and its
transaction preview yields no negative `__offset` expressions. Matcher source
and bytes remain unchanged at 28.64% (617/696 instructions, 27 clean masked
operands); no source coercion or fakematching is involved.

## 2026-07-26 entrance array ownership

The native fixed entrance loop advances one byte-stride cursor while indexing
both sample arrays from the `Path` owner; it does not retain separate primary
and secondary sample-pointer aliases across the loop body. Removing those two
aliases from SlalomBig moves focused Wibo from 28.64% (617/696) to 29.26%
(623/696), and improves the masked audit from 27 to 28 clean operands with no
unresolved or mismatched operands.

This ownership boundary does not transfer blindly. The same source change
regresses the smaller Slalom scratch from 28.42% to 27.84% in its different
surrounding compilation context, and extending direct array indexing into the
SlalomBig departure loop regresses the new 29.26% baseline to 28.14%. Both
probes were reverted; only the independently improving fixed entrance owner is
retained.

## 2026-07-26 shared-face UV completion

SlalomBig's mesh tail is instruction-identical in ownership to Slalom's. One
face cursor survives the winding branch, while the two arms finish their own
fourth UV pairs at `0x422b02` and `0x422ba5`. Moving `uv[3].v` into those
branches raises focused matching from 29.26% to 31.64%, grows the candidate
from 623 to 625 instructions, and raises the clean operand audit from 28 to 30.

The native header clear is a 16-bit store. Replacing the old byte-sized
`face->flags = 0` view with the shared `face->header_word = 0` owner is
code-generation neutral at that improved result and prevents the scratch from
misstating the record boundary.

## 2026-07-26 complete mesh-vector ownership

SlalomBig's native vertex block at `0x4228bd..0x4229a1` is instruction-identical
in ownership to Slalom's. Ordinary rows own a lateral-offset vector and
generated position; the terminal row separately owns its lateral offset,
raised endpoint, and generated position. The destination vertex is branch-local
and late. Its face builder remains the distinct shared-record shape documented
above.

Recovering those five vector owners raises focused matching from 31.64% to
**33.80%**, grows the candidate from 625 to **653/696** instructions, closes
the `0x44` candidate frame to the native `0x50`, and creates a two-instruction
exact prefix. The masked audit remains clean at 29 accepted, 0 unresolved, and
0 mismatched operands.

## 2026-07-27 paired-mobile ownership refinement

The exact Android and iOS
`cRPath::BuildSlalomBig(int, int, bool, char*, char*)` symbols prove the
boolean ABI. Their paired bodies also branch on the logical curve induction
owner at zero, rather than on a sample index derived from it. Replacing
`current_index <= 4` with `curve_index == 0` is byte-neutral but recovers that
more faithful owner. Both mobile bodies stop after sample/delta construction
and `CalcLengthZ`; Windows owns the cap-texture and mesh-building tail.

Binary Ninja preview, apply, readback, and lifetime replay kept every recovered
owner current. The focused build remains **33.80%**, **653/696** candidate
instructions, and a two-instruction exact prefix; its masked audit has 35
accepted and 10 unaudited operands with no unresolved or mismatched operands.

## 2026-07-28 paired-mobile control ownership

The exact Android and iOS bodies independently preserve the four-sample
lead-in/out loops, the logical curve induction variable, the curve phase, and
the two absolute center-distance values used by the squared falloff. Those
cross-port bodies establish the authored source graph; the Windows instructions
remain authoritative for exact stack/register lifetimes and for the
Windows-only cap-texture, strip-mesh, and UV tail.

SlalomBig is an exact Windows instruction homology of the smaller Slalom
constructor across this ownership graph. The guarded replay therefore
translates one reviewed address set by the exact function-base delta, then
requires every translated MLIL identity to resolve before applying it. The
stack splits include the loop SSA Phi definitions; a separate branch-local
`face_width_plus_one` register owner keeps partial `ecx` width loads from
contaminating the two-pass `face_pass` induction variable.

Replay, readback, strict export, and decompile health checks produce zero
negative `__offset` expressions and reject the former false curve-to-mesh and
face-pass-to-width dependencies. This is analysis-only: focused matching stays
at **33.80%**, **653/696** candidate instructions, a two-instruction exact
prefix, and 35 accepted plus 10 unaudited operands with no unresolved or
mismatched operands.

## 2026-07-30 x87 compare-reference alignment

The compare-family audit proves two ordered `fcom`/`fcomp` pairs against the
same zero constant without equating either instruction with an ordinary load.
Source and bytes remain unchanged at 33.80%, 653/696 instructions, and prefix
2/696. The current receipt has 39 clean plus 2 unaudited entries, down from
37 clean plus 6 unaudited, with no unresolved or mismatched references.

## 2026-07-30 paired identity-call schedule bound

The two unaudited entries are one native and one candidate
`set_matrix_rotation_identity` call. Both sides invoke the helper for each lane,
but native finishes the lane work before one shared first-curve branch, so its
two calls are adjacent; the current forced-inline lane helpers retain separate
guards and leave one call pair outside sequence alignment.

Three bounded sweeps cover outer zero/nonzero and sample-index guards, removal
of the redundant helper branch, and path/array pair-helper ownership. Every
pair-level guard audits all 40 references, but the best form loses 27 weighted
bytes and falls from 33.80% to 32.77%. Pair helpers reach at most 32.62%.

The append-only ledger contains 17 variants: 2 are byte-identical and 15
regress. The tested forms leave the target at
the retained 33.80%, 653/696-instruction frontier. Recovering the adjacency now
requires a broader loop-lifetime change, not another local guard or helper
spelling.

## 2026-07-30 terminal-delta expression ownership

The exact terminal-delta helper shape shared with Twister provides a new
independent owner boundary outside the recorded identity-call schedule.
Replacing the four loop-wide sample pointers with direct primary and secondary
array ownership raises focused matching from 33.80% to **36.61%**, adds 71.85
weighted bytes, and moves the candidate from 653 to 659 instructions against
696. The two-instruction prefix and the 39 clean plus 2 unaudited references
are unchanged.

Applying authored `Vector3::operator-` at both delta sites adds another 7.57
weighted bytes. The retained result is **36.90%**, 659/696 instructions,
prefix 2/696, with the same 39 clean and 2 unaudited references. The exhaustive
two-site sweep proves that either operator alone gains 3.78 bytes and that the
paired form is the unique best result.

## 2026-07-30 orientation subtraction bound

The remaining previous/current orientation helper was tested with the authored
operator form and compiles byte-identically. The retained frontier stays
**36.90%**, 659/696 instructions, prefix 2/696, with 39 clean and 2 unaudited
references.

## 2026-07-30 mesh arithmetic ownership

The native vertex block at `0x4228bd..0x4229a1` preserves the lateral value on
the x87 stack across SlalomBig's already-recovered five-vector graph. `double
lateral` gains 6.60 weighted bytes, and the terminal
`Vector3::operator+` gains another 5.21 while the ordinary addition is
byte-neutral.

Both `Vector3::operator*` expressions improve independently and gain 63.11
weighted bytes together. Rechecking the ordinary addition in that final state
is still byte-neutral, so it remains component-authored.

The retained scalar, terminal add, and paired scales raise focused matching
from 36.90% (659/696) to **39.82%** (655/696), a total gain of 74.92 weighted
bytes. The two-instruction prefix and the 39 clean plus 2 unaudited reference
receipt remain unchanged. The four-instruction shortening is bounded to
directly proven native arithmetic owners.

## 2026-07-30 complete sample-owner dependency

Raw Windows instructions preserve the same ownership graph already recovered
for Slalom: width is stored before kind, `curve_segments + 4` remains the
departure owner, both fixed arrays are reloaded through that index, and the
curved initializer and both orientation lanes share one advancing sample
offset. The paired mobile bodies independently support the logical
first-curve guard.

Recovering the native header, direct departure samples, direct curved
initializer, and shared direct orientation as one transaction raises focused
matching from **39.82%** to **50.98%**. It adds 286 weighted bytes, moves the
candidate from 655 to **685/696** instructions, grows the exact prefix from 2
to **6/696**, and resolves the two remaining unaudited operands. The receipt is
now **40 clean references with no unresolved, mismatched, or unaudited
entries**.

Reverse probes bound each required part on the new frontier. Restoring the
departure pointer pair loses 316 weighted bytes; restoring only the curved
initializer helper loses 303; restoring the two orientation helpers loses 273
and reintroduces both audit gaps. Changing the nonnegative logical
`i == 0` guard to signed `i <= 0` loses 141 weighted bytes.

The old header order happens to gain four fuzzy bytes after the other owners
are fixed, but it contradicts the observed width/kind/departure/flag store
order and adds no prefix, instruction-count, or audit benefit. That metric-only
tradeoff is recorded and rejected; the instruction-backed header is retained.

## 2026-07-30 face-index ownership divergence

The branch-local face-index recovery from Slalom does not transfer to
SlalomBig. Native `0x422a5e..0x422a6b` computes the common record offset,
materializes one `ObjectFaceQuad*`, and clears its header before testing the
parity arm. That is exactly the current hoisted-pointer source shape, whereas
Slalom materializes its face record inside each arm.

This native control-flow difference closes the sibling hypothesis without a
metric probe. SlalomBig remains **50.98%**, 685/696 instructions, prefix
6/696, with all 40 references clean.

## 2026-07-30 post-ownership curved byte cursor rejected

The Slalom cursor win was retested only after SlalomBig's complete direct
sample-owner dependency was retained. Native SlalomBig has the same physical
induction: `edi` starts at `0x2a0` at `0x4223de`, the logical curve counter
increments independently at `0x4226ba`, the cursor advances by `0xa8` at
`0x4226bb`, and the logical counter is tested at `0x4226c1`.

That physical similarity does not transfer as explicit source ownership.
Addressing the current and preceding samples through a direct byte cursor
rotates the candidate's long-lived `this`, logical counter, and address cursor
across EDI/ESI/EBX. The simple form falls from **50.98%** to **34.42%**
(681/696 instructions). Adding the native positive guard and one hoisted
floating curve count reaches only **34.52%** (683/696) and loses 422.03
weighted bytes from the retained frontier. Both forms keep all 40 references
clean, so the regression is allocation and schedule debt rather than an audit
artifact.

The guarded reverse probe is recorded and the source is restored. SlalomBig
therefore keeps direct array ownership; its native byte cursor remains a
compiler-derived consequence of that dependency in the current source
context.

## 2026-07-30 checkerboard texture control

SlalomBig's native mesh keeps the same duplicated per-face texture calls
behind `(column ^ row) & 1`, but its hoisted face-record owner differs from
Slalom's branch-local records. Testing the two texture branches in isolation
and together confirms that this allocation supports the complete control
unit.

The first parity branch alone adds 31.32 weighted bytes; the second alone
loses 63.02. Restoring both is the unique best native-backed result: it adds
**45.90 weighted bytes**, raises focused matching from **50.98% to 52.77%**,
and grows the candidate from 685 to **695/696** instructions. Prefix remains
6/696 and all 40 references stay clean.

The symmetric truth-first family form is retained. The near-exact instruction
count is a corroborating consequence, not the selection criterion: the
evidence-complete pair wins on weighted agreement and preserves the target's
observed control flow, while the tempting one-sided alternatives do not.

## 2026-07-30 post-parity curve cursor recovery

The earlier physical curve-cursor probe was not a permanent negative result.
It preceded the complete direct sample-owner dependency and checkerboard
control recovery. Replaying the same `0x2a0` start and `0xa8` stride on that
stronger frontier changes the allocation cascade: the cursor plus a
first-physical-sample equality guard raises focused matching from **52.77% to
61.25%**, keeps the candidate at 695/696 instructions, and extends the exact
prefix from 6 to **26/696**. All 40 references remain clean.

The equality expresses the cross-port logical first-iteration condition under
the positive cursor invariant. A complete six-way guard sweep bounds the
choice on the final cursor frontier. Hexadecimal equality is byte-identical;
the logical loop index loses 188 weighted bytes, the native rendered
less-or-equal range loses 225, the next-sample range loses 349, and the
separate logical sample index loses 355. The committed pre-cursor source loses
218 weighted bytes in the intermediate reverse probe.

This resolves the prior 34.42% reversal as an ordering dependency, not evidence
against the native cursor. The physical owner only becomes profitable after
the surrounding array, orientation, and texture-control lifetimes agree.

## 2026-07-30 fixed-sample byte cursors

The native entrance and departure loops independently advance byte offsets
beside their logical sample indices. Replaying both owners after the curve
cursor recovery improves each site independently: the entrance cursor adds
10 weighted bytes and grows the exact prefix from 26 to 48 instructions; the
departure cursor adds 34. Their paired form reaches **62.97%** and adds 44
weighted bytes over the 61.25% curve-cursor result.

The entrance's independent logical counter is retained from the native owner
graph; splitting it from the later curve counter is byte-identical. Ordering
its semantic increment before the byte stride adds another 11 weighted bytes,
while reversing only the departure increments loses 7. Alternative secondary
pointer-addition orders are byte-identical. Three algebraically equivalent
departure bounds are also byte-identical, while direct upper-bound and
lead-out-owner conditions regress by 429 and 572 weighted bytes.

The complete sample-cursor cascade raises SlalomBig from **52.77% to 63.40%**,
adds **273 weighted bytes**, shortens the candidate from 695 to **692/696**
instructions, and grows the exact prefix from 6 to **48/696**. The masked
receipt remains proof-clean at 40 accepted references with no unresolved,
mismatched, or unaudited entries.

Post-cascade controls do not expose a hidden follow-up: all six curve increment
orders are neutral or lose four bytes, authored orientation subtraction stays
byte-identical, and moving the sine phase ahead of the two falloff comparisons
loses 285 weighted bytes. The retained source therefore stops at the measured
owner boundary rather than coercing the remaining register-order differences.

## 2026-07-30 terminal-delta cursor and guard ownership

The terminal-delta loop at `0x4226cd..0x4227a0` has a second independent
physical induction that was not covered by the earlier curve and fixed-sample
cursor work. Native zeroes the logical counter in EBX before its positive
guard, zeroes the byte cursor in EDI only after the guard succeeds, advances
the counters by one sample and `0xa8` bytes respectively, and tests the
logical counter against `segment_count - 1`. Both verified mobile bodies
preserve this logical-plus-physical traversal; the iOS rendering also preserves
the guarded `do/while` control shape.

Making that byte owner explicit adds 18.47 weighted bytes to the 63.40%
frontier and reaches **64.12%**. The direct and offset-first spellings compile
identically. A scoped sample-pointer spelling loses 31.45 weighted bytes,
shortens the candidate by eight instructions, and collapses the prefix from 48
to 6, so the owner is the offset itself rather than a persistent record
pointer.

Placing the logical zero before the guard and expressing the body as a
`do/while` adds another 3.69 weighted bytes. The retained result is
**64.27%**, 692/696 instructions, prefix 48/696, with all 40 references clean.
Its emitted control unit has the native shape exactly: logical zero, one
positive guard, physical zero, body, logical increment, final secondary
length store, byte stride, reloaded bound, and back edge.

One source spelling scored **72.09%** and 694/696 instructions, but it is
rejected. Wrapping a `for` loop in the positive guard emits a second
`cmp`/`jle` immediately after the native guard. That duplicate test is absent
from the Windows target and from the verified mobile ownership evidence; the
large fuzzy gain is downstream alignment purchased by two known-wrong
instructions. Initializing both counters before the guard is neutral, while
moving both inside the guarded `do/while` is byte-identical to the retained
logical-before-guard spelling. The committed form therefore follows the
instruction evidence rather than the largest aggregate score.

## 2026-07-31 native mesh-row ownership

The mesh vertex block has the same logical row and physical sample traversal
seen in the native body: a nonnegative segment guard, a guarded post-tested
column loop, and independent `row` and `0xa8` sample-offset advances. Replaying
that ownership while preserving the already-proven double lateral arithmetic,
ordinary vector operators, and terminal `sample[-1]` endpoint raises focused
matching from **64.27% to 65.37%**. It adds **28.28 weighted bytes**, shortens
the candidate from 692 to **690/696** instructions, keeps the exact prefix at
48/696, and leaves all 40 masked references clean. Reverting only this owner
loses the same 28.28 weighted bytes, so the source change is retained.

The surrounding owner frontier is bounded rather than guessed through. A
separate departure-bound local loses 102.69 weighted bytes and collapses the
prefix to 6. Moving the curve phase earlier loses 285.46 weighted bytes; only
the named-denominator late-angle spelling is byte-identical. Explicit mesh
object acquisition is neutral when face records stay first, while
vertices-first acquisition loses 3.70 weighted bytes.

The terminal endpoint's closest default-construction spelling still loses
8.51 weighted bytes and adds four instructions; alternate assignment orders
lose more, and copy-then-add forms lose 117.09. Finally, replaying the complete
native-style positive guards and post-tested face loops on this new frontier
loses 25.90 weighted bytes without changing the prefix or instruction count.
The target's remaining terminal and face-register differences therefore do not
transfer as isolated source owners. The retained milestone stops at the
evidence-backed mesh-row replay.

## 2026-07-31 lead secondary-acquisition bound

The 48-instruction prefix ends at the lead loop's secondary identity call:
native forms the address by loading the array base into EAX and adding the byte
cursor through ECX, while the candidate loads the base directly into ECX.
Arithmetic-order spellings were already neutral, so four scoped acquisition
owners were tested around the call.

Call-only `PathTemplateSample*` and `TransformMatrix*` owners compile
byte-identically. Extending the record owner through the three position stores
loses 74.00 weighted bytes and collapses the prefix to one instruction.
Addressing only the identity call through the logical sample index loses
499.18 weighted bytes, adds four instructions, reduces the clean audit to 39
references plus two unaudited entries, and also leaves only a one-instruction
prefix.

No acquisition owner is retained. SlalomBig remains **65.37%**, 690/696
instructions, prefix 48/696, with all 40 references clean; the register choice
at the identity call remains compiler allocation debt.

## 2026-07-31 direct face-offset record ownership

Writing the face record directly through its semantic array offset raises
focused matching from **65.37%** to **66.09%** and moves candidate size from
690 to 693 instructions against the 696-instruction target. Prefix remains
48/696 and all 40 references remain clean. The secondary-acquisition bound
above remains intact; this change is isolated to the later mesh record.

## 2026-07-31 post-face sample-owner replay

Hoisting the byte-derived current sample across the mesh branch loses 138
weighted bytes and falls from **66.09%** to **60.71%**. Candidate size moves
from 693 to 691 instructions against 696 native; prefix 48/696 and all 40
references remain clean. The existing branch-local sample derivations remain
part of the recovered row-cursor schedule.

## 2026-07-31 post-face ordinary position-add replay

The direct face-offset recovery changed the tail allocation after the earlier
mesh-vector sweep. Replaying the ordinary generated-position expression on the
new frontier raises focused matching from **66.09%** to **66.23%**, adding
**3.69 weighted bytes** without changing the 693/696 instruction count,
48-instruction prefix, or 40 clean references.

The retained `position + lateral_offset` boundary completes the same
post-face dependency seen in Start, Invert, Wibble, and Twister. Screw already
owns both vector additions, while Hump and Dump have explicit post-counter
vector bounds, so this closes the remaining untested member of the current
mesh-tail family.

## 2026-07-31 post-add face-phase closure

The remaining face-phase owners were replayed after the ordinary position
addition changed the final allocation. Native loads vertices before facequads,
but that explicit source order still loses **3.69 weighted bytes** and falls
back to 66.09%; retaining a strip-mesh object with facequads-first acquisition
is byte-identical to the current **66.23%** source.

Separating the reused face counters is negative. A fresh face row loses about
seven weighted bytes and reaches 65.95%; a fresh face column loses 37 and
reaches 64.79%; separating both also reaches 64.79%. The native-looking
independent UV-column owner is byte-identical, so VC6 already emits that
physical lifetime from the clearer shared column.

No source change is retained. SlalomBig remains at **66.23%**, 693/696
instructions, prefix 48/696, with all 40
references clean. The remaining load and counter identities are bounded
compiler-allocation residuals rather than untested source owners.
