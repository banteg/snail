# initialize_object_distort

`initialize_object_distort` is the tiny authored `cRDistort::Init` helper
reached from `initialize_subgoldy` at `0x43aa6c`. It clears the five-float
`Distort` embedded at `Player::presentation.object +0x80` before SubGoldy
seeds the rest of its runtime state.

Boundary evidence:

- The helper starts at `0x41aa30`, immediately before `apply_distort_to_object`
  at `0x41aa50`.
- Native bytes zero five dwords on `ecx`: `+0x00`, `+0x10`, `+0x0c`, `+0x04`,
  and `+0x08`, then return. The exact 0x14-byte extent closes against
  `Object::bounding_radius +0x94`.
- Android independently exports `cRDistort::Init`, clears the same five words,
  and calls it from `cRSubGoldy::Init` on the presentation object's embedded
  distort owner. iOS retains `cRDistort::Init` and `cRDistort::BuildMatrix`.
- The adjacent `initialize_backdrop_tile_quad` matcher output remained
  unchanged after the split, so this scratch records a new proof-grade helper
  without claiming a tile-quad improvement.

Current focused result:

- match: 100.00%
- target/candidate instructions: 7 / 7
- prefix: 7 / 7
- masked operands: none

2026-07-14 owner correction: the former `SpringFloat` identity was disproved by
the cross-port symbol and caller evidence. The shared `Distort` now owns
all five words, and `initialize_subgoldy` calls it through
`presentation.object->distort`. Focused Wibo remains exact at 7/7 instructions
with no masked operands.

2026-07-28 class identity closure: Android and iOS independently preserve the
exact `cRDistort` class name. Cross-port reads stop after the three leading
controls, so `+0x0c` and `+0x10` remain unnamed.

## 2026-07-29 primary cRDistort ownership

The matcher now uses `cRDistort` as the primary 0x14-byte type and emits this
exact body as `cRDistort::Init()`. `Distort` and `ObjectDistort` remain
compatibility typedefs for the repeatable Binary Ninja and IDA vocabularies.
Binary Ninja confirms the sole Windows call constructs the receiver as
`presentation.object + 0x80`; the authored name remains 7/7 instructions with
no masked operands.
