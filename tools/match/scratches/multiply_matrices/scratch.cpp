// multiply_matrices @ 0x44d060 (thiscall, ret 0x8)

#include "transform_matrix.h"

TransformMatrix* TransformMatrix::multiply_matrices(
    const TransformMatrix* lhs,
    const TransformMatrix* rhs)
{
    basis_right.x = lhs->basis_right.x * rhs->basis_right.x
        + lhs->basis_right.y * rhs->basis_up.x
        + lhs->basis_right.z * rhs->basis_forward.x;
    basis_right.y = lhs->basis_right.y * rhs->basis_up.y
        + rhs->basis_right.y * lhs->basis_right.x
        + rhs->basis_forward.y * lhs->basis_right.z;
    basis_right.z = lhs->basis_right.y * rhs->basis_up.z
        + rhs->basis_right.z * lhs->basis_right.x
        + rhs->basis_forward.z * lhs->basis_right.z;

    basis_up.x = lhs->basis_up.z * rhs->basis_forward.x
        + lhs->basis_up.y * rhs->basis_up.x
        + lhs->basis_up.x * rhs->basis_right.x;
    basis_up.y = lhs->basis_up.z * rhs->basis_forward.y
        + lhs->basis_up.y * rhs->basis_up.y
        + lhs->basis_up.x * rhs->basis_right.y;
    basis_up.z = lhs->basis_up.z * rhs->basis_forward.z
        + lhs->basis_up.y * rhs->basis_up.z
        + lhs->basis_up.x * rhs->basis_right.z;

    basis_forward.x = lhs->basis_forward.x * rhs->basis_right.x
        + lhs->basis_forward.z * rhs->basis_forward.x
        + lhs->basis_forward.y * rhs->basis_up.x;
    basis_forward.y = rhs->basis_forward.y * lhs->basis_forward.z
        + rhs->basis_up.y * lhs->basis_forward.y
        + rhs->basis_right.y * lhs->basis_forward.x;
    basis_forward.z = rhs->basis_forward.z * lhs->basis_forward.z
        + rhs->basis_up.z * lhs->basis_forward.y
        + rhs->basis_right.z * lhs->basis_forward.x;

    position.x = lhs->position.z * rhs->basis_forward.x
        + lhs->position.y * rhs->basis_up.x
        + lhs->position.x * rhs->basis_right.x
        + rhs->position.x;
    position.y = lhs->position.z * rhs->basis_forward.y
        + lhs->position.y * rhs->basis_up.y
        + lhs->position.x * rhs->basis_right.y
        + rhs->position.y;
    position.z = lhs->position.z * rhs->basis_forward.z
        + lhs->position.y * rhs->basis_up.z
        + lhs->position.x * rhs->basis_right.z
        + rhs->position.z;

    return const_cast<TransformMatrix*>(rhs);
}
