# create_vertex_buffer @ 0x4114b0

The renderer's embedded fixed-pool vertex-buffer factory.

- The factory-owned `ObjectRenderBuffers` slot is recovered as a 12-byte
  record: requested FVF at `+0x00`, one still-unknown dword at `+0x04`, and the
  `IDirect3DVertexBuffer8*` at `+0x08`. Those fields now live in the shared
  matching and decompiler views rather than a scratch-local overlay.
- The call is the real `IDirect3DDevice8::CreateVertexBuffer` vtable slot at
  `+0x5c`; the shared D3D8 device view now owns its five-argument signature.
- FVF `2`, `0x102`, and `0x142` select 12-, 20-, and 24-byte vertex strides;
  all use D3D usage `8` and pool `1`.
- The function preserves native HRESULT diagnostics and the deliberate infinite
  trap after reporting that the 3000-slot vertex-buffer pool overflowed.

2026-07-14 owner recovery: Binary Ninja's receiver, the exact callsites, and
the adjacent index-buffer factory agree that renderer `+0x0000..+0x8ca3` is a
complete `VertexBufferFactory`: a count followed by 3000 12-byte slots. The
next `IndexBufferFactory` begins at `+0x8ca4`, exactly
`4 + 3000 * sizeof(ObjectRenderBuffers)`. The method and all five callers now
use that embedded owner instead of flattening its fields onto
`Direct3DRenderer`.

Focused result: 76.68%, 92 candidate instructions versus 101 target, with all
10 masked operands resolved. Native emits three complete D3D call blocks in
descending physical case order. A plain `if`/`else if` probe emits 101
instructions and preserves all three complete calls, but uses literal `cmp`
dispatch; the recovered `switch` emits the native subtract ladder and
tail-merges nine instructions from the shared call suffix. Ordinary `break`s,
explicit case `goto`s, the real virtual-interface syntax, and VC6 RTM all keep
that merge. The residual is therefore bounded compiler-layout debt, not forced
with volatile state or byte-shaped dispatch arithmetic.

2026-07-15 replay closure: the manifest/source name `create_vertex_buffer` is
now canonical in both decompiler replay lanes. Binary Ninja readback confirms
the `VertexBufferFactory*` receiver and resolves every device access through
`g_direct3d_renderer.device`; direct callers now show the allocator rooted at
the renderer singleton instead of the older verbose resource-helper alias.
This is ownership/ABI recovery only: focused output remains 76.68% with all ten
masked operands clean.

2026-07-18 durable owner closure: the IDA replay now rejects any header unless
`ObjectRenderBuffers` is `0x0c`, `VertexBufferFactory` is `0x8ca4`, the adjacent
`IndexBufferFactory` is `0x2ee4`, and their enclosing `Direct3DRenderer` is
`0xbcc0`. The allocator, its exact index-buffer sibling, renderer
construction/teardown, and all direct allocation callers are reanalyzed as one
ownership boundary. IDA now has a tracked allocator artifact with the factory
receiver, embedded slot array, real device vtable call, and stable
`next_count` identity. Four tempting HRESULT/return-slot overrides were tested,
failed exact decompiler readback, and were removed rather than forced. Strict
dual-lane export passes all 760 health checks; matcher source and the honest
76.68% focused result are unchanged.

2026-07-19 lifetime closure: exact Binary Ninja SSA readback separates the
three-way `CreateVertexBuffer` HRESULT from the incoming vertex count as
`create_result`, then separates the post-allocation pool cursor as
`next_count`. The latter now visibly owns the count store, overflow comparison,
and returned 12-byte slot selection. These are register-lifetime annotations,
not new retained fields: guarded replay first verifies the canonical
`ObjectRenderBuffers`, `VertexBufferFactory`, and enclosing
`Direct3DRenderer.device` layouts. Attempts to type the unsplit out-pointer and
return expression did not survive exact user-variable readback and were
removed. Strict dual-lane export has zero mismatches, and health checks reject
the former false `vertex_count_1` and anonymous `edx_5` lifetimes. Matcher
source and the honest 76.68% focused result remain unchanged.
