# initialize_turnoverdouble_path_template_pair

Ownership recovery for `initialize_turnoverdouble_path_template_pair @ 0x427640`.

This target uses the same six-argument stack shape as turnover (`ret 0x18`),
but the interior curve performs a double roll and returns to the same lateral
side. The retained scratch scores 51.70% (616/680 candidate/target
instructions), with 43 masked operands clean, 0 unresolved, and 0 mismatch.
It owns the straight sample seeds, folded double-roll construction, transform
propagation, and 16-bit face header. The main remaining structural debt is the
target's 0x50 stack frame and native mesh/delta loop layout; the retained
candidate uses a 0x2c frame.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 9.81% (176/680
candidate/target instructions) to 23.98% (571/680), with masked operands
improving from 14 ok, 0 unresolved, 7 mismatch to 32 ok, 0 unresolved, 1
mismatch.

2026-07-03 rejected seed-X reload: applying turnover's secondary-X reload from
the primary center field reduces focused Wibo to 23.68% (570/680), so this
sibling keeps the original argument-based seed helper spelling.

2026-07-03 retained mesh-face loop: replacing the direct `a`/`b` face writes
with the two-iteration `face_index` loop moves focused Wibo from 23.98% (571/680)
to 27.60% (581/680). Masked operands improve from 32 ok, 0 unresolved,
1 mismatch to 34 ok, 0 unresolved, 1 mismatch; the remaining mismatch is still
the sine/cosine pairing in the curved interior.

2026-07-04 cosine-center probe rejected: replacing the center-X expression
`sine(slalom_angle + 1.5707964f) * left` with the semantic equivalent
`cosine(slalom_angle) * left` regressed focused Wibo from 27.60% (581/680) to
25.76% (578/680). Masked operands worsened from 34 ok, 0 unresolved,
1 mismatch to 31 ok, 0 unresolved, 2 mismatch, adding a target `sine` vs
candidate `cosine` pairing before the existing target `cosine` vs candidate
`sine` residual. Keep the phase-shifted sine spelling until the surrounding
curved-call schedule changes.

2026-07-13 terminal ownership: as in `turnover`, the delta loop retains its
local sample pointers, while the two terminal writes belong directly to the
`Path` sample arrays. Replacing `last_primary` and `last_secondary` pointer
aliases with direct count-relative array stores moves focused Wibo from 27.60%
(581/680) to 28.53% (589/680). The masked audit remains 34 ok, 0 unresolved,
1 mismatch; the sole residual is still the curved sine/cosine call pairing.

2026-07-15 sibling ownership cascade: replacing the helper-shaped six-sample
lead-in and two-sample lead-out with direct primary/secondary array ownership,
separate logical Z counters, and the target's do-loop bounds recovers the same
owner split as `turnover`. The floating curve count is retained, the incoming
`length` slot owns the derived double-roll radius, and the lateral curve center
loads the already-written first primary sample field.

The curved body now uses separate curve and sample indices, preserves the
native phase-shifted sine and folded roll angles, follows the target's trig call
schedule, constructs forward/right bases directly, and copies only the primary
transform before applying the secondary up-vector offset. Focused Wibo moves
from 28.53% (589/680) to 51.70% (616/680), and the prior sine/cosine audit
mismatch clears: all 43 masked operands resolve cleanly. The face loop now
clears `header_word`, matching the target's 16-bit store.

As with `turnover`, keep `compute_terminal_deltas` and the semantic strip-mesh
helper boundary until their native loop owners can be recovered together.
Target-shaped mesh transplants in the sibling recovered frame pressure but
reduced whole-function agreement, so this target does not repeat those
lower-signal rewrites.

## 2026-07-17 live constructor ABI closure

The restarted Binary Ninja session confirms the native `retn 0x18` contract:
`Path* self`, `float length`, integer width and side-exit mode, two surface
textures, and the Windows-only cap texture. This agrees with the portable iOS
`cRPath::BuildTurnoverDouble(float, int, bool, char*, char*)` prefix. The stale
database prototype stopped after two textures and mislabeled the final known
stack slot, leaving the cap texture absent.

Guarded recreation and post-write readback now report the exact seven-parameter
prototype with no pending operation. The refreshed caller passes all six stack
operands through `path_pairs[0x26].primary`, and the callee exposes `Path`
fields plus void finalizer flow. This is analysis-only: focused matching remains
51.70% (616/680) with 43 clean masked operands.
