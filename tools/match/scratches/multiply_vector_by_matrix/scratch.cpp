// multiply_vector_by_matrix @ 0x44cb90 (thiscall)

#include "transform_matrix.h"

void Vector3::operator*=(TransformMatrix matrix)
{
    Vector3 source = *this;

    x = matrix.basis_right.x * source.x + matrix.basis_up.x * source.y + matrix.basis_forward.x * source.z + matrix.position.x;
    y = matrix.basis_right.y * source.x + matrix.basis_up.y * source.y + matrix.basis_forward.y * source.z + matrix.position.y;
    z = matrix.basis_right.z * source.x + matrix.basis_up.z * source.y + matrix.basis_forward.z * source.z + matrix.position.z;
}
