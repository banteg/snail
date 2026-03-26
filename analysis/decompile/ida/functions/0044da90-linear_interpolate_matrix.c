/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: linear_interpolate_matrix @ 0x44da90 */
/* selector: linear_interpolate_matrix */

// Interpolates one transform toward another by blending rotation in matrix space and linearly blending translation. Android symbols match this helper to `tMatrix::LinearInterpolate(const tMatrix&, const tMatrix&, float)`.
TransformMatrix *__thiscall linear_interpolate_matrix(
        TransformMatrix *out,
        TransformMatrix *from,
        TransformMatrix *to,
        float alpha)
{
  TransformMatrix *v4; // edx
  TransformMatrix *v5; // esi
  double v6; // st6
  float v8; // [esp+Ch] [ebp-24h]
  float v9; // [esp+10h] [ebp-20h]
  float v10; // [esp+14h] [ebp-1Ch]
  float v11; // [esp+18h] [ebp-18h]
  float v12; // [esp+1Ch] [ebp-14h]
  float v13; // [esp+20h] [ebp-10h]
  float v14; // [esp+28h] [ebp-8h]
  float v15; // [esp+2Ch] [ebp-4h]

  v5 = out;
  invert_matrix_from_source(out, v4);
  multiply_matrix_in_place(v5, to);
  interpolate_matrix_rotation(v5, alpha);
  premultiply_matrix_in_place(v5, from);
  orthogonalize_matrix(v5);
  v5 = (TransformMatrix *)((char *)v5 + 48);
  v14 = alpha * to->position.y;
  v15 = alpha * to->position.z;
  v6 = 1.0 - alpha;
  v8 = v6 * from->position.x;
  v9 = v6 * from->position.y;
  v10 = v6 * from->position.z;
  v11 = v8 + alpha * to->position.x;
  v5->basis_right.x = v11;
  v12 = v9 + v14;
  v5->basis_right.y = v12;
  v13 = v10 + v15;
  v5->basis_right.z = v13;
  return (TransformMatrix *)LODWORD(v13);
}

