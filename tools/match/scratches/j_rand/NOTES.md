# j_rand @ 0x44c920

Game-code jump thunk to the statically linked CRT `rand` body at `0x48bfe5`.
Exact `random_signed_float_below` and `random_float_below` both call this thunk,
while the startup random-table initializer calls the CRT body directly.

## 2026-08-12 source-unit provenance

Both callers are verified `RMaths.o` functions, and the thunk is physically
bounded by verified `next_math_random_value` and
`initialize_trigonometry_tables` from that same unit. Live xrefs find no other
caller. This recovers `RMaths.o` without treating the CRT body itself as game
source.
