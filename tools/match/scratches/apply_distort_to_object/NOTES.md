# apply_distort_to_object

`Object +0x80` is a three-float `ObjectDistort` subobject used only when the
object has dynamic vertex data (`flags & 0x800000` in
`refresh_object_vertex_buffer`).

- `z_wave` offsets vertex Y from absolute Z with a sine envelope over the
  object's Z bounds.
- `y_squash` stretches X while squashing Y around `bounds_min.y`.
- `xyz_scale` grows X/Y slightly while squashing Z.

Every active pass writes into `copied_vertices`; later passes read from that
copy. If any pass ran, `vertices` is redirected to `copied_vertices` and the
simple face-quad normals are recomputed.

Current scratch status:

- 52.15% instruction match, 197 target insns vs. 198 candidate insns.
- Masked operands: 23 ok, 0 unresolved, 0 mismatch.
- Main remaining shape gap is compiler scheduling/register allocation in the
  float compare loops, not unresolved object layout.
