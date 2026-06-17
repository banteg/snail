# build_all_objects

ObjectList build pass at `0x42f9e0`.

- Confirms `build_all_objects` is an `ObjectList` method, not a free helper
  taking IDA's synthetic `edi`/`st0` parameters.
- Walks `ObjectList::objects` with the established `0xdc` stride and skips
  objects with zero `vertex_count`.
- Proves the build order: bounding box, texture-ref sort, texture-group
  calculation, optional toon normals/edges for `flags & 0x4000`, then the
  cdecl D3D texture-group buffer build.
