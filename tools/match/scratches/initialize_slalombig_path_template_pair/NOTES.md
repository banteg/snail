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
