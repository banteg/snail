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
