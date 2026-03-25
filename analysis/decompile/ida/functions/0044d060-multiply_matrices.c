/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: multiply_matrices @ 0x44d060 */
/* selector: multiply_matrices */

// Core affine matrix multiply that writes `out = lhs * rhs` for the 3x3 basis and translated origin row. Android symbols match this helper to `tMatrix::Multiply(const tMatrix&, const tMatrix&)`.
float *__thiscall sub_44D060(float *this, float *a2, float *a3)
{
  *this = *a2 * *a3 + a2[1] * a3[4] + a2[2] * a3[8];
  *(this + 1) = a2[1] * a3[5] + a3[1] * *a2 + a3[9] * a2[2];
  *(this + 2) = a2[1] * a3[6] + a3[2] * *a2 + a3[10] * a2[2];
  *(this + 4) = a2[6] * a3[8] + a2[5] * a3[4] + a2[4] * *a3;
  *(this + 5) = a2[6] * a3[9] + a2[5] * a3[5] + a2[4] * a3[1];
  *(this + 6) = a2[6] * a3[10] + a2[5] * a3[6] + a2[4] * a3[2];
  *(this + 8) = a2[8] * *a3 + a2[10] * a3[8] + a2[9] * a3[4];
  *(this + 9) = a3[9] * a2[10] + a3[5] * a2[9] + a3[1] * a2[8];
  *(this + 10) = a3[10] * a2[10] + a3[6] * a2[9] + a3[2] * a2[8];
  *(this + 12) = a2[14] * a3[8] + a2[13] * a3[4] + a2[12] * *a3 + a3[12];
  *(this + 13) = a2[14] * a3[9] + a2[13] * a3[5] + a2[12] * a3[1] + a3[13];
  *(this + 14) = a2[14] * a3[10] + a2[13] * a3[6] + a2[12] * a3[2] + a3[14];
  return a3;
}

