/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: linear_interpolate_matrix @ 0x44da90 */
/* selector: linear_interpolate_matrix */

// Exact void `TransformMatrix::linear_interpolate_matrix(const TransformMatrix&, const TransformMatrix&, float)` method: blends rotation in matrix space and translation linearly, matching mobile `tMatrix::LinearInterpolate(tMatrix const&, tMatrix const&, float)`.
void __thiscall linear_interpolate_matrix(
        TransformMatrix *out,
        const TransformMatrix *from,
        const TransformMatrix *to,
        float alpha)
{
  TransformMatrix *v4; // esi
  double v5; // st6
  float v6; // [esp+Ch] [ebp-24h]
  float v7; // [esp+10h] [ebp-20h]
  float v8; // [esp+14h] [ebp-1Ch]
  float v9; // [esp+18h] [ebp-18h]
  float v10; // [esp+1Ch] [ebp-14h]
  float v11; // [esp+20h] [ebp-10h]
  float v12; // [esp+28h] [ebp-8h]
  float v13; // [esp+2Ch] [ebp-4h]

  v4 = out;
  invert_matrix_from_source(out, from);
  multiply_matrix(v4, to);
  interpolate_matrix_rotation(v4, alpha);
  premultiply_matrix_in_place(v4, from);
  orthogonalize_matrix(v4);
  v4 = (TransformMatrix *)((char *)v4 + 48);
  v12 = alpha * to->position.y;
  v13 = alpha * to->position.z;
  v5 = 1.0 - alpha;
  v6 = v5 * from->position.x;
  v7 = v5 * from->position.y;
  v8 = v5 * from->position.z;
  v9 = v6 + alpha * to->position.x;
  v4->basis_right.x = v9;
  v10 = v7 + v12;
  v4->basis_right.y = v10;
  v11 = v8 + v13;
  v4->basis_right.z = v11;
}
