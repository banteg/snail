# calc_object_facequad_normals_simple

First tracked scratch for `calc_object_facequad_normals_simple @ 0x430230`.

This helper is the lightweight face-normal rebuild used after object vertex
distortion. It:

- ensures `Object::facequad_normals` is allocated;
- walks the `ObjectFaceQuad` array with the native 0x30-byte face stride;
- builds one normalized cross-product normal from vertices `0, 1, 2`;
- for four-vertex quads, builds a second normalized cross-product normal from
  vertices `0, 1, 3`;
- writes two 12-byte normals per face into `Object +0x60`.

The scratch uses the shared `Object`, `ObjectFaceQuad`, and `Vector3` layouts.
It intentionally keeps the byte-offset loop for faces and output normals because
native also walks facequads by 0x30 bytes and normal pairs by 0x18 bytes.

The remaining mismatch is compiler shape, not unresolved behavior. Native keeps
`this` in `esi`, `face_offset` in `ebx`, `normal_offset` in `ebp`, and reserves a
0x58-byte stack frame with separate temporary float/vector lanes. The current
source-shaped scratch emits the same work through a tighter 0x44-byte frame and
different nonvolatile ownership. A trial that made the object owner explicit was
assembly-identical, so it was reverted.
