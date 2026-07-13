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

2026-07-03 retained mesh-face loop: replacing the direct `a`/`b` face writes
with the two-iteration `face_index` loop moves focused Wibo from 23.36% (562/671)
to 26.85% (573/671). Masked operands improve from 29 ok, 0 unresolved,
1 mismatch to 31 ok, 0 unresolved, 1 mismatch; the remaining mismatch is still
the sine/cosine pairing in the curved interior.

Rejected: materializing the curved `sine(angle)`, `cosine(angle)`, and
`sine(half)` calls cleared the masked audit but regressed focused Wibo. The
straight local order fell to 24.88% (567/671) and kept one mismatch; the
interleaved `sine(angle)`, `cosine(angle)`, `sine(half)` order fell to 24.54%
(568/671), with masked operands moving to 30 ok, 0 unresolved, 0 mismatch. Keep
the inline expression until a schedule preserves the fuzzy score.

2026-07-13 terminal ownership: fully expanding `compute_terminal_deltas` into
the method regressed focused Wibo from 26.85% (573/671) to 24.03% (586/671)
and worsened the masked audit from 31 ok, 0 unresolved, 1 mismatch to 25 ok,
0 unresolved, 2 mismatch, so `turnover` retains its local delta-loop sample
pointers. Narrowing the change to direct terminal stores through
`path->primary_samples[path->segment_count - 1]` and the secondary array moves
focused Wibo to 27.80% (581/671), with the masked audit unchanged at 31 ok,
0 unresolved, 1 mismatch. The recovered boundary is terminal-array ownership,
not wholesale helper removal.
