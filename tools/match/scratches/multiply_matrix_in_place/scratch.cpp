// multiply_matrix_in_place @ 0x44d1a0 (thiscall)

#include "vector_types.h"

struct TransformMatrix {
    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 position;

    TransformMatrix* multiply_matrix_in_place(TransformMatrix* rhs);
    TransformMatrix* multiply_matrices(const TransformMatrix* lhs, const TransformMatrix* rhs);
};

TransformMatrix* TransformMatrix::multiply_matrix_in_place(TransformMatrix* rhs)
{
    TransformMatrix lhs = *this;
    return multiply_matrices(&lhs, rhs);
}
