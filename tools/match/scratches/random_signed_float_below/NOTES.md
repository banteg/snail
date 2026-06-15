# random_signed_float_below @ 0x44dc70

Exact match: 100.00%, 9/9 instructions.

Centers the CRT RNG stream around zero before scaling by the caller's upper
bound. Like `random_float_below`, the native call targets the `j_rand` thunk at
`0x44c920`, not the CRT body directly.
