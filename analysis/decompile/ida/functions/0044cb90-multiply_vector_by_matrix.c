/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: multiply_vector_by_matrix @ 0x44cb90 */
/* selector: multiply_vector_by_matrix */

// Applies one affine matrix to a vector in place, including translation. Android symbols match this helper to `tVector::Multiply(const tMatrix&)`.
int __thiscall sub_44CB90(
        float *this,
        float a2,
        float a3,
        float a4,
        int a5,
        float a6,
        float a7,
        float a8,
        int a9,
        float a10,
        float a11,
        float a12,
        int a13,
        float a14,
        float a15,
        float a16,
        int a17)
{
  int result; // eax
  float v18; // [esp+0h] [ebp-Ch]
  float v19; // [esp+4h] [ebp-8h]

  v18 = *this;
  v19 = *(this + 1);
  result = *((int *)this + 2);
  *this = *(float *)&result * a10 + v19 * a6 + *this * a2 + a14;
  *(this + 1) = a11 * *(float *)&result + a7 * v19 + a3 * v18 + a15;
  *(this + 2) = a12 * *(float *)&result + a8 * v19 + a4 * v18 + a16;
  return result;
}

