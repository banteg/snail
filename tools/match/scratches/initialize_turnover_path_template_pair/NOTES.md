# initialize_turnover_path_template_pair

Ownership recovery for `initialize_turnover_path_template_pair @ 0x426cb0`.

The constructor callsite and target tail show six stack arguments (`ret 0x18`).
The retained scratch scores 52.22% (612/671 candidate/target instructions),
with 36 masked operands clean, 0 unresolved, and 0 mismatch. It now owns the
straight sample seeds, curved sample construction, transform propagation, and
16-bit face header. The main remaining structural debt is the target's 0x54
stack frame and native mesh/delta loop layout; the retained candidate uses a
0x30 frame.

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

2026-07-15 sample ownership cascade: replacing the helper-shaped six-sample
lead-in and two-sample lead-out with direct primary/secondary array ownership,
separate logical Z counters, and the target's do-loop bounds moves focused Wibo
from 27.80% (581/671) to 37.93% (605/671). Retaining the floating curve count,
reusing the incoming `length` slot for the derived radius, and loading the curve
interpolation endpoints from the already-written sample fields also removes the
last masked mismatch.

2026-07-15 curved-body ownership: using separate curve and sample indices,
direct primary/secondary sample fields, the target's sine/cosine call schedule,
inline forward normalization and right-vector cross, and transform-only
secondary propagation moves focused Wibo to 52.22% (612/671). All 36 masked
operands resolve cleanly. The face loop now clears `header_word`, matching the
target's 16-bit store; this is score-neutral but recovers the actual field
width.

Rejected: fully expanding `compute_terminal_deltas` after the curved-body
recovery regressed focused Wibo to 43.26% (619/671), despite clean operands.
Retain the helper boundary until its loop owners can be recovered together.

Rejected: duplicating the parity-specific texture branches around the common
mesh body regressed focused Wibo to 45.83% (625/671). A full Loopbow-shaped
vertex/face mesh transplant fell to 32.79% (689/671) and used a 0x50 frame.
Both encode target-like concepts but not this constructor's source shape.

Rejected: explicitly splitting the terminal and nonterminal mesh vertex paths
with `Vector3` temporaries recovered the exact 0x54 target frame and a
15-instruction prefix, but regressed focused Wibo to 48.64% (657/671).
Combining that shape with duplicated parity branches fell to 45.09% (673/671).
Scalar staging fell to 49.23% (629/671) and lost the recovered frame. Hoisting
the terminal endpoint and passing it through an inlined helper scored 48.98%
(656/671), again with the exact frame and 15-instruction prefix. These probes
locate the remaining frame pressure in the mesh owner without justifying a
lower-agreement rewrite.

## 2026-07-17 live constructor ABI closure

The restarted Binary Ninja session confirms the native `retn 0x18` contract:
`Path* self`, `float length`, integer width and side-exit mode, two surface
textures, and the Windows-only cap texture. This agrees with the portable iOS
`cRPath::BuildTurnover(float, int, bool, char*, char*)` prefix. The stale
database prototype stopped after two textures and mislabeled the final known
stack slot, leaving the cap texture absent.

Guarded recreation and post-write readback now report the exact seven-parameter
prototype with no pending operation. The refreshed caller passes all six stack
operands through `path_pairs[0x25].primary`, and the callee exposes `Path`
fields plus void finalizer flow. This is analysis-only: focused matching remains
52.22% (612/671) with 36 clean masked operands.

## 2026-07-20 live lifetime ownership

A guarded transaction proves nine complete live owners: the primary seed and
mesh samples, primary up vector, secondary position, both terminal deltas, mesh
vertex, and the two face records. Their fields now render directly through
`PathTemplateSample`, `Vec3`, and `ObjectFaceQuad`, with no `__offset`
expressions. A tenth candidate, the pre-biased curved-sample cursor, was
rejected because typing it created two backward `__offset` accesses. Focused
matching remains 52.22% (612/671) with 36 clean masked operands.
