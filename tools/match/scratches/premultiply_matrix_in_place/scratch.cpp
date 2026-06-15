// premultiply_matrix_in_place @ 0x44d1e0 (thiscall)

#include "transform_matrix.h"

TransformMatrix* TransformMatrix::premultiply_matrix_in_place(TransformMatrix* rhs)
{
    TransformMatrix lhs = *this;
    return multiply_matrices(rhs, &lhs);
}
