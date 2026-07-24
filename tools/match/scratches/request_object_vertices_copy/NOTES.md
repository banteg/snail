# request_object_vertices_copy @ 0x42f7d0

Allocates the Object-owned backup vertex array and copies the live `Vector3`
bank into it. The allocation now uses `vertex_count * sizeof(Vector3)` rather
than duplicating the 0xc-byte representation. Matching remains exact at 14/14
instructions with all three operands clean.

## 2026-07-15 retained-copy allocation replay

The helper's real `void Object::request_object_vertices_copy()` ABI is now
shared and replayed into Binary Ninja. Its artifact shows the Object retaining
the `vertex_count * sizeof(Vector3)` allocation in `copied_vertices` before
calling the exact copy helper; the former incidental `void*` return is removed.
Focused matching remains exact at 14/14 with all three operands clean.

## 2026-07-24 paired IDA ownership replay

The tracked IDA database now shares the exact void Object member ABI. Its
artifact resolves the allocation as the Object-owned `Vec3* copied_vertices`
bank and the tail call as `copy_object_vertices(object)`, retiring the raw
`unsigned int* this` view and fake integer return. Matching remains unchanged
at 14/14.
