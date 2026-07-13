# update_snail_skin @ 0x445cd0

Exact Windows counterpart of Android `cRSnail::BuildHotSpots()`. The stable
Windows name predates cross-port ownership recovery; this promotes the
cross-confirmed Snail hotspot fields:

- `snail_hotspot_source_matrix_a` at `+0x1604`;
- `snail_hotspot_source_matrix_b` at `+0x1684`;
- `snail_hotspots_local[19]` at `+0x16cc`;
- `snail_hotspots_world[19]` at `+0x17b0`.

Recovered behavior: each tick transforms the 19 local hotspots into world
space. Slots `0..10` use source matrix B; slots `11..18` use source matrix A.
The world bank feeds `update_cutscene`, including the known camera anchors
`CameraSkidStop` at slot `12`, `CameraSlugDeath` at slot `17`, and
`CameraIntroTalk` at slot `18`.

2026-06-21 index-loop pass: rewriting the loop as a plain indexed transform
over `snail_hotspots_local[index]` into `snail_hotspots_world[index]` exact
matches the native function: 100.00%, 44/44 instructions, 44/44 prefix, and the
single masked operand clean. The index-driven source keeps the native loop
index in `ebx`, the world-hotspot cursor in `ebp`, and preserves the by-value
`TransformMatrix` stack copy before `multiply_vector_by_matrix`. Earlier
pointer-walk and dual-pointer forms either swapped `ebx`/`ebp` ownership or
changed the prologue.

2026-07-13 index-owner closure: the exact loop now uses
`SNAIL_HOTSPOT_COUNT` and switches source matrices at
`SNAIL_HOTSPOT_PARCEL_POINT`, the first body/camera anchor after the eleven
weapon hotspots. This is codegen-neutral and ties the transform-bank split to
the same authored texture ordering used by extraction and cutscene consumers.
