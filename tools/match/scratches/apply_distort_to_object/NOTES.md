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

- 95.43% instruction match, 197 target insns vs. 197 candidate insns, up from
  52.15% and 198 candidate instructions.
- Masked operands: 26 ok, 0 unresolved, 0 mismatch.
- Native repeatedly loads each bound before and after its x87 comparison and
  reloads the selected bound after the max comparison. That is the VC6 shape
  of expanded `ABS_FLOAT` and `MAX_FLOAT` expressions, not stored min/max
  temporaries.
- The Z-envelope pass copies through the chained `source` view, but its
  absolute-Z input reloads `object->vertices`. Expressing that owner distinction
  recovers the native induction registers and exact instruction count.
- All three passes use direct indexed writes into `copied_vertices`; removing
  synthetic per-iteration `in`/`out` pointers and phase locals recovers the
  native loop scheduling.
- The final pass is positively guarded by `xyz_scale != 0.0f`, with the
  no-distortion return in the `else` arm. This reproduces the native fallthrough
  and post-pass jump.
- The remaining nine differing instructions are only equivalent base/index
  orderings in scale-1 x86 SIB addresses. No ownership, control-flow, call, or
  data-flow mismatch remains, so the source deliberately avoids artificial
  pointer arithmetic to choose an encoding.
- 2026-06-21 owner-local retry: adding an explicit `ObjectDistort* self = this`
  and reading all three distort fields through it is codegen-neutral at 52.15%.
  VC6 still anchors `this` in `ebp` instead of native `edi`; a simple owner
  name does not free `ebp` for the loop/index role.
