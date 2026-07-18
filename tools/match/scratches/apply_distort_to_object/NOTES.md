# apply_distort_to_object

`Object +0x80` is a five-float, 0x14-byte `ObjectDistort` subobject used only
when the object has dynamic vertex data (`flags & 0x800000` in
`refresh_object_vertex_buffer`). The first three floats are the recovered
controls below; the final two remain unknown.

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

## 2026-07-15 receiver replay

The repeatable Binary Ninja sync now records both real owners:
`ObjectDistort*` is the `this` receiver and `Object*` is the borrowed geometry
target. The refreshed artifact names all three distortion controls, the Object
bounds/live/copy views, and the final simple-normal rebuild. This replaces the
old `int(float*, float)` interpretation without changing the honest 95.43%
matcher frontier or its nine equivalent SIB base/index order residuals.

## 2026-07-18 checked-in IDA owner closure

The IDA replay now owns this helper by address as well as name, verifies the
0x14-byte `ObjectDistort` and 0xdc-byte `Object` layouts before applying the
prototype, and refreshes `refresh_object_vertex_buffer` as its sole caller.
The tracked IDA artifact now exposes all three distort controls, the borrowed
live vertex view, the owned copy buffer, bounds, and final normal rebuild.

No matcher source changed. Focused Wibo remains `95.43%`, exactly `197/197`
instructions with 26 clean masks; all residuals are still equivalent x86 SIB
base/index encodings rather than ownership or behavior differences.
