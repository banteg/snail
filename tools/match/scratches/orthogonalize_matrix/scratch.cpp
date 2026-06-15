// orthogonalize_matrix @ 0x44d3d0 (fastcall)

#include "transform_matrix.h"

float __fastcall normalize_vector(Vector3* vector);

void __fastcall orthogonalize_matrix(TransformMatrix* transform)
{
    Vector3* right = &transform->basis_right;
    Vector3* up = &transform->basis_up;
    Vector3* forward = &transform->basis_forward;

    normalize_vector(right);
    normalize_vector(up);
    normalize_vector(forward);
    right->cross_vectors(up, forward);
    forward->cross_vectors(right, up);
}
