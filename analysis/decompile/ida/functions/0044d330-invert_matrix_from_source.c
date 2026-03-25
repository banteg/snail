/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: invert_matrix_from_source @ 0x44d330 */
/* selector: invert_matrix_from_source */

// Writes the inverse of a source orthonormal transform into a destination matrix. Android symbols match this helper to `tMatrix::Invert(const tMatrix&)`.
int __thiscall sub_44D330(float *this, float *a2)
{
  *(this + 12) = -(a2[13] * a2[1] + a2[2] * a2[14] + a2[12] * *a2);
  *(this + 13) = -(a2[13] * a2[5] + a2[6] * a2[14] + a2[12] * a2[4]);
  *(this + 14) = -(a2[13] * a2[9] + a2[12] * a2[8] + a2[14] * a2[10]);
  *this = *a2;
  *(this + 1) = a2[4];
  *(this + 2) = a2[8];
  *(this + 4) = a2[1];
  *(this + 5) = a2[5];
  *(this + 6) = a2[9];
  *(this + 8) = a2[2];
  *(this + 9) = a2[6];
  *(this + 10) = a2[10];
  *(this + 11) = 0.0;
  *(this + 7) = 0.0;
  *(this + 3) = 0.0;
  *(this + 15) = 1.0;
  return 0;
}

