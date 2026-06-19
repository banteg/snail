# `update_galaxy` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.18% | **61.11%** |
| Target instructions | 566 | 566 |
| Candidate instructions | 1 | 550 |
| Common prefix | 0 / 566 | **6 / 566** |
| Masked operands | none | **34 clean, 9 unresolved, 0 mismatched** |

The retained candidate is sixteen instructions shorter than the target. The
unresolved operands are the global route limit `data_4df9b8` and the route
record tick helper at `0x409bd0`; there are no masked mismatches.

The first remaining mismatch is the no-op `Color4f` constructor receiver:

```text
target[6]    lea ecx, [esp+0x3c]
candidate[6] lea ecx, [esp+0x2c]
```

Both sides now use the native `0x3c` frame, but the two stack `Color4f` slots
are assigned in the opposite order.

## Accepted source-shape changes

- Modeled the opening `Color4f::noop_this_constructor` call and the second
  stack color used by the route-zero `set_color_rgba` path.
- Corrected the route-record tick call to a `thiscall` on the view at
  `this + 0x10`, stepping by the native `0x2a0` record stride.
- Kept the route icon loop's apparently unreachable `route_index == 0` branch;
  VC6 retains it and it recovers the native frame size.
- Added a slot-base route-record view so the icon pass addresses fields as
  `this + route_index * 0x2a0 + field`.
- Seeded the hover route sentinel as `-1` and reused the probe index from `1`,
  matching the native hover/highlight setup more closely.
- Renamed the route-limit global to the neighboring scratch convention
  `data_4df9b8`.

## Remaining work

- The primary/secondary `Color4f` stack slots are still reversed, keeping the
  common prefix at six instructions.
- The route-card connector and hit-test blocks still schedule x87 locals
  differently from native.
- The tail click handling prefers the current saved mouse-state pointer; a
  direct reload from `g_game_base + 0x28c` regressed the frame to `0x38`, so it
  was rejected.
- The `data_4df9b8` and `update_galaxy_route_record` operands need curated
  reference symbols before the mask audit can become fully clean.
