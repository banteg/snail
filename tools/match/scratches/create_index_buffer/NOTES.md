# create_index_buffer @ 0x4115d0

Embedded `IndexBufferFactory` allocator owned by `Direct3DRenderer + 0x8ca4`.

- Allocates `index_count * 2` bytes as 16-bit D3D indices with usage `0x28`,
  format `0x65`, and pool `1`.
- Stores the returned interface in the current four-byte slot, increments the
  fixed-pool count, reports the native 3000-slot overflow, and retains the
  original shared "Vertex Buffer Request fail" diagnostic for HRESULT failure.

Focused match is exact: 36/36 instructions with all five masked operands clean.

2026-07-14 device ABI ownership: the call target is the canonical
`Direct3DDevice8*` global and vtable slot `+0x60`, directly after the shared
`CreateVertexBuffer` slot. The scratch-local `Direct3DIndexFactoryDevice` and
vtable were partial duplicates, not a distinct owner. `IndexBufferFactory`
continues to own the returned 3000 interface slots; the device only creates
each COM resource.

2026-07-15 replay closure: the function now replays under the canonical
`create_index_buffer` name, and live callers resolve its receiver as
`g_direct3d_renderer.index_buffer_factory`. The stale standalone symbol at
`0x5000fc` was removed with an exact-name, previewed mutation; readback resolves
that address to the enclosing `g_direct3d_renderer` data variable. The exact
36/36 match is unchanged.
