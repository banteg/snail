// invert_matrix_in_place @ 0x44d280 (thiscall)

#include "transform_matrix.h"

void TransformMatrix::invert_matrix_in_place()
{
    TransformMatrix source = *this;

    position.x = -(source.basis_right.z * position.z + source.basis_right.x * source.position.x + source.basis_right.y * source.position.y);
    basis_right.y = source.basis_up.x;
    basis_right.z = source.basis_forward.x;
    basis_up.x = source.basis_right.y;
    basis_up.z = source.basis_forward.y;
    basis_forward.x = source.basis_right.z;
    basis_forward.y = source.basis_up.z;
    position.y = -(source.basis_up.z * position.z + source.basis_up.y * source.position.y + source.basis_up.x * source.position.x);
    position.z = -(source.basis_forward.z * position.z + source.basis_forward.x * source.position.x + source.basis_forward.y * source.position.y);
}
