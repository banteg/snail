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

The scratch exports `?AI@cRSubGolb@@QAEXXZ`. Its current result is
93.01%, 693/694 instructions, prefix 9, with all 71 references clean.
The remaining differences include constant lifetimes through the garbage
collision branches and two floating-point operand orders. Their source shape
is still unresolved. The persistent collision-side carrier previously tested
is behaviorally wrong and is not retained.

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

## 2026-09-05 indexed slug loop and collision phases

Direct indexing through `game->slug_hazards.slots[m]` removes the raw byte
cursor, redundant logical counter, and offset enum. Calls reload the owned
slot through the live game field after Kill/Explode, as the native code does.
This recovers the native base-plus-offset addresses without introducing a
long-lived slot pointer. A named z difference before publishing the complete
slug delta restores its x87 compare without extra reloads. Separating garbage
normalization from the radius comparison restores the native FXCH and test.
Together these changes improve 91.72% to 93.01%, from 695/694 to 693/694
instructions, with 71 clean references and the unchanged 0x70 frame.

The existing owned `Normalize()` calls replace the scratch-only fastcall
compatibility declaration. Their isolated full normalized diff is identical
to the 91.72% baseline, so this is an ownership correction without a codegen
tradeoff. The retained combined diff independently reproduces the measured
93.01% result after formatting.

Three recipes record 25 compiling variants. The eight ownership/distance
combinations include the byte-neutral Normalize control; the nine vector
phase alternatives leave the best unchanged (constructing the deflection
vector, dropping flight borrows, or using a separate flight sum regresses);
the eight garbage-loop/exit alternatives leave the while/for cases neutral
and regress the guarded do/while cases. These do not prove that the remaining
constant or operand choices are exhausted. No shared vector implementation,
compiler flag, return contract, or artificial collision-side dependency changed.
