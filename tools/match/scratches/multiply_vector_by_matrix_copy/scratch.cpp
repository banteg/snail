// multiply_vector_by_matrix_copy @ 0x44cac0 (thiscall)

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

    Vec3* multiply_vector_by_matrix_copy(Vec3* out, const TransformMatrix* matrix) const;
};

Vec3* Vec3::multiply_vector_by_matrix_copy(Vec3* out, const TransformMatrix* matrix) const
{
    Vec3 result = *this;

    result.x = matrix->basis_forward.x * z + matrix->basis_up.x * y + matrix->basis_right.x * x + matrix->position.x;
    result.y = matrix->basis_forward.y * z + matrix->basis_right.y * x + matrix->basis_up.y * y + matrix->position.y;
    result.z = matrix->basis_forward.z * z + matrix->basis_right.z * x + matrix->basis_up.z * y + matrix->position.z;

    *out = result;
    return out;
}
