# initialize_directx_loader @ 0x405c90

Windows and the symbol-preserving ports identify this as the authored void
`cRDirectX::Init()` member. It initializes the root-owned `DirectXLoader` by
clearing the fixed-cache count, retaining the loaded `XAnimation.txt` bytes,
and allocating the duplicate-vertex workspace after the 128-slot cached-mesh
bank.

The exact containing layout is `0x5e10` bytes: `animation_bytes +0x00`,
`cached_x_mesh_count +0x04`, `CachedXMeshSlot[128] +0x08` with `0xbc` stride,
and authored `cRDuplicateVertices +0x5e08`. Its sole startup caller discards `eax`;
changing the former helper-pointer result to `void` preserves the proof-grade
`13/13` match with three clean masked operands.
