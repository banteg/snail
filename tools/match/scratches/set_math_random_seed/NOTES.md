# RandSeed @ 0x44c970

Exact at 100.00%, 5/5 instructions, with its one masked operand clean.

Windows is a void wrapper around CRT `srand`. Android and iOS preserve the
authored `RandSeed(int)` name while also updating their compact random-table
state. The platform-specific state tail is not transferred into Windows.
