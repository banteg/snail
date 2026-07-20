# initialize_slalombig_path_template_pair

Honest starter scratch for `initialize_slalombig_path_template_pair @ 0x4221f0`.

Recovered from the IDA/Binja decompiles and the constructor callsite in
`initialize_game_assets_and_world`: the native cleanup is `ret 0x18`, so the
scratch keeps six explicit arguments after `this`.

The implementation initializes the `SLALOMBIG` path-template record, allocates
primary/secondary samples, builds the four straight lead-in and lead-out nodes,
fills the sinusoidal interior slalom body, derives per-sample orientation and
segment deltas, emits the strip mesh, and calls `finalize_path_template`.

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
