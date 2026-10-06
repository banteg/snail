// premultiply_matrix_in_place @ 0x44d1e0 (thiscall)

#include "transform_matrix.h"

void tMatrix::PreMultiply(const tMatrix& lhs)
{
    tMatrix rhs = *this;
    Multiply(lhs, rhs);
}
