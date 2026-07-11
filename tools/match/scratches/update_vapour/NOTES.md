# update_vapour

First structured scratch for `update_vapour` @ `0x4425f0`.

Recovered relationships:

- `VapourTrail::half_width +0x88` is stored as raw bits by
  `initialize_vapour`, then used as a float width when expanding each point
  into a quad strip.
- `VapourTrail::z_floor +0x8c` is an optional `float*` clamp pointer, not a
  mode enum. When present, every point's `TransformMatrix::position.z` is
  clamped to `*z_floor`. The independent iOS symbol
  `cRVapour::ReSet(float*)` (`__ZN8cRVapour5ReSetEPf`) pins the pointer type.
- `VapourTrail::points +0x90` is a `TransformMatrix*`; each segment reads the
  current point's `basis_right` and current/next `position`.
- `VapourTrailOwner` owns the output buffers: `vertex_count +0x2c`, quad
  vertices at `+0x38`, attribute/UV words at `+0x5c`, and final index count
  through `+0xd4`.

2026-07-11 complete owner extent: `VapourTrail` is exactly 0x94 bytes, ending
after `points +0x90`. The exact JetPack constructor builds two consecutive
instances at parent `+0x74` and `+0x108`, installs the same cRVapour table at
`0x49731c`, and closes the parent at `+0x19c`. This replaces two 0x78-byte
renderable views plus anonymous tail padding with complete embedded cRVapour
owners; all four existing vapour scratches remain byte-stable.
