# load_or_reuse_cached_x_mesh

- `this` is the cached mesh bank; `count` is at `+0x04`, and slots start at
  `+0x08` with a `0xbc` stride.
- Existing cached entries are compared by path string at slot `+0x3c`.
- Misses copy the mesh name into the next slot, attach a newly allocated object
  to the slot `BodBase`, then load the X mesh through the bank-local thiscall
  helper.
