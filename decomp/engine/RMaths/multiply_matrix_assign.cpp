// tMatrix::operator*= @ 0x44d1a0 (thiscall)

#include "transform_matrix.h"

void tMatrix::operator*=(const tMatrix& rhs)
{
    tMatrix lhs = *this;
    Multiply(lhs, rhs);
}
