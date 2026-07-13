# multiply_matrix_in_place_forward_thunk @ 0x44d1d0

Thiscall forwarding thunk used twice by the loopbow path-template constructor.
It pushes the rhs argument and calls the canonical in-place matrix multiply at
`0x44d1a0`, preserving the incoming matrix receiver in `ECX`.
