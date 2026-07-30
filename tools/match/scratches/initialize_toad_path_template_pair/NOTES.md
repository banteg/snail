# initialize_toad_path_template_pair

Starter reconstruction for `initialize_toad_path_template_pair @ 0x42cbf0`.

Captures the branch-dependent lead/exit counts, fixed width `4`, 26-sample turn
arc, Z-rotation by the recovered turn angle, secondary offsets, delta
recomputation, strip mesh generation, and finalization.

The scratch is an honest partial. The remaining gaps are the exact local/stack
shape and mesh-tail scheduling.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 9.55% (175/663
candidate/target instructions) to 19.25% (594/663), with masked operands
improving from 5 ok, 0 unresolved, 8 mismatch to 16 ok, 0 unresolved, 3
mismatch.

2026-07-03 angle-order split: spelling the turn angle as a separate `0.5f`
multiply before applying the branch sign and quarter-turn scale moves focused
Wibo to 19.40% (595/663), with masked operands improving to 18 ok, 0
unresolved, 2 mismatch. A neutral-sample/writeback probe raised the operand
count but reduced fuzzy score to 19.26%, so it was left out.

2026-07-03 parameter-width pass: focused head diff showed the native
constructor reads the branch selector as a byte (`mov al, [esp+4]`), while the
scratch declared it as an `int`. Narrowing the shared declaration and scratch
signature to `char turn_left` moves focused Wibo to 19.71% (595/663), exposes a
1-instruction prefix, and leaves masked operands unchanged at 18 ok, 0
unresolved, 2 mismatch. The remaining focused residual is stack-frame and
interior orientation/copy scheduling, not call ABI width.

2026-07-03 sample-scalar retry after ABI cleanup: after narrowing the branch
selector to `char`, removing the scratch-only `lateral_source` writes from the
primary initializer and secondary copy now improves focused Wibo from 19.71%
(595/663) to 19.79% (590/663). The 1-instruction prefix and masked audit stay
at 18 ok, 0 unresolved, 2 mismatch, so this is a small source-shape win while
the interior orientation/copy scheduling residual remains.

2026-07-03 secondary-flat scalar probe: removing the remaining flat secondary
`lateral_source` copy improved the masked audit to 18 ok, 0 unresolved, 1
mismatch, but regressed focused Wibo to 19.70% (586/663). Left out to preserve
the retained 19.79% source shape until the flat seed loop is rebuilt more
substantially.

2026-07-03 retained mesh-face loop: replacing the direct `a`/`b` face writes
with the two-texture `face_index` loop moves focused Wibo from 19.79% (590/663)
to 25.97% (600/663). The 1-instruction prefix is preserved and masked operands
improve from 18 ok, 0 unresolved, 2 mismatch to 22 ok, 0 unresolved,
2 mismatch. The remaining audit debt stays in the interior orientation/copy
schedule.

2026-07-13 terminal ownership: replacing `primary_last` and `secondary_last`
aliases with direct count-relative stores through the two `Path` sample arrays
moves focused Wibo from 25.97% (600/663) to 27.69% (608/663). The
1-instruction prefix is preserved and the masked audit remains 22 ok,
0 unresolved, 2 mismatch; both pre-existing interior orientation residuals are
unchanged. The delta loop retains its local sample pointers.

2026-07-13 interior lane ownership: the native post-orientation copy is a
0x40-byte `TransformMatrix` copy, so `center_x`, rotation, lateral-scale, and
special scalars remain primary-owned. Removing those non-native secondary
copies moves focused Wibo from 27.69% (608/663) to 27.94% (597/663). The
1-instruction prefix and masked audit remain unchanged at 22 ok, 0 unresolved,
2 mismatch.

2026-07-15 lane and interior ownership: the native flat secondary samples own
only their transform and `delta_length`; their X comes from the primary
`center_x`, Y is the authored constant `0.49000001f`, and Z shares the loop's
converted logical index. Rebuilding both flat loops around those direct array
writes, then spelling the 26-sample interior in native order, recovers the
primary-only scalar initialization, identity-before-sine schedule, local-Z
rotation, 0x40-byte transform copy, and basis-up offset. Focused Wibo rises
from 27.94% (597/663) to 45.89% (601/663), while the masked audit improves from
22 ok / 2 mismatch to 27 ok / 0 mismatch. A direct-array rewrite of the delta
loop regressed to 41.35%, so its better local sample-pointer shape remains.

2026-07-17 owner and ABI closure: the Windows body ends in `ret 0x10`, and all
four asset-constructor callsites push the turn selector plus three textures
after `this`. The previous Binary Ninja prototype left the fourth texture as an
unpromoted stack local, kept the receiver on the legacy partial `PathTemplate`,
and inferred an `int32_t` result from register residue. Guarded recreation now
records `void __thiscall(Path* self, char turn_left, char* texture_a, char*
texture_b, char* vertical_texture)`, and the tracked caller renders the complete
ABI including `Objects/Path/VeryDark.tga`. The matcher source already carried
that honest declaration, so focused Wibo remains **45.89%** (601/663), with its
1-instruction prefix and clean 27-operand masked audit unchanged.

## 2026-07-20 live lifetime ownership

A guarded Binary Ninja transaction now preserves eight complete live owners:
the interior primary right vector, secondary position, both terminal deltas,
the mesh sample and vertex, and both face records. Their accesses render
through `Vec3`, `PathTemplateSample`, and `ObjectFaceQuad` with zero residual
`__offset` expressions. Focused matching remains 45.89% (601/663), with its
1-instruction prefix and 27 clean masked operands.

