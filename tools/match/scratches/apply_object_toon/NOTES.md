# apply_object_toon

Object toon setup at `0x42fa80`.

- Confirms `Object +0x08` is the toon vertex storage allocated at
  `12 * vertex_count`.
- Confirms `Object +0x0c` is the toon facequad-normal support storage allocated
  at `24 * facequad_count`.
- Marks toon support with caller flags plus `OBJECT_FLAG_TOON_ENABLED` and
  `OBJECT_FLAG_BUILD_TOON_EDGES`; the later build pass uses the first bit to
  generate normals and the toon index buffer, while `calc_object_edges`
  independently consumes the second as its edge-build gate.

2026-07-14 void ABI closure: every Windows callsite discards EAX, and the
cross-port owner is the side-effecting `cRObject::ApplyToon(int)` method. The
Windows tail happens to leave the second tracked allocation in EAX, but that
buffer is already retained by `Object::toon_facequad_normals`; it is not a
second ownership transfer. Modeling the method as `void` keeps the exact 24/24
instruction stream and all four masked operands clean.
