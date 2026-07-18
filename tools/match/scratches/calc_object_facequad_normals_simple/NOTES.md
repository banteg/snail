# calc_object_facequad_normals_simple

Exact scratch for `calc_object_facequad_normals_simple @ 0x430230`.

This helper is the lightweight face-normal rebuild used after object vertex
distortion. It:

- ensures `Object::facequad_normals` is allocated;
- walks the `ObjectFaceQuad` array with the native 0x30-byte face stride;
- builds one normalized cross-product normal from vertices `0, 1, 2`;
- for four-vertex quads, builds a second normalized cross-product normal from
  vertices `0, 1, 3`;
- writes two 12-byte normals per face into `Object +0x60`.

The fourth-corner branch is now spelled through
`OBJECT_FACEQUAD_FLAG_TRIANGLE`, whose X-loader producer and independent
normal/edge/index consumers close the bit's ownership.

The scratch uses the shared `Object`, `ObjectFaceQuad`, and `Vector3` layouts.
It intentionally keeps the byte-offset loop for faces and output normals because
native also walks facequads by 0x30 bytes and normal pairs by 0x18 bytes.

2026-07-10 exact recovery: each vertex subtraction owns a temporary `Vector3`
value which is then copied into the persistent `lhs` or `rhs` operand used by
`cross_vectors`; the quad path replaces only `rhs`. The face and output-normal
pointers are deliberately not retained across calls: source expressions reload
`facequads + face_offset` and independently address
`facequad_normals + normal_offset`. Those ownership choices naturally recover
the native 0x58-byte frame, `this` in `esi`, face offset in `ebx`, and normal
offset in `ebp`.

Focused Wibo is 100.00%, 139/139 instructions and full prefix, with five clean
masked operands and no unresolved or mismatched operands.

2026-07-18 analyzer replay closure: the object-topology replay now owns this
helper's `int __thiscall(Object*)` boundary alongside the full normal and edge
builders. IDA recovers indexed `ObjectFaceQuad` inputs and the two `Vec3`
normal slots per face; Binary Ninja recovers the canonical object fields while
honestly preserving the native byte-offset face walk. Both lanes retain the
real `Object` owner and the exact scratch remains 139/139 with five clean
operands.
