# multiply_matrix_in_place_forward_thunk @ 0x44d1d0

Thiscall forwarding thunk used twice by the loopbow path-template constructor.
It pushes the rhs argument and calls the canonical matrix multiply at
`0x44d1a0`, preserving the incoming matrix receiver in `ECX`.

2026-07-14 ownership pass: the thunk is now declared and defined directly on
the shared `TransformMatrix` owner. The scratch-local `TransformMatrixForwardView`
duplicated the same receiver and argument layout. The canonical spelling stays
exact at 4/4 instructions with its single masked call operand clean.

The forwarder is now honestly void and takes a const reference, matching its
callee and remaining 4/4 exact. Although the adjacent mobile symbol inventory
contains `tMatrix::operator*=`, this tiny Windows body is kept under its stable
forwarder identity until the operator mapping itself has independent proof.
