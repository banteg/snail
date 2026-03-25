/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_matrix_rotation_identity @ 0x44d250 */
/* selector: set_matrix_rotation_identity */

// Resets the rotational basis and homogeneous row to identity while preserving the translation slots. Android symbols match this helper to `tMatrix::RotIdentity()`.
int32_t __fastcall set_matrix_rotation_identity(TransformMatrix *transform)
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
  return 0;
}

