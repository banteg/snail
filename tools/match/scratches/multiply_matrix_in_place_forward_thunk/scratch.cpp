// TransformMatrix::multiply_matrix_in_place_forward_thunk @ 0x44d1d0

#include "transform_matrix.h"

void TransformMatrix::multiply_matrix_in_place_forward_thunk(
    const TransformMatrix& rhs)
{
    multiply_matrix(rhs);
}
