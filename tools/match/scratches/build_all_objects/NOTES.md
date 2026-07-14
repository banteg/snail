# build_all_objects

ObjectList build pass at `0x42f9e0`.

- Confirms `build_all_objects` is an `ObjectList` method, not a free helper
  taking IDA's synthetic `edi`/`st0` parameters.
- Walks `ObjectList::objects` with the established `0xdc` stride and skips
  objects with zero `vertex_count`.
- Proves the build order: bounding box, texture-ref sort, texture-group
  calculation, optional toon normals/edges for `OBJECT_FLAG_TOON_ENABLED`,
  then the cdecl D3D texture-group buffer build.

2026-07-10 global-owner closure: `g_object_list` is now a typed `ObjectList`
data variable in Binary Ninja. This exact method proves that the list owns one
contiguous `Object[capacity]` allocation and lends each `0xdc` slot to the
builder. The builder's corrected `void(Object*)` prototype makes the ownership
handoff explicit. Focused Wibo remains exact at 100%, 54/54, with eight clean
masked operands.
