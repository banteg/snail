# initialize_math_random_table @ 0x44c8d0

Exact match: 100.00%, 10/10 instructions.

Fills the 0x1fff-entry gameplay random table from the CRT `rand()` stream and
resets the shared table cursor. The pointer compare is intentionally spelled as
a signed integer compare, matching the native `jl` loop guard.

## 2026-07-27 authored gRMathRand2Init contract

Android exports the corresponding platform body as void
`gRMathRand2Init()`. Its compact persisted table differs from the Windows
0x1fff-entry `int` table, but both fill the owned gameplay stream and reset its
cursor before `RMathInit()` returns.

The final Windows sample remains live in EAX only because it was last returned
by CRT `rand`; no caller consumes it. Removing the synthetic result is
byte-identical at 10/10 instructions with all four operands clean. The void
declaration is shared through `rmath_random.h`.
