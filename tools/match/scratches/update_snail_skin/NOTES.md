# update_snail_skin @ 0x445cd0

First tracked scratch for the snail hotspot rebuild loop. This promotes the
cross-confirmed presentation hotspot fields:

- `snail_hotspot_source_matrix_a` at `+0x1604`;
- `snail_hotspot_source_matrix_b` at `+0x1684`;
- `snail_hotspots_local[19]` at `+0x16cc`;
- `snail_hotspots_world[19]` at `+0x17b0`.

Recovered behavior: each tick transforms the 19 local hotspots into world
space. Slots `0..10` use source matrix B; slots `11..18` use source matrix A.
The world bank feeds `update_cutscene`, including the known camera anchors
`CameraSkidStop` at slot `12`, `CameraSlugDeath` at slot `17`, and
`CameraIntroTalk` at slot `18`.

Focused Wibo result: 57.47%, 43/44 candidate/target instructions. The by-value
`TransformMatrix` argument preserves the native `0x40`-byte stack copy before
`multiply_vector_by_matrix`. Remaining drift is mostly register ownership:
native keeps the loop index in `ebx` and the world-hotspot cursor in `ebp`;
this source keeps those reversed. A `register` index hint and declaration-order
probe did not improve the score, so keep the clear source until a stronger VC6
idiom explains the split.
