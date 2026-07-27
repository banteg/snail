# random_float_below @ 0x44dc90

Exact match: 100.00%, 8/8 instructions.

Scales the CRT RNG stream by the caller's upper bound. The native call is
through the small `j_rand` thunk at `0x44c920`, which immediately jumps to the
CRT `rand` body at `0x48bfe5`.

## 2026-07-27 authored RAND contract

Android and iOS export this helper as `RAND(float, char*)`; both multiply a
15-bit random sample by `0.000030517578f` and then by the first argument.
Windows reaches the CRT `rand` implementation through `j_rand`, whose result
already has the same 15-bit range.

Windows callers also push the source/debug tag retained by the mobile symbol,
although the release helper never reads it. Restoring the two-argument
`float` contract is byte-identical at 8/8 instructions with both operands
clean. The canonical declaration now lives in `rmath_random.h`; migrating its
callers from divergent float/double and pointer/integer declarations preserves
every focused result, including all three exact hazard consumers.
