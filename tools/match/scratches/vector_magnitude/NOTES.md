# vector_magnitude @ 0x44ccf0

Exact match: 100.00%, 19/19 instructions, with one masked operand resolved.

This helper computes `sqrt(x*x + y*y + z*z)` through the shared `square_root`
wrapper. It is used by Golb spawn, track parcels, star-field entries, object
geometry helpers, and audio distance falloff.

The exact source shape keeps the `square_root` result in a named local before
returning it. Returning the call directly compiles to an equivalent `pop ecx`
cleanup, while native uses `add esp, 0x4`.

2026-07-14 owner pass: iOS and Android both export
`tVector::Magnitude() const`, and the Windows body only reads its ECX receiver.
The shared source and analysis declarations now preserve that const receiver
and float return while remaining exact at 19/19 with its one operand clean.
