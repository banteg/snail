/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: multiply_vector_by_matrix_copy @ 0x44cac0 */
/* selector: multiply_vector_by_matrix_copy */

// Stable Windows harness identity for the exact value-returning `Vector3::operator*(const TransformMatrix&) const`. Its hidden output pointer exposes the ordinary VC6 aggregate-return ABI. Android and iOS retain `tVector::operator*(const tMatrix&) const`.
Vec3 *__thiscall multiply_vector_by_matrix_copy(const Vec3 *vector, Vec3 *out, const TransformMatrix *matrix)
{
  Vec3 v4; // 0:^0.12

  v4.x = matrix->basis_forward.x * vector->z
       + matrix->basis_up.x * vector->y
       + matrix->basis_right.x * vector->x
       + matrix->position.x;
  v4.y = matrix->basis_forward.y * vector->z
       + matrix->basis_right.y * vector->x
       + matrix->basis_up.y * vector->y
       + matrix->position.y;
  v4.z = matrix->basis_forward.z * vector->z
       + matrix->basis_right.z * vector->x
       + matrix->basis_up.z * vector->y
       + matrix->position.z;
  *out = v4;
  return out;
}
