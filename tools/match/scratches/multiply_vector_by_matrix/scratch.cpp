// multiply_vector_by_matrix @ 0x44cb90 (thiscall)

#include "vector_types.h"

struct TransformMatrix {
    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 position;
};

struct Vec3 {
    float x;
    float y;
    float z;

    void multiply_vector_by_matrix(TransformMatrix matrix);
};

void Vec3::multiply_vector_by_matrix(TransformMatrix matrix)
{
    Vec3 source = *this;

    x = source.x * matrix.basis_right.x + source.y * matrix.basis_up.x + source.z * matrix.basis_forward.x + matrix.position.x;
    y = matrix.basis_right.y * source.x + matrix.basis_up.y * source.y + matrix.basis_forward.y * source.z + matrix.position.y;
    z = matrix.basis_right.z * source.x + matrix.basis_up.z * source.y + matrix.basis_forward.z * source.z + matrix.position.z;
}
