# create_vertex_buffer @ 0x4114b0

Direct3DRenderer's fixed-pool vertex-buffer factory.

- The factory-owned pool slot is recovered as a 12-byte record: requested FVF
  at `+0x00`, one still-unknown dword, and the `IDirect3DVertexBuffer8*` at
  `+0x08`. The broad shared `ObjectRenderBuffers` keeps that prefix opaque
  because exposing the extra fields shifts VC6 local table labels in unrelated
  exact scratches; this owner uses the proven narrow overlay.
- FVF `2`, `0x102`, and `0x142` select 12-, 20-, and 24-byte vertex strides;
  all use D3D usage `8` and pool `1`.
- The function preserves native HRESULT diagnostics and the deliberate infinite
  trap after reporting that the 3000-slot vertex-buffer pool overflowed.

Focused result: 76.68%, 92 candidate instructions versus 101 target, with all
10 masked operands resolved. Native emits three complete D3D call blocks in
descending physical case order; VC6 tail-merges the shared call suffix in the
recovered switch source. Explicit case `goto`s produce the same merge, so the
remaining nine-instruction delta is kept as compiler-layout debt rather than
being forced with volatile state or duplicate fake helpers.
