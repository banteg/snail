// orthogonalize_matrix @ 0x44d3d0 (thiscall)

#include "transform_matrix.h"

void tMatrix::Orthoganalize()
{
    tVector* right = &basis_right;
    tVector* up = &basis_up;
    tVector* forward = &basis_forward;

    right->Normalize();
    up->Normalize();
    forward->Normalize();
    right->cross_vectors(up, forward);
    forward->cross_vectors(right, up);
}
