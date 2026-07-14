// TransformMatrix::multiply_matrix_in_place_forward_thunk @ 0x44d1d0

#include "transform_matrix.h"

TransformMatrix* TransformMatrix::multiply_matrix_in_place_forward_thunk(
    TransformMatrix* rhs)
{
    return multiply_matrix_in_place(rhs);
}
