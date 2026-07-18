/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_matrix_identity @ 0x44d210 */
/* selector: set_matrix_identity */

// Exact void `TransformMatrix::set_matrix_identity()` method: resets the complete 4x4 transform including translation, matching mobile `tMatrix::Identity()`.
void __thiscall set_matrix_identity(TransformMatrix *transform)
{
  transform->position.w = 1.0;
  transform->basis_forward.z = 1.0;
  transform->basis_up.y = 1.0;
  transform->basis_right.x = 1.0;
  transform->position.z = 0.0;
  transform->position.y = 0.0;
  transform->position.x = 0.0;
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
