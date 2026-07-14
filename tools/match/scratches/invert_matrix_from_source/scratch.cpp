// invert_matrix_from_source @ 0x44d330 (thiscall)

#include "transform_matrix.h"

void TransformMatrix::invert_matrix_from_source(const TransformMatrix& source)
{
    position.x = -(source.position.y * source.basis_right.y + source.basis_right.z * source.position.z + source.position.x * source.basis_right.x);
    position.y = -(source.position.y * source.basis_up.y + source.basis_up.z * source.position.z + source.position.x * source.basis_up.x);
    position.z = -(source.position.y * source.basis_forward.y + source.position.x * source.basis_forward.x + source.position.z * source.basis_forward.z);
    basis_right.x = source.basis_right.x;
    basis_right.y = source.basis_up.x;
    basis_right.z = source.basis_forward.x;
    basis_up.x = source.basis_right.y;
    basis_up.y = source.basis_up.y;
    basis_up.z = source.basis_forward.y;
    basis_forward.x = source.basis_right.z;
    basis_forward.y = source.basis_up.z;
    basis_forward.z = source.basis_forward.z;
    basis_forward_w = 0.0f;
    basis_up_w = 0.0f;
    basis_right_w = 0.0f;
    position_w = 1.0f;
}
