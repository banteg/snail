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

## 2026-07-23 contiguous object build ownership

The ObjectList lifecycle replay now ties every build stage back to the same
owned `Object* objects` allocation. Binary Ninja preserves the current
`Object*` borrow plus the typed sort, texture-group, toon-normal, edge, and
buffer-build receivers. The native loop still carries an integer
`object_byte_offset` and advances it by 0xdc; recomputed borrows may therefore
render as `&objects->_pad_00[object_byte_offset]`, which is honest
strength-reduced addressing rather than evidence for another pointer owner.

The guarded replay verifies the 0x0c `ObjectList`, 0xdc `Object`, list fields,
and the `Object::flags`/`vertex_count` consumers, and is fully idempotent. The
matcher remains unchanged at 100.00%, 54/54 instructions, prefix 54/54, with
eight clean masked operands.
