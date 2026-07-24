// TransformMatrix::multiply_matrix @ 0x44d1d0

#include "transform_matrix.h"

void TransformMatrix::multiply_matrix(const TransformMatrix& rhs)
{
    *this *= rhs;
}
