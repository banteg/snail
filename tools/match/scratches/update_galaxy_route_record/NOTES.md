# update_galaxy_route_record @ 0x409bd0

Exact star-child tint interpolator. The receiver is the real `0x2a0`-byte
`GalaxyStar` beginning at `Galaxy +0x10 + index * 0x2a0`:

- slot `+0x18` is the live route tint alpha;
- slot `+0x1c` is its highlight target;
- each update advances the live value by 10% of the remaining difference.

These offsets independently prove the four-byte slot prefix before the
`GalaxyRouteRecord` body at slot `+0x04`.

## 2026-07-15 Binary Ninja lifecycle replay

The live database now names `0x409bd0` and types its receiver as
`GalaxyStar*`; the focused export therefore exposes both interpolation
fields without raw offsets. Matching remains exact at 6/6 with one clean
operand.

## 2026-07-28 mobile GalaxyStar ownership

Android retains this body as the named `cRGalaxyStar::AI()` member. Its entire
expression is the same child-relative update as Windows: live tint at `+0x18`
advances by `(target +0x1c - live +0x18) * 0.1`. The Android
`cRGalaxy::AI()` caller passes `this +0x204 + index * 0x2a0`, independently
proving both the child owner and its extent.

iOS has no standalone `cRGalaxyStar::AI()` export, but `cRGalaxy::AI()`
inlines the identical expression and advances by the same `0x2a0` stride.
Its other accesses place the route-name index, position vector, tint, target,
detail text, and description text at the same child-relative offsets as
Windows. This promotes the former structural `GalaxyRouteSlot` label to the
authored `GalaxyStar` class without assigning meaning to the still-unknown
leading dword. The Windows helper remains exact at 6/6; no source coercion was
needed.
