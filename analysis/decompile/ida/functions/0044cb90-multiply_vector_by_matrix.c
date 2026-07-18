/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: multiply_vector_by_matrix @ 0x44cb90 */
/* selector: multiply_vector_by_matrix */

// Exact void by-value `Vector3::operator*=(TransformMatrix)` retained by iOS as `tVector::operator*=(tMatrix)`. It applies the affine basis and translation in place; Android exposes the analogous operation as `tVector::Multiply(const tMatrix&)`.
void __thiscall multiply_vector_by_matrix(Vec3 *vector, TransformMatrix matrix)
{
  Vec3 v2; // 0:^0.12

  v2 = *vector;
  vector->x = vector->z * matrix.basis_forward.x
            + vector->y * matrix.basis_up.x
            + vector->x * matrix.basis_right.x
            + matrix.position.x;
  vector->y = matrix.basis_forward.y * v2.z + matrix.basis_up.y * v2.y + matrix.basis_right.y * v2.x + matrix.position.y;
  vector->z = matrix.basis_forward.z * v2.z + matrix.basis_up.z * v2.y + matrix.basis_right.z * v2.x + matrix.position.z;
}
