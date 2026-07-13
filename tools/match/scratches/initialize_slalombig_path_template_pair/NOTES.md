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
