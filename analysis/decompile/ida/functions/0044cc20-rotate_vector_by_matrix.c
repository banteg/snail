/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: rotate_vector_by_matrix @ 0x44cc20 */
/* selector: rotate_vector_by_matrix */

// Exact reference-returning `Vector3::rotate_vector_by_matrix(const TransformMatrix&)` harness for Android/iOS `tVector::Rotate(const tMatrix&)`. It applies only the 3x3 rotational basis in place; sprite-facing callers consume the returned receiver.
Vec3 *__thiscall rotate_vector_by_matrix(Vec3 *vector, const TransformMatrix *matrix)
{
  Vec3 v3; // 0:^0.12

  v3 = *vector;
  vector->x = vector->z * matrix->basis_forward.x + vector->y * matrix->basis_up.x + vector->x * matrix->basis_right.x;
  vector->y = v3.z * matrix->basis_forward.y + v3.y * matrix->basis_up.y + v3.x * matrix->basis_right.y;
  vector->z = v3.z * matrix->basis_forward.z + v3.y * matrix->basis_up.z + v3.x * matrix->basis_right.z;
  return vector;
}
