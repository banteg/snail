/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: multiply_matrix_in_place_forward_thunk @ 0x44d1d0 */
/* selector: multiply_matrix_in_place_forward_thunk */

// Exact void thiscall forwarder that passes one const-reference rhs matrix to the owned `TransformMatrix::multiply_matrix` member. Its source-level operator identity remains deliberately unresolved.
void __thiscall multiply_matrix_in_place_forward_thunk(TransformMatrix *matrix, const TransformMatrix *rhs)
{
  multiply_matrix(matrix, rhs);
}
