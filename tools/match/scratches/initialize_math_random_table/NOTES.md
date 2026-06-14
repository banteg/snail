# initialize_math_random_table @ 0x44c8d0

Exact match: 100.00%, 10/10 instructions.

Fills the 0x1fff-entry gameplay random table from the CRT `rand()` stream and
resets the shared table cursor. The pointer compare is intentionally spelled as
a signed integer compare, matching the native `jl` loop guard.
