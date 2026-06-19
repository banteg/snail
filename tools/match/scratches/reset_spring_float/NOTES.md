# reset_spring_float

`reset_spring_float` is the tiny thiscall helper reached from
`initialize_subgoldy` at `0x43aa6c`. It clears the spring object at
`*(player + 0x29a8) + 0x80` before SubGoldy seeds the rest of its runtime state.

Boundary evidence:

- The helper starts at `0x41aa30`, immediately before `apply_distort_to_object`
  at `0x41aa50`.
- Native bytes zero five dwords on `ecx`: `+0x00`, `+0x10`, `+0x0c`, `+0x04`,
  and `+0x08`, then return.
- The adjacent `initialize_backdrop_tile_quad` matcher output remained
  unchanged after the split, so this scratch records a new proof-grade helper
  without claiming a tile-quad improvement.

Current focused result:

- match: 100.00%
- target/candidate instructions: 7 / 7
- prefix: 7 / 7
- masked operands: none
