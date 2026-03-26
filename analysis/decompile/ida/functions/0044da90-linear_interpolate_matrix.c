/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: linear_interpolate_matrix @ 0x44da90 */
/* selector: linear_interpolate_matrix */

// Interpolates one transform toward another by blending rotation in matrix space and linearly blending translation. Android symbols match this helper to `tMatrix::LinearInterpolate(const tMatrix&, const tMatrix&, float)`.
void __thiscall linear_interpolate_matrix(
        TransformMatrix *out,
        TransformMatrix *from,
        TransformMatrix *to,
        float alpha)
{
  TransformMatrix *v4; // edx
  TransformMatrix *v5; // esi
  double v6; // st6
  float v7; // [esp+Ch] [ebp-24h]
  float v8; // [esp+10h] [ebp-20h]
  float v9; // [esp+14h] [ebp-1Ch]
  float v10; // [esp+18h] [ebp-18h]
  float v11; // [esp+1Ch] [ebp-14h]
  float v12; // [esp+20h] [ebp-10h]
  float v13; // [esp+28h] [ebp-8h]
  float v14; // [esp+2Ch] [ebp-4h]

  v5 = out;
  invert_matrix_from_source(out, v4);
  multiply_matrix_in_place(v5, to);
  interpolate_matrix_rotation(v5, alpha);
  premultiply_matrix_in_place(v5, from);
  orthogonalize_matrix(v5);
  v5 = (TransformMatrix *)((char *)v5 + 48);
  v13 = alpha * to->position.y;
  v14 = alpha * to->position.z;
  v6 = 1.0 - alpha;
  v7 = v6 * from->position.x;
  v8 = v6 * from->position.y;
  v9 = v6 * from->position.z;
  v10 = v7 + alpha * to->position.x;
  v5->basis_right.x = v10;
  v11 = v8 + v13;
  v5->basis_right.y = v11;
  v12 = v9 + v14;
  v5->basis_right.z = v12;
}

