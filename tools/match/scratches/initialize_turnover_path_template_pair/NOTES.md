# initialize_turnover_path_template_pair

Honest starter scratch for `initialize_turnover_path_template_pair @ 0x426cb0`.

The constructor callsite and target tail show six stack arguments (`ret 0x18`).
The scratch models the left lead-in, right lead-out, single turnover roll,
secondary sample offset along the rotating up vector, deltas, strip mesh, and
`finalize_path_template`.

Residuals are expected; helper calls keep this readable and semantic rather
than byte-shaped.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 8.77% (173/671
candidate/target instructions) to 22.85% (563/671), with masked operands
improving from 9 ok, 0 unresolved, 7 mismatch to 28 ok, 0 unresolved, 1
mismatch.

2026-07-03 seed-X reload: spelling the straight seed helper's secondary X as a
reload from the already-written primary center field moves focused Wibo to
23.36% (562/671), with masked operands improving to 29 ok, 0 unresolved, 1
mismatch.

Rejected: moving the curved sample Y/cosine write before the X/sine write raised
focused Wibo only to 23.52% (562/671) while worsening the masked audit from
29 ok, 0 unresolved, 1 mismatch to 28 ok, 0 unresolved, 2 mismatch. The retained
order keeps X before Y until the sine/cosine pairing is better understood.
