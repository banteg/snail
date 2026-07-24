/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: multiply_matrix_assign @ 0x44d1a0 */
/* selector: multiply_matrix_assign */

// Exact void `TransformMatrix::operator*=(const TransformMatrix&)` member: it snapshots its receiver and delegates to the two-reference multiply core. Android retains the full body as `tMatrix::operator*=`, while its `tMatrix::Multiply(const tMatrix&)` entry is a forwarding branch to this operator; the Windows pair has the same ownership split.
void __thiscall multiply_matrix_assign(TransformMatrix *matrix, const TransformMatrix *rhs)
{
  TransformMatrix lhs; // [esp+8h] [ebp-40h] BYREF

  qmemcpy(&lhs, matrix, sizeof(lhs));
  multiply_matrices(matrix, &lhs, rhs);
}
