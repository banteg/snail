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
