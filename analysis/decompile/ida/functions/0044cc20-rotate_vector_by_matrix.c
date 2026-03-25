/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: rotate_vector_by_matrix @ 0x44cc20 */
/* selector: rotate_vector_by_matrix */

// Applies only the 3x3 rotational basis of a matrix to a vector in place, leaving translation out. Android symbols match this helper to `tVector::Rotate(const tMatrix&)`.
float *__thiscall sub_44CC20(float *this, float *a2)
{
  float v3; // [esp+0h] [ebp-Ch]
  float v4; // [esp+4h] [ebp-8h]
  float v5; // [esp+8h] [ebp-4h]

  v3 = *this;
  v4 = *(this + 1);
  v5 = *(this + 2);
  *this = v5 * a2[8] + v4 * a2[4] + *this * *a2;
  *(this + 1) = v5 * a2[9] + v4 * a2[5] + v3 * a2[1];
  *(this + 2) = v5 * a2[10] + v4 * a2[6] + v3 * a2[2];
  return this;
}

