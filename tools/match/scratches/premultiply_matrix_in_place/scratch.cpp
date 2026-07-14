// premultiply_matrix_in_place @ 0x44d1e0 (thiscall)

#include "transform_matrix.h"

void TransformMatrix::premultiply_matrix_in_place(const TransformMatrix& lhs)
{
    TransformMatrix rhs = *this;
    multiply_matrices(lhs, rhs);
}
