# apply_object_toon

Object toon setup at `0x42fa80`.

- Confirms `Object +0x08` is the toon vertex storage allocated at
  `12 * vertex_count`.
- Confirms `Object +0x0c` is the toon facequad-normal support storage allocated
  at `24 * facequad_count`.
- Marks toon support with caller flags plus `0x4001`; the later build pass uses
  `0x4000` to decide whether to generate normals, edges, and the toon index
  buffer.
