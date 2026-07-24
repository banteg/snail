/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: multiply_matrix @ 0x44d1d0 */
/* selector: multiply_matrix */

// Exact void `TransformMatrix::multiply_matrix(const TransformMatrix&)` member retained by iOS and Android as `tMatrix::Multiply(const tMatrix&)`. The Windows body forwards its rhs reference to the owned multiply-assignment operator, matching Android's direct branch from `Multiply` to `operator*=`.
void __thiscall multiply_matrix(TransformMatrix *matrix, const TransformMatrix *rhs)
{
  multiply_matrix_assign(matrix, rhs);
}
