# initialize_turnunder_path_template_pair

Ownership recovery for `initialize_turnunder_path_template_pair @ 0x427fe0`.

The retained scratch scores 48.06% (628/687 candidate/target instructions),
with 41 masked operands clean, 0 unresolved, and 0 mismatch. It owns the
opposite-signed straight sample seeds, nonlinear under-roll construction,
transform-only secondary propagation, and 16-bit face header. The main
remaining structural debt is the target's 0x54 stack frame and native
mesh/delta loop layout; the retained candidate uses a 0x2c frame.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 8.37% (197/687
candidate/target instructions) to 14.79% (598/687), with masked operands
improving from 6 ok, 0 unresolved, 10 mismatch to 13 ok, 0 unresolved, 7
mismatch.

2026-07-03 path-template seed-loop sweep: delayed the `turns * 2pi`
conversion until after the header stores, split straight lead-in/exit samples
into a native-style primary/secondary initializer, set straight-sample
`delta_length`, and reload the nonlinear interpolation endpoints from the
seeded primary sample centers. Focused Wibo moved from 14.79% (598/687) to
20.96% (582/687), with masked operands improving from 13 ok, 0 unresolved, 7
mismatch to 22 ok, 0 unresolved, 5 mismatch. Rejected adjacent probes: swapping
the start/end center expressions regressed to 20.80%, and materializing
`interior_count_f` / `radius = interior_count_f * 0.15915494f` before allocation
regressed to 20.33% despite one extra clean masked operand.

2026-07-03 scalar-order cleanup probe: applying the sibling sample-scalar
spelling (`rotation_scalar_98`, `rotation_scalar_94`, `special_scalar`,
`lateral_scale`) and removing scratch-only `lateral_source` traffic regressed
focused Wibo from 20.96% (582/687) to 18.08% (563/687), with masked operands
dropping from 22 ok, 0 unresolved, 5 mismatch to 19 ok, 0 unresolved, 5
mismatch. Left out; the current turnunder layout still depends on the older
scalar traffic until the interior loop shape is rebuilt.

2026-07-03 retained mesh-face loop: replacing the direct `a`/`b` face writes
with the two-texture `face_index` loop moves focused Wibo from 20.96% (582/687)
to 23.92% (592/687). Masked operands improve from 22 ok, 0 unresolved,
5 mismatch to 24 ok, 0 unresolved, 5 mismatch. The remaining audit debt stays
in the turn angle/interior orientation schedule.

2026-07-04 retained interior-loop schedule: switched the nonlinear body to the
recovered negative one-turn angle, count-derived radius, native-style
half-angle/full-angle/Y/roll trig order, and primary `basis_forward` /
`basis_right` construction before copying the secondary lane. Focused Wibo moves
from 23.92% (592/687) to 27.22% (628/687), with masked operands improving from
24 ok, 0 unresolved, 5 mismatch to 38 ok, 0 unresolved, 1 mismatch. Retesting
the prologue-radius lifetime clears the masked audit at 37 ok, 0 unresolved,
0 mismatch, but lowers focused Wibo to 26.62%, so the retained source keeps the
loop-local radius spelling for now.

2026-07-13 terminal ownership: replacing `primary_last` and `secondary_last`
aliases with direct count-relative stores through the two `Path` sample arrays
moves focused Wibo from 27.22% (628/687) to 28.27% (636/687). The masked
audit remains 38 ok, 0 unresolved, 1 mismatch; its sole constant-alignment
residual is unchanged. The constructor keeps its local delta-loop pointers and
loop-local radius schedule.

2026-07-13 interior lane ownership: the native oriented-sample copy is exactly
the 0x40-byte `TransformMatrix`; fields at `+0x90..+0xa4` are not secondary
copies. Removing that scratch-only scalar traffic changes focused Wibo from
28.27% (636/687) to 27.77% (624/687), while the masked audit stays at 38 ok,
0 unresolved, 1 mismatch. The small fuzzy-score regression is retained as a
proved ownership correction rather than preserving non-native work for metric
alignment.

2026-07-15 coordinated sample ownership: replacing both helper-shaped straight
loops with direct primary/secondary arrays, separate logical Z counters, and
the target's do-loop bounds recovers the actual lateral endpoints. The lead-in
owns `-(width * 0.5 - 4.0)` while the exit owns
`-(4.0 - width * 0.5)`; the earlier isolated endpoint swap probe lacked the
native loop and lifetime context and therefore was not sufficient evidence.

The floating interior count now survives across allocation and the incoming
`turns` slot owns the derived radius. The curved body uses separate curve and
sample indices, reloads interpolation endpoints from the seeded sample fields,
preserves the repeated under-roll sine calls, constructs the forward/right
bases directly, and copies only the 0x40-byte transform into the secondary
lane. Together these changes move focused Wibo from 27.77% (624/687) to 48.06%
(628/687) and clear the last constant-alignment mismatch: all 41 masked
operands resolve cleanly. The face loop now clears `header_word`, matching the
target's 16-bit store.

Rejected: retaining an explicit `tail_start_index` across the tail and curved
loops reduced focused Wibo to 46.11% (623/687), with the operand audit still
clean. Although the target preserves a related byte offset, that source-level
lifetime does not reproduce it; keep the direct count-relative spelling.
