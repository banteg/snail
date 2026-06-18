# copy_object_vertices

Copies the source object vertex array at `Object +0x38` into the copied-vertex
array at `Object +0x3c`, using the signed vertex count at `Object +0x2c`.

The helper is modeled as `void`: the native fallthrough leaves either the
non-positive vertex count or the final byte offset in `eax`, which is leftover
register state rather than a coherent API result.

2026-06-18 probe: the readable indexed member source is the best source-shaped
attempt so far at 47.27% with prefix 3/28. The compiler-shaped pointer/offset
loop from the decompiler note did compile once the shared declaration was made
`void`, but VC6 chose `edi` for the loop index and regressed to 28.07%. Keeping
the readable form documents the true semantics while leaving the remaining
register/base-reload scheduling as residual debt.
