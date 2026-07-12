# load_or_reuse_cached_x_mesh

- `this` is the root-owned `DirectXLoader`, not a standalone overlapping cache
  object. Its cached-mesh count is at `+0x04`, and 128 slots start at `+0x08`
  with a `0xbc` stride.
- Existing cached entries are compared by path string at slot `+0x3c`.
- Misses copy the mesh name into the next slot, attach a newly allocated object
  to the slot `BodBase`, then load the X mesh through the loader's thiscall
  helper.
- The slot bank ends at loader `+0x5e08`, exactly where the independently
  proven `DuplicateVertexBuffer` begins; together they close the loader's
  `0x5e10`-byte extent through the next root owner.

2026-07-12 analysis promotion: `DirectXLoader`, `CachedXMeshSlot`, and the
duplicate-vertex types now live in the shared BN/IDA object slice. The four
loader-family prototypes use the authored `cRDirectX` receiver; in particular,
`load_x_mesh` is no longer mis-typed as a free stdcall over a partial path-mesh
view. This exact cache method remains `65/65` with six clean masked operands.
