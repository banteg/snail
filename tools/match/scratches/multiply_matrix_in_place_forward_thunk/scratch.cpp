// TransformMatrix::multiply_matrix_in_place_forward_thunk @ 0x44d1d0

struct TransformMatrixForwardView {
    TransformMatrixForwardView* multiply_matrix_in_place(TransformMatrixForwardView* rhs);
    TransformMatrixForwardView* multiply_matrix_in_place_forward_thunk(
        TransformMatrixForwardView* rhs);
};

TransformMatrixForwardView* TransformMatrixForwardView::multiply_matrix_in_place_forward_thunk(
    TransformMatrixForwardView* rhs)
{
    return multiply_matrix_in_place(rhs);
}
