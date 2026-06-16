# vector_magnitude @ 0x44ccf0

Exact match: 100.00%, 19/19 instructions, with one masked operand resolved.

This helper computes `sqrt(x*x + y*y + z*z)` through the shared `square_root`
wrapper. It is used by Golb spawn, track parcels, star-field entries, object
geometry helpers, and audio distance falloff.

The exact source shape keeps the `square_root` result in a named local before
returning it. Returning the call directly compiles to an equivalent `pop ecx`
cleanup, while native uses `add esp, 0x4`.
