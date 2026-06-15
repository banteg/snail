#include "transform_matrix.h"

void __fastcall set_matrix_rotation_identity(TransformMatrix* transform)
{
    transform->position_w = 1.0f;
    transform->basis_forward.z = 1.0f;
    transform->basis_up.y = 1.0f;
    transform->basis_right.x = 1.0f;
    transform->basis_forward_w = 0.0f;
    transform->basis_forward.y = 0.0f;
    transform->basis_forward.x = 0.0f;
    transform->basis_up_w = 0.0f;
    transform->basis_up.z = 0.0f;
    transform->basis_up.x = 0.0f;
    transform->basis_right_w = 0.0f;
    transform->basis_right.z = 0.0f;
    transform->basis_right.y = 0.0f;
}
