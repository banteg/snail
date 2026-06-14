// initialize_uniform_scale_matrix @ 0x44cde0 (thiscall)

#include "vector_types.h"

struct TransformMatrix {
    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 position;

    TransformMatrix* initialize_uniform_scale_matrix(float scale);
};

TransformMatrix* TransformMatrix::initialize_uniform_scale_matrix(float scale)
{
    basis_right.x = scale;
    basis_right.y = 0.0f;
    basis_right.z = 0.0f;
    basis_right.w = 0.0f;
    basis_up.x = 0.0f;
    basis_up.y = scale;
    basis_up.z = 0.0f;
    basis_up.w = 0.0f;
    basis_forward.x = 0.0f;
    basis_forward.y = 0.0f;
    basis_forward.z = scale;
    basis_forward.w = 0.0f;
    position.x = 0.0f;
    position.y = 0.0f;
    position.z = 0.0f;
    position.w = 1.0f;
    return this;
}
