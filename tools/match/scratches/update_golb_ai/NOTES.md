# cRSubGolb::AI @ 0x414820

Authored void `cRSubGolb::AI()` over one live 0x2e8-byte projectile owner.
Windows installs this entry in the shot callback table; Binary Ninja confirms
a no-argument `__thiscall`. Android and iOS each retain one complete
`cRSubGolb::AI()` body in `Golb.o`.

The method covers pause/live gates, straight and path-follow motion, homing,
the Sprite/Vapour/rocket presentation families, lifetime and bounds teardown,
garbage and slug collision trees, bounce, splash, wall impact, and the exact
`Kill`, `Jet`, `Smoke`, and `Explode` children. The 12-slot bank index is read
only by the kind-zero trail path and becomes each trail Sprite's opaque object
reference; impact sprites deliberately retain the allocator sentinel.

The scratch exports `?AI@cRSubGolb@@QAEXXZ`. It is semantic-complete at
91.56%, 693/694 instructions, prefix 9, with all 71 references clean. Sixteen
recorded bounded sweeps cover 130 variants. Remaining differences are
equivalent VC6 register ownership, branch layout, and collision-temporary
scheduling; the tempting persistent collision-side carrier is behaviorally
wrong and is not retained.
