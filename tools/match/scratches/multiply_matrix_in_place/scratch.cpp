// multiply_matrix_in_place @ 0x44d1a0 (thiscall)

#include "transform_matrix.h"

TransformMatrix* TransformMatrix::multiply_matrix_in_place(TransformMatrix* rhs)
{
    TransformMatrix lhs = *this;
    return multiply_matrices(&lhs, rhs);
}
