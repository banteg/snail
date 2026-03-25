/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: invert_matrix_in_place @ 0x44d280 */
/* selector: invert_matrix_in_place */

// Inverts one orthonormal transform matrix in place by transposing the basis and recomputing the negated translated origin. Android symbols match this helper to `tMatrix::Invert()`.
float *__thiscall sub_44D280(float *this)
{
  float *result; // eax
  double v2; // st7
  float v3; // edx
  float v4; // ecx
  double v5; // st7
  double v6; // st6
  float v7; // edx
  float v8; // ecx
  double v9; // st7
  double v10; // st6
  float v11; // edx
  float v12[16]; // [esp+8h] [ebp-40h] BYREF

  result = this;
  qmemcpy(v12, this, sizeof(v12));
  v2 = v12[2] * *(this + 14) + v12[13] * v12[1] + v12[12] * v12[0];
  v3 = v12[8];
  *(this + 1) = v12[4];
  v4 = v12[1];
  result[12] = -v2;
  v5 = v12[6] * result[14];
  v6 = v12[5] * v12[13];
  result[2] = v3;
  v7 = v12[9];
  result[4] = v4;
  v8 = v12[2];
  v9 = v5 + v6;
  v10 = v12[4] * v12[12];
  result[6] = v7;
  v11 = v12[6];
  result[8] = v8;
  result[9] = v11;
  result[13] = -(v9 + v10);
  result[14] = -(v12[10] * result[14] + v12[9] * v12[13] + v12[8] * v12[12]);
  return result;
}

