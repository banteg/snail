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

## 2026-09-05 borrowed slug slots and vector subtraction

The hazard scan now derives a typed `cRSlug*` from the owned slot bank and its
existing byte cursor. State and position are read through that owner, and the
separation uses the shared vector subtraction. This improves 91.56% to
**91.72%**, with 695/694 instructions, the same prefix of 9, and all 71
references clean. Instruction-count distance remains one. A higher-scoring
692-instruction alternative was rejected because its count distance worsens.

The scan still keeps a separate logical slug index and reloads the live game
owner at the calls that need it; it does not extend a cached owner across
Kill/Explode. Three distance-gate comparison spellings did not improve the
current result. Their VC6 output does not independently establish NaN source
semantics, and none is retained.

## 2026-09-05 paired projectile latch type diagnostics

The four `whole-projectile-latch-types-20260905-mutations.json` variants replay
the unchanged-header control and the skip/bounce/both boolean alternatives
used by CreateGolb. All retain 91.72%, 695/694 instructions, prefix 9, and
71 clean references. This does not establish a bool-versus-byte ownership
correction, so the shared header remains unchanged.
