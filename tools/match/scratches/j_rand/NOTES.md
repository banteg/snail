# j_rand @ 0x44c920

Game-code jump thunk to the statically linked CRT `rand` body at `0x48bfe5`.
Exact `random_signed_float_below` and `random_float_below` both call this thunk,
while the startup random-table initializer calls the CRT body directly.
