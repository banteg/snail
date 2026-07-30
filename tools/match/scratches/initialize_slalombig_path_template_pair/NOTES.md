# initialize_slalombig_path_template_pair

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
regress. Three consecutive non-improving sweeps formally stall the target at
the retained 33.80%, 653/696-instruction frontier. Recovering the adjacency now
requires a broader loop-lifetime change, not another local guard or helper
spelling.
