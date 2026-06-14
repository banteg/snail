# vector_magnitude @ 0x44ccf0

Near-exact match: 94.74%, 18/19 instructions.

This helper computes `sqrt(x*x + y*y + z*z)` through the shared `square_root`
wrapper. It is used by Golb spawn, track parcels, star-field entries, object
geometry helpers, and audio distance falloff.

Residual: the native cleanup after the `square_root` call is `add esp, 0x4`;
the same direct source shape compiles to `pop ecx`. Variants with an explicit
local squared value regress by introducing an early stack slot, so this scratch
is pinned at the one-instruction stack-cleanup spelling difference.
