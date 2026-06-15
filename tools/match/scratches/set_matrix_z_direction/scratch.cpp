// set_matrix_z_direction @ 0x44d410 (thiscall)

#include "transform_matrix.h"

void TransformMatrix::set_matrix_z_direction(const Vector3* direction)
{
    Vector3 right;
    Vector3 forward;
    Vector3* up = &basis_up;

    if (forward.normalize_vector_from_source(direction) != 0.0f) {
        basis_forward.x = forward.x;
        basis_forward.y = forward.y;
        basis_forward.z = forward.z;

        if (forward.x == 0.0f && forward.z == 0.0f) {
            right.x = 1.0f;
            right.z = 0.0f;
        } else {
            right.z = -forward.x;
            right.x = forward.z;
        }

        right.y = 0.0f;
        right.normalize_vector();
        basis_right.x = right.x;
        basis_right.y = right.y;
        basis_right.z = right.z;
        up->cross_vectors(&forward, &right);
    }
}
