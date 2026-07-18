/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_uniform_scale_matrix @ 0x44cde0 */
/* selector: initialize_uniform_scale_matrix */

// Stable Windows harness identity for the authored single-float `tMatrix::tMatrix(float)` constructor retained by Android. The exact constructor writes the scalar across the xyz diagonal, zeroes off-diagonal and translation slots, and sets homogeneous `w` to 1.0.
TransformMatrix *__thiscall initialize_uniform_scale_matrix(TransformMatrix *transform, float scale)
{
  transform->basis_right.x = scale;
  transform->basis_right.y = 0.0;
  transform->basis_right.z = 0.0;
  transform->basis_right.w = 0.0;
  transform->basis_up.x = 0.0;
  transform->basis_up.y = scale;
  transform->basis_up.z = 0.0;
  transform->basis_up.w = 0.0;
  transform->basis_forward.x = 0.0;
  transform->basis_forward.y = 0.0;
  transform->basis_forward.z = scale;
  transform->basis_forward.w = 0.0;
  transform->position.x = 0.0;
  transform->position.y = 0.0;
  transform->position.z = 0.0;
  transform->position.w = 1.0;
  return transform;
}
