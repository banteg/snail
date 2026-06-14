// rotate_vector_by_matrix @ 0x44cc20 (thiscall)

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

    Vec3* rotate_vector_by_matrix(const TransformMatrix* matrix);
};

Vec3* Vec3::rotate_vector_by_matrix(const TransformMatrix* matrix)
{
    Vec3 source = *this;

    x = source.x * matrix->basis_right.x + source.y * matrix->basis_up.x + source.z * matrix->basis_forward.x;
    y = source.x * matrix->basis_right.y + source.y * matrix->basis_up.y + source.z * matrix->basis_forward.y;
    z = source.x * matrix->basis_right.z + source.y * matrix->basis_up.z + source.z * matrix->basis_forward.z;
    return this;
}
