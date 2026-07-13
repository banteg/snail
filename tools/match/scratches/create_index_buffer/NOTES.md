# create_index_buffer @ 0x4115d0

Embedded `IndexBufferFactory` allocator owned by `Direct3DRenderer + 0x8ca4`.

- Allocates `index_count * 2` bytes as 16-bit D3D indices with usage `0x28`,
  format `0x65`, and pool `1`.
- Stores the returned interface in the current four-byte slot, increments the
  fixed-pool count, reports the native 3000-slot overflow, and retains the
  original shared "Vertex Buffer Request fail" diagnostic for HRESULT failure.

Focused match is exact: 36/36 instructions with all five masked operands clean.
