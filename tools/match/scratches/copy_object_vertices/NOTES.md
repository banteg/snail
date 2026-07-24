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

## 2026-07-23 element-borrow lifetime replay

The guarded vertex-storage replay now distinguishes the integer
`vertex_byte_offset` from the completed `Vec3* source_vertex` and
`Vec3* copied_vertex` borrows. Binary Ninja consequently renders the native
three-dword transfer as the real component copy:

`copied_vertex->{x,y,z} = source_vertex->{x,y,z}`.

The replay verifies `Vec3` at 0x0c, `Object` at 0xdc, and the
`vertex_count`/`vertices`/`copied_vertices` fields before mutation, saves and
reads back every annotation, and is fully idempotent. The exact matcher source
remains unchanged at 100.00%, 28/28 instructions, prefix 28/28, with no masked
operands.

## 2026-07-24 paired IDA ownership replay

The object-render replay now applies the same exact
`void __thiscall copy_object_vertices(Object*)` ABI to the tracked IDA
database. IDA consequently resolves the source and destination as the canonical
Object-owned `Vec3* vertices` and `Vec3* copied_vertices` banks and renders the
three component assignments directly. This retires the stale
`unsigned int* this` view and its fake integer return without changing the
already-exact matcher source.
