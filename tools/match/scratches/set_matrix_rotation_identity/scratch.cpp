#include "transform_matrix.h"

void TransformMatrix::set_matrix_rotation_identity()
{
    position_w = 1.0f;
    basis_forward.z = 1.0f;
    basis_up.y = 1.0f;
    basis_right.x = 1.0f;
    basis_forward_w = 0.0f;
    basis_forward.y = 0.0f;
    basis_forward.x = 0.0f;
    basis_up_w = 0.0f;
    basis_up.z = 0.0f;
    basis_up.x = 0.0f;
    basis_right_w = 0.0f;
    basis_right.z = 0.0f;
    basis_right.y = 0.0f;
}
