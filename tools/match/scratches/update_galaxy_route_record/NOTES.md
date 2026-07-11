# update_galaxy_route_record @ 0x409bd0

Exact route-slot tint interpolator. The receiver is the real `0x2a0`-byte
`GalaxyRouteSlot` beginning at `GalaxyRoute +0x10 + index * 0x2a0`:

- slot `+0x18` is the live route tint alpha;
- slot `+0x1c` is its highlight target;
- each update advances the live value by 10% of the remaining difference.

These offsets independently prove the four-byte slot prefix before the
`GalaxyRouteRecord` body at slot `+0x04`.
