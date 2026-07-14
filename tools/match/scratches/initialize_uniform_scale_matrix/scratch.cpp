// initialize_uniform_scale_matrix @ 0x44cde0
// Authored owner: tMatrix::tMatrix(float).

#include "transform_matrix.h"

TransformMatrix::TransformMatrix(float scale)
{
    basis_right.x = scale;
    basis_right.y = 0.0f;
    basis_right.z = 0.0f;
    basis_right_w = 0.0f;
    basis_up.x = 0.0f;
    basis_up.y = scale;
    basis_up.z = 0.0f;
    basis_up_w = 0.0f;
    basis_forward.x = 0.0f;
    basis_forward.y = 0.0f;
    basis_forward.z = scale;
    basis_forward_w = 0.0f;
    position.x = 0.0f;
    position.y = 0.0f;
    position.z = 0.0f;
    position_w = 1.0f;
}
