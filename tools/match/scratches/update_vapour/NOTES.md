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

## 2026-07-12 exact AI recovery

Android `cRVapour::AI()` returns directly from both the hidden and emitted-strip
paths without establishing a semantic result, and neighboring empty AI methods
also leave their receiver in the return register. The varying Windows EAX value
is therefore incidental; the exact scratch retains the authored `void` virtual
contract and real borrowed `Object*` output owner.

The remaining Windows source shape is now recovered:

- An inlined component-wise vector addition joins the already recovered
  `Vector3::operator*`. Four direct expressions over `points[segment]` reproduce
  the native 0x60-byte temporary frame and its complete copy schedule.
- The owner consumes four ordinary `Object::vertices` entries per segment.
  Removing the synthetic retained point pointer and quad-vertex owner view lets
  the compiler reproduce native's independent point reloads and confirms that
  the storage remains the shared `Vector3*` array.
- The optional floor clamp uses a direct pointer to
  `points[index].position.z`, matching the native strength-reduced 0x40-byte
  transform walk.
- The authored UV cases are separate two-point, first-segment, last-segment,
  and interior branches. They map the facequad V coordinates to 0 at the strip
  start, 0.5 at internal joins, and 1 at the strip end. This also corrects the
  earlier scratch's reversed last/interior assignments.
- A normal `for` loop shares the primitive-count tail and reproduces native's
  shrink-wrapped saved-register lifetime without any control-flow artifact.

Focused Windows result: **100.00%**, `227/227` candidate/target instructions,
full `227/227` prefix, and no masked operands.
