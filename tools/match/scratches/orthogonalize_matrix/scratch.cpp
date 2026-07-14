// orthogonalize_matrix @ 0x44d3d0 (thiscall)

#include "transform_matrix.h"

void TransformMatrix::orthogonalize_matrix()
{
    Vector3* right = &basis_right;
    Vector3* up = &basis_up;
    Vector3* forward = &basis_forward;

    right->normalize_vector();
    up->normalize_vector();
    forward->normalize_vector();
    right->cross_vectors(up, forward);
    forward->cross_vectors(right, up);
}
