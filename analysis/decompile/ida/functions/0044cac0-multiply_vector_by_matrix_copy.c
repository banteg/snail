/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: multiply_vector_by_matrix_copy @ 0x44cac0 */
/* selector: multiply_vector_by_matrix_copy */

// Writes an out-of-place affine vector-by-matrix transform into a destination output. Android symbols match this helper to `tVector::operator*(const tMatrix&) const`.
float *__thiscall sub_44CAC0(float *this, float *a2, float *a3)
{
  float v4; // [esp+0h] [ebp-Ch]
  float v5; // [esp+4h] [ebp-8h]
  float v6; // [esp+8h] [ebp-4h]

  v4 = a3[8] * *(this + 2) + a3[4] * *(this + 1) + *a3 * *this + a3[12];
  v5 = a3[9] * *(this + 2) + a3[1] * *this + a3[5] * *(this + 1) + a3[13];
  v6 = a3[10] * *(this + 2) + a3[2] * *this + a3[6] * *(this + 1) + a3[14];
  *a2 = v4;
  a2[1] = v5;
  a2[2] = v6;
  return a2;
}

