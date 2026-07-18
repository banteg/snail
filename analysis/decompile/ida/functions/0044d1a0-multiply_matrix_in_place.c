/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: multiply_matrix_in_place @ 0x44d1a0 */
/* database symbol: multiply_matrix */
/* selector: multiply_matrix_in_place */

// Stable Windows harness identity for the exact void `TransformMatrix::multiply_matrix(const TransformMatrix&)` member retained by iOS and Android as `tMatrix::Multiply(const tMatrix&)`. It snapshots its receiver and delegates to the two-reference multiply core.
void __thiscall multiply_matrix(TransformMatrix *matrix, const TransformMatrix *rhs)
{
  TransformMatrix lhs; // [esp+8h] [ebp-40h] BYREF

  qmemcpy(&lhs, matrix, sizeof(lhs));
  multiply_matrices(matrix, &lhs, rhs);
}