## 2026-07-25 mesh-vector ownership

Raw native assembly at `0x42d222..0x42d2ff` proves that the row-terminal test
belongs inside the vertex column loop. Ordinary rows materialize one complete
generated-position vector. The terminal row separately owns a previous-sample
lateral-offset vector and a generated-position vector whose Z lane includes
`+1.0f`, matching the same source boundary recovered in SBend, Invert, and
Turnunder.

Recovering that proven source shape moves the candidate instruction count from
601 to 628 against the 663-instruction target. It regresses the global fuzzy
alignment from 45.89% to 44.15% and leaves 25 rather than 27 aligned masked
operands; all remaining masks are clean, with no unresolved or mismatched
operands. The ownership correction is retained despite the score regression:
the affected native region directly proves the aggregate temporaries, while
the lost alignment is downstream compiler scheduling rather than contrary
source evidence.

## 2026-07-26 complete mesh-vector ownership

The completed family model identifies the two owners missing from the first
Toad rewrite. Native `0x42d231..0x42d2ff` first materializes an ordinary-row
lateral-offset vector before the generated position. The terminal branch
separately owns an endpoint reached from the previous sample through the
current row cursor, with its Z lane extended by `1.0f`.

Adding those owners resolves the earlier scheduling regression: focused
matching rises from 44.15% (628/663) to 47.92% (635/663), restores the masked
audit from 25 to 27 clean operands with no unresolved or mismatched masks, and
recovers the exact native `0x54` frame. The exact prefix expands from one to 15
instructions. The face initializer now also names the owning 16-bit
`header_word` proven by the native word clear; that field-width correction is
score-neutral.

## 2026-07-26 portable selector type

Android and iOS independently export the exact mangled
`cRPath::BuildToad(bool, char*, char*)` symbol. That resolves the Windows
selector's previously known one-byte storage width from generic `char` to the
authored `bool turn_left` type. The Windows-only fourth stack argument remains
`vertical_texture`: native `ret 0x10` cleanup and all four world-initializer
callsites prove it, while the mobile builders stop before the Windows strip-mesh
tail and therefore expose only the portable two-texture surface.

The matcher declaration, authoritative analysis header, and Binary Ninja/IDA
replay specifications now agree on the boolean selector. VC6 emits the same
47.92% candidate (635/663), with its 15-instruction prefix and 33 clean masked
operands, so this is an ownership correction rather than a score claim.

## 2026-07-28 mobile-authored phase and control ownership

Both mobile `cRPath::BuildToad` bodies preserve the authored curved-section
phase as `k * 6.2831855f / 26.0f` and the turn angle as
`(1 - cos(phase)) * 0.5f * turn_sign * 3.1415927f * 0.5f`. Restoring that
hierarchy in the Windows scratch is byte-identical: VC6 folds it to the same
`0.241660982f` and `1.57079637f` operands, retaining the honest 47.92% result,
635/663 instructions, 15-instruction prefix, and all 33 masked operands clean.

The two ports also corroborate the Windows branch-selected lead count, tail
count, starting X, and turn sign. Binary Ninja had inferred the lead-count
stack lifetime as `PathTemplateSample*`, which turned integer additions into
false matrix-field expressions. The guarded replay now pins those four scalar
owners, splits the void `get_path_nodes` call clobber away from the later
lead-count bound, and separately splits the genuine primary-sample-bank reload
used by the curved secondary-position offset. Readback keeps `get_path_nodes`
void, exposes `lead_count`, `tail_count`, `start_x`, `turn_sign`, and
`lead_count_bound` as scalars, and retains `primary_sample_bank` as a borrowed
`PathTemplateSample*` only for its real lifetime. No mobile layout or
Windows-only mesh-tail statement is transferred.

## 2026-07-30 terminal-delta array-owner bound

The exact terminal-delta helper shape also appears in the Twister family, so
the same one-site plan exhaustively tests direct arrays, separately scoped
pointer pairs, and separately scoped references. The two scoped forms compile
byte-identically to the retained source. Direct arrays lose 68.41 weighted
bytes and fall from 47.92% to **45.09%**, while moving the candidate from 635
to 641 instructions; the 15-instruction prefix and all 33 references remain
clean. Toad therefore retains its loop-wide pointer owners.

## 2026-07-30 secondary terminal-delta expression ownership

Keeping the proven loop-wide pointer owners while applying
`Vector3::operator-` only to the secondary delta adds 66.15 weighted bytes and
raises focused matching from 47.92% to **50.65%**. The candidate moves from
635 to 636 instructions against 663; prefix 15/663 and all 33 clean references
are unchanged. Applying the operator only to primary gains 51.01 bytes, while
applying it to both gains 47.37 bytes.

The source asymmetry is retained narrowly rather than generalized. Android and
iOS independently corroborate the two component subtractions but cannot expose
the inlined C++ spelling. On Windows, localized diffing shows the secondary
operator improves the delta-loop region itself: the former 37-instruction
mismatch splits into a better 32-instruction region and a 50%-matching tail.
Scoped and unscoped pointer forms emit the same bytes, while all three
direct-array/operator interactions repeat the prior 68.41-byte regression.

## 2026-07-30 orientation subtraction bound

The primary current/previous orientation operator loses 59.46 weighted bytes
and falls to 48.20%, while preserving the 15-instruction prefix and all 33
clean references. Toad keeps the expanded component constructor and the
independently retained secondary terminal-delta operator.
