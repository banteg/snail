# copy_object_vertices

Copies the source object vertex array at `Object +0x38` into the copied-vertex
array at `Object +0x3c`, using the signed vertex count at `Object +0x2c`.

The helper is modeled as `void`: the native fallthrough leaves either the
non-positive vertex count or the final byte offset in `eax`, which is leftover
register state rather than a coherent API result.

2026-06-18 match: the high-level indexed whole-struct assignment
`copied_vertices[i] = vertices[i]` is the exact source shape. VC6 emits the
same byte-offset/index loop from that assignment, including the `eax` offset,
`edx` loop index, and three dword moves through `ebx`/`esi`.

The compiler-shaped pointer/offset loop from the decompiler note does compile
once the shared declaration is `void`, but VC6 pins the loop index in `edi` and
regresses to 28.07%. The note was right about the fake return and the 12-byte
vertex struct; explicit field stores are just not the matching source shape.

## 2026-07-15 retained-copy ownership replay

The exact `void Object::copy_object_vertices()` ABI is now shared across the
matcher and repeatable Binary Ninja sync. The refreshed decompile reads the
source `vertices` view and writes the Object-owned `copied_vertices` bank for
exactly `vertex_count` entries; the old untyped fastcall/`void*` view is gone.
Focused matching remains exact at 28/28 instructions.
