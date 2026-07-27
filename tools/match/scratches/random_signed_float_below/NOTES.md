# random_signed_float_below @ 0x44dc70

Exact match: 100.00%, 9/9 instructions.

Centers the CRT RNG stream around zero before scaling by the caller's upper
bound. Like `random_float_below`, the native call targets the `j_rand` thunk at
`0x44c920`, not the CRT body directly.

## 2026-07-27 authored SRAND contract

Android and iOS export this helper as `SRAND(float, char*)`; both subtract
`16384.0f` from a 15-bit random sample, multiply by `0.000061035156f`, and
scale by the first argument. Windows reaches the CRT `rand` implementation
through `j_rand`, whose result already has the same 15-bit range.

Windows callers also push the source/debug tag retained by the mobile symbol,
although the release helper never reads it. Restoring the two-argument
`float` contract is byte-identical at 9/9 instructions with all three operands
clean. The canonical declaration now lives in `rmath_random.h`; migrating its
callers from divergent float/double and pointer/integer declarations preserves
every focused result, including the exact garbage and slug AI consumers.
