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

## 2026-07-17 live constructor ABI closure

The restarted Binary Ninja session and the tail at `0x428987` confirm the
native `retn 0x18` contract: `Path* self`, `float turns`, integer width and
side-exit mode, two surface textures, and the Windows-only vertical texture.
This agrees with the portable iOS
`cRPath::BuildTurnunder(float, int, bool, char*, char*)` prefix. The stale
database prototype stopped after two textures and mislabeled the final known
stack slot, leaving the vertical texture absent.

Guarded recreation and post-write readback now report the exact seven-parameter
prototype with no pending operation. The refreshed caller passes all six stack
operands through `path_pairs[0x27].primary`, and the callee exposes `Path`
fields plus void finalizer flow. This is analysis-only: focused matching remains
48.06% (628/687) with 41 clean masked operands.

## 2026-07-20 live lifetime ownership

A guarded transaction proves nine complete live owners: the primary seed and
mesh samples, primary up vector, secondary position, both terminal deltas, mesh
vertex, and the two face records. Their fields now render directly through
`PathTemplateSample`, `Vec3`, and `ObjectFaceQuad`, with no `__offset`
expressions. Unlike its turnover siblings, this constructor already expresses
the curved-body sample through typed base arithmetic and needs no additional
cursor view. Focused matching remains 48.06% (628/687) with 41 clean masked
operands.

## 2026-07-25 mesh-vector ownership

Raw native assembly at `0x428650..0x42872d` proves the same branch-local mesh
owners recovered in the Invert and SBend constructors. The row-terminal test
belongs inside the column loop. Ordinary rows materialize one generated
position, while the terminal row owns a previous-sample lateral-offset vector
and a second generated position whose Z lane includes `+1.0f`.

Recovering that source shape raises focused matching from 48.06% (628/687) to
48.15% (663/687), bringing the candidate instruction count substantially
closer to the target. All 41 masked operands remain clean, with no unresolved
or mismatched masks. The remaining candidate `0x3c` versus native `0x54` stack
frame gap belongs to other constructor lifetimes.

## 2026-07-26 complete mesh-vector ownership

The Turnover sibling recovery identifies the two aggregate owners that the
initial Turnunder rewrite still collapsed. At `0x428650..0x42872d`, the ordinary
branch first owns a lateral-offset vector before its generated position. The
terminal branch reaches the previous sample through the current row cursor and
separately owns an endpoint vector whose Z lane is extended by `1.0f`.

Adding those owners completes the four-vector mesh model. Focused matching
rises from 48.15% (663/687) to 50.55% (670/687), the masked audit improves from
41 to 42 clean operands with no unresolved or mismatched masks, and the
candidate now uses the exact native `0x54` frame with a six-instruction exact
prefix. The earlier `0x3c` frame gap was therefore mesh-vector ownership, not a
separate constructor lifetime.

## 2026-07-27 paired mobile boolean ownership

Exact Android and iOS symbols agree on
`cRPath::BuildTurnunder(float, int, bool, char*, char*)`, proving
`bool side_exit` rather than an integer mode. Both portable bodies end at
`CalcLengthZ`; Windows keeps its additional vertical texture and local mesh
builder. The shared declaration, replay tooling, and live Binary Ninja
prototype now encode that platform split. The scalar refinement is
byte-neutral: focused matching remains 50.55% (670/687), with a six-instruction
prefix and 45 clean masked operands.

## 2026-07-28 paired-mobile control ownership

The exact Android and iOS bodies independently preserve the six-sample lead,
two-sample tail, curved body beginning at sample 6, separate curve/sample and
delta/sample cursors, count-derived radius, transform-only secondary copy, and
final `CalcLengthZ` traversal. Windows SSA independently proves the corresponding
native stack definitions, including `curve_count`, `curve_count_f`, the
`curve_count + 8` total, logical indices, byte offsets, and the negative
one-turn `angle`. Mobile evidence supplies source shape only; the Windows ABI,
storage, and mesh tail remain authoritative and unchanged.

The guarded replay now persists those conflict-free lifetimes and is
idempotent on a second run. The refreshed Binary Ninja decompile renders the
owners without `__offset` artifacts. IDA 9.4 also replaces the stale tracked
five-argument `PathTemplate*`/`int32_t` export with the recovered seven-argument
`Path*`/`void` Windows signature and current object/mesh types. This
analysis-only recovery leaves focused matching at 50.55% (670/687), with a
six-instruction prefix and 45 clean masked operands.
