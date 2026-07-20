# initialize_slalomdouble_path_template_pair

Honest starter scratch for `initialize_slalomdouble_path_template_pair @ 0x425050`.

The constructor callsite uses the same six-argument stack shape as the slalom
family and the native epilogue is `ret 0x18`. The runtime kind written by this
public constructor is `0x20`, matching the current decompile. The scratch builds
the fixed 70-sample double-slalom body with four straight samples at each end,
sinusoidal lateral motion, raised Y motion, orientation, deltas, strip mesh, and
`finalize_path_template`.

Residuals are expected. This is a semantic starter, not a tuned byte match.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 10.59% (129/683
candidate/target instructions) to 22.28% (574/683), with masked operands
improving from 12 ok, 0 unresolved, 5 mismatch to 31 ok, 0 unresolved, 1
mismatch.

2026-07-03 falloff shape: split the double-slalom center falloff into the two
native absolute-distance temporaries before the sine/scale multiply. Focused
Wibo moves from 22.28% (574/683) to 22.66% (588/683), with masked operands
improving from 31 ok, 0 unresolved, 1 mismatch to 32 ok, 0 unresolved, 1
mismatch.

2026-07-03 orientation guard: native source shape always dispatches the previous
sample through `rotate_matrix_world_z(roll_angle)` after the up/cross-vector
orientation frame. Removing the zero-roll guard moves focused Wibo from 22.66%
(588/683) to 22.84% (578/683), with masked operands unchanged at 32 ok,
0 unresolved, 1 mismatch.

2026-07-03 fixed-sample initializer spelling: reload primary and secondary X
from the stored primary `center_x` field, then delay the integer-to-float Z
conversion until inside the inlined sample initializer after the primary
identity call. Focused Wibo moves from 22.84% (578/683) to 23.14% (570/683);
the masked audit keeps the same single call mismatch but has one fewer audited
ok (31 ok, 0 unresolved, 1 mismatch).

Rejected: spelling the fixed trailing straight samples with `lead_out_start =
66` and `total_segments = lead_out_start + 4` regressed focused Wibo to 22.61%
(582/683) and worsened the masked audit to 30 ok, 0 unresolved, 2 mismatch, so
the fixed `70` / `66` constants stay in the scratch.

2026-07-03 retained mesh-face loop: replacing the direct `a`/`b` face writes
with the two-iteration `face_index` loop moves focused Wibo from 23.14% (570/683)
to 26.92% (580/683). Masked operands change from 31 ok, 0 unresolved,
1 mismatch to 32 ok, 0 unresolved, 3 mismatch; the extra residuals are in the
interior orientation call pairings.

Rejected: the `slalom` orientation scheduling split does not transfer here.
Expanding both lane orientations before either roll call reduced masked
residuals from 32 ok, 0 unresolved, 3 mismatch to 30 ok, 0 unresolved,
1 mismatch, but regressed focused Wibo from 26.92% (580/683) to 25.08%
(577/683). The compact helper calls stay as the better current score baseline.

2026-07-04 fixed-loop expansion retest rejected: expanding the four lead-in
fixed samples from `initialize_pair_sample` compiled to the same focused Wibo
result as the retained helper loop: 26.92% (580/683), with masked operands
unchanged at 32 ok, 0 unresolved, 3 mismatch. Expanding only the four trailing
fixed samples was also binary-neutral at the same score and audit. Keep both
fixed loops in the compact helper form until a broader register-ownership
change gives the expansion a different alignment context.

2026-07-04 mesh request-order probe rejected: swapping strip-mesh requests to
facequads-before-vertices regressed focused Wibo from 26.92% (580/683) to
26.13% (580/683). Masked operands worsened from 32 ok, 0 unresolved,
3 mismatch to 30 ok, 0 unresolved, 5 mismatch, adding explicit vertices vs
facequads allocation call pairings alongside the existing orientation residuals.
The helper keeps vertices-first order.

2026-07-13 terminal ownership: removing the `last_primary` and
`last_secondary` pointer aliases while retaining the constructor-specific
delta loop moves focused Wibo from 26.92% (580/683) to 29.90% (588/683).
The masked audit remains 32 ok, 0 unresolved, 3 mismatch; all three residuals
are the pre-existing interior orientation pairings. The terminal stores belong
directly to the two count-relative `Path` sample arrays.

2026-07-15 curved-body ownership: the native double-slalom keeps a zero-based
logical curve counter separate from its sample cursor. Its sample constructor
also owns the primary field stores and identity before calling `cosine` for Y,
then initializes the secondary transform from the written primary position.
Recovering those lifetimes and computing both delta streams directly in the
`Path` owner moves the retained focused result through 29.96% and 32.89%.
Splitting terminal and ordinary vertex rows then reaches 33.05%; expanding the
curved initializer in its target call order reaches 33.31%.

2026-07-15 orientation ownership: unlike the single outer guard used by the
related Slalom source, this target has an independent guard for each lane. Each
non-initial lane builds and normalizes its own frame, performs its cross, and
only then derives the roll from the primary previous sample. The secondary
lane recomputes that primary-owned roll after completing its own cross. This
source order supersedes the older grouped-frame rejection above, reaches
33.98% (606/683), and clears all three call residuals for 33 ok, 0 unresolved,
0 mismatch. The face header is now cleared through the shared 16-bit
`header_word` owner; that field clarification is codegen-neutral.

Rejected in the current context: forcing the four trailing fixed samples into
an explicit subtract-bound `do/while` regressed 30.03% (589/683) to 29.80%
(599/683), and rewriting the already post-tested face-column loop explicitly
regressed 33.05% (606/683) to 32.27%. Neither changed the operand audit, so the
smaller equivalent loop spellings remain instead of tuning control flow.

2026-07-17 live owner-ABI closure: the native tail is `retn 0x18`, the iOS
counterpart is `cRPath::BuildSlalomDouble(int, int, bool, char*, char*)`, and
the Windows caller supplies the additional final cap-texture argument. Binary
Ninja's stale view returned `int32_t`, owned a `PathTemplate*`, and exposed only
three stack parameters; a user-authored `char*` survived at `+0x10`, `+0x14`
was merely automatic, and the final `+0x18` slot was absent. The guarded
recreation now owns the exact void `Path*` contract and all six stack arguments.
Post-restart readback confirms authored parameter storages `+4..+24`. This is
analysis-only: focused Wibo remains 33.98% (606/683), with 33 clean masked
operands and no unresolved or mismatched operands.

2026-07-20 live lifetime closure: transactional MLIL preview recovers the
preceding primary/secondary forward vectors, both current-sample reloads, both
terminal deltas, the current mesh sample, and the complete facequad record
reused by the native two-variant mesh branch. All eight owners render direct
`Vec3`, `PathTemplateSample`, or `ObjectFaceQuad` fields without introducing an
`__offset` expression. The earlier sample and rotation cursors and the
previous-row mesh cursor remain automatic because typing their byte-relative
addresses did not improve ownership. This is analysis-only: focused Wibo
remains 33.98% (606/683), with 33 clean masked operands and no unresolved or
mismatched operands.
