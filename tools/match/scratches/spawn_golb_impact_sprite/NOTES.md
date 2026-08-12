# cRSubGolb::Explode @ 0x415d80

Current recovery: semantic-complete (`compiler` residual), 63.64%, 43/45
candidate instructions, 3/45 prefix, and all three masked operands clean.

## Ownership and ABI

Android preserves the authored `cRSubGolb::Explode(tVector)` symbol and a body
with the same effect gate, owning-player slot, allocated Sprite, gameplay flag,
velocity, progress/lifetime, size, gravity, and copied position. The five live
Windows callers are all in `cRSubGolb::AI()` and pass one existing vector
pointer. The Windows function ends in `ret 4` and has the verified prototype
`void __thiscall cRSubGolb::Explode(tVector*)`; the mobile by-value signature is
a real platform ABI difference.

The impact Sprite deliberately keeps the allocator's `-1` object sentinel.
Unlike `Jet`, neither this helper nor any caller reads the shot-slot word at
`cRSubGolb +0x274` or writes `Sprite::object_ref`.

## Remaining compiler residual

The normalized diff is confined to allocator argument scheduling and
publication of a real 12-byte local `tVector`. Native VC6 saves `esi`, reuses it
for the zero velocity lanes, and splits the vector copy around the scalar
Sprite stores. The retained source expresses the proven behavior without
register coercion.

Recorded bounded probes cover normal constructor/assignment forms, scalar and
aggregate stores, owner-slot lifetimes, field orderings, and ordinary register
storage hints. None improves this baseline. A by-value Windows probe emits the
wrong `ret 0xc` and also damages `cRSubGolb::AI()`, so it is rejected. Further
matching work needs new Windows source-shape evidence rather than another ABI
or field-layout guess.
