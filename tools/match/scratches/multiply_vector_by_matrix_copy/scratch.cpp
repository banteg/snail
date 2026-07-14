// multiply_vector_by_matrix_copy @ 0x44cac0 (thiscall)

#include "transform_matrix.h"

Vector3 Vector3::operator*(const TransformMatrix& matrix) const
{
    Vector3 result = *this;

    result.x = matrix.basis_forward.x * z + matrix.basis_up.x * y + matrix.basis_right.x * x + matrix.position.x;
    result.y = matrix.basis_forward.y * z + matrix.basis_right.y * x + matrix.basis_up.y * y + matrix.position.y;
    result.z = matrix.basis_forward.z * z + matrix.basis_right.z * x + matrix.basis_up.z * y + matrix.position.z;

    return result;
}
