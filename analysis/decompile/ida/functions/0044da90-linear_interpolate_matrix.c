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
  double v5; // st6
  float v6; // [esp+Ch] [ebp-24h]
  float v7; // [esp+10h] [ebp-20h]
  float v8; // [esp+14h] [ebp-1Ch]
  float v9; // [esp+28h] [ebp-8h]
  float v10; // [esp+2Ch] [ebp-4h]
  Vec3 v11; // 0:^1C.12

  invert_matrix_from_source(out, from);
  multiply_matrix_assign(out, to);
  interpolate_matrix_rotation(out, alpha);
  premultiply_matrix_in_place(out, from);
  orthogonalize_matrix(out);
  v9 = alpha * to->position.y;
  v10 = alpha * to->position.z;
  v5 = 1.0 - alpha;
  v6 = v5 * from->position.x;
  v7 = v5 * from->position.y;
  v8 = v5 * from->position.z;
  v11.x = v6 + alpha * to->position.x;
  v11.y = v7 + v9;
  v11.z = v8 + v10;
  out->position = v11;
}
