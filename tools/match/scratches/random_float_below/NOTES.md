# random_float_below @ 0x44dc90

Exact match: 100.00%, 8/8 instructions.

Scales the CRT RNG stream by the caller's upper bound. The native call is
through the small `j_rand` thunk at `0x44c920`, which immediately jumps to the
CRT `rand` body at `0x48bfe5`.
