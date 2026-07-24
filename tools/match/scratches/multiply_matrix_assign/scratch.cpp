// TransformMatrix::operator*= @ 0x44d1a0 (thiscall)

#include "transform_matrix.h"

void TransformMatrix::operator*=(const TransformMatrix& rhs)
{
    TransformMatrix lhs = *this;
    multiply_matrices(lhs, rhs);
}
