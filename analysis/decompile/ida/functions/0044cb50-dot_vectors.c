/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: dot_vectors @ 0x44cb50 */
/* selector: dot_vectors */

// Computes the 3D dot product of two vectors. Android symbols match this helper to the static overload `tVector::Dot(const tVector&, const tVector&)`.
double __stdcall sub_44CB50(float *a1, float *a2)
{
  return a1[2] * a2[2] + a1[1] * a2[1] + *a1 * *a2;
}

