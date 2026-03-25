/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: linear_interpolate_matrix @ 0x44da90 */
/* selector: linear_interpolate_matrix */

// Interpolates one transform toward another by blending rotation in matrix space and linearly blending translation. Android symbols match this helper to `tMatrix::LinearInterpolate(const tMatrix&, const tMatrix&, float)`.
int __thiscall sub_44DA90(float *this, float *a2, float *a3, float a4)
{
  float *v4; // esi
  double v5; // st6
  float v7; // [esp+Ch] [ebp-24h]
  float v8; // [esp+10h] [ebp-20h]
  float v9; // [esp+14h] [ebp-1Ch]
  float v10; // [esp+18h] [ebp-18h]
  float v11; // [esp+1Ch] [ebp-14h]
  float v12; // [esp+20h] [ebp-10h]
  float v13; // [esp+28h] [ebp-8h]
  float v14; // [esp+2Ch] [ebp-4h]

  v4 = this;
  invert_matrix_from_source(this, a2);
  multiply_matrix_in_place(v4, a3);
  interpolate_matrix_rotation(v4, a4);
  premultiply_matrix_in_place(v4, a2);
  orthogonalize_matrix(v4);
  v4 += 12;
  v13 = a4 * a3[13];
  v14 = a4 * a3[14];
  v5 = 1.0 - a4;
  v7 = v5 * a2[12];
  v8 = v5 * a2[13];
  v9 = v5 * a2[14];
  v10 = v7 + a4 * a3[12];
  *v4 = v10;
  v11 = v8 + v13;
  v4[1] = v11;
  v12 = v9 + v14;
  v4[2] = v12;
  return LODWORD(v12);
}

