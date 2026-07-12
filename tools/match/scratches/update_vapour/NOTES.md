# update_vapour

First structured scratch for `update_vapour` @ `0x4425f0`.

Recovered relationships:

- `Vapour::half_width +0x88` is stored as raw bits by
  `initialize_vapour`, then used as a float width when expanding each point
  into a quad strip.
- `Vapour::z_floor +0x8c` is an optional `float*` clamp pointer, not a
  mode enum. When present, every point's `TransformMatrix::position.z` is
  clamped to `*z_floor`. The independent iOS symbol
  `cRVapour::ReSet(float*)` (`__ZN8cRVapour5ReSetEPf`) pins the pointer type.
- `Vapour::points +0x90` is a `TransformMatrix*`; each segment reads the
  current point's `basis_right` and current/next `position`.
- The retained owner at `+0x24` is the real shared `Object`/`cRObject`, not a
  trail-specific view. Every consumed field lands on the exact existing owner:
  `vertex_count +0x2c`, vertices `+0x38`, `facequad_count +0x54`, facequads and
  their UV words `+0x5c`, and `group_primitive_counts +0xd4`.

2026-07-11 complete owner extent: `Vapour` is exactly 0x94 bytes, ending
after `points +0x90`. The exact JetPack constructor builds two consecutive
instances at parent `+0x74` and `+0x108`, installs the same cRVapour table at
`0x49731c`, and closes the parent at `+0x19c`. This replaces two 0x78-byte
renderable views plus anonymous tail padding with complete embedded cRVapour
owners; all four existing vapour scratches remain byte-stable.

2026-07-12 authored contract closure: Android `cRVapour::AI()` returns directly
from both the hidden and emitted-strip paths without establishing a result, so
the varying Windows EAX residue is incidental. The scratch now uses the void
contract and real `Object*` output owner. Focused Windows code generation is
unchanged at the honest 28.50% baseline (180/227 instructions); the remaining
gap is the large native temporary/vector-copy schedule, not ownership evidence.
