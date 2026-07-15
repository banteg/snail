# update_galaxy_route_record @ 0x409bd0

Exact route-slot tint interpolator. The receiver is the real `0x2a0`-byte
`GalaxyRouteSlot` beginning at `Galaxy +0x10 + index * 0x2a0`:

- slot `+0x18` is the live route tint alpha;
- slot `+0x1c` is its highlight target;
- each update advances the live value by 10% of the remaining difference.

These offsets independently prove the four-byte slot prefix before the
`GalaxyRouteRecord` body at slot `+0x04`.

## 2026-07-15 Binary Ninja lifecycle replay

The live database now names `0x409bd0` and types its receiver as
`GalaxyRouteSlot*`; the focused export therefore exposes both interpolation
fields without raw offsets. Matching remains exact at 6/6 with one clean
operand.
