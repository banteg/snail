// multiply_matrix_in_place @ 0x44d1a0 (thiscall)

#include "transform_matrix.h"

void TransformMatrix::multiply_matrix(const TransformMatrix& rhs)
{
    TransformMatrix lhs = *this;
    multiply_matrices(lhs, rhs);
}
