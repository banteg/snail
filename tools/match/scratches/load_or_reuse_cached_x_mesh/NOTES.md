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
