/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_matrix_rotation_identity @ 0x44d250 */
/* selector: set_matrix_rotation_identity */

// Exact void `TransformMatrix::set_matrix_rotation_identity()` method: resets the rotational basis and homogeneous row while preserving translation, matching mobile `tMatrix::RotIdentity()`.
void __thiscall set_matrix_rotation_identity(TransformMatrix *transform)
{
  transform->position.w = 1.0;
  transform->basis_forward.z = 1.0;
  transform->basis_up.y = 1.0;
  transform->basis_right.x = 1.0;
  transform->basis_forward.w = 0.0;
  transform->basis_forward.y = 0.0;
  transform->basis_forward.x = 0.0;
  transform->basis_up.w = 0.0;
  transform->basis_up.z = 0.0;
  transform->basis_up.x = 0.0;
  transform->basis_right.w = 0.0;
  transform->basis_right.z = 0.0;
  transform->basis_right.y = 0.0;
}
