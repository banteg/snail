/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: rotate_matrix_world_y @ 0x44cec0 */
/* database symbol: rotate_matrix_local_y */
/* selector: rotate_matrix_world_y */

// Stable Windows harness identity for the exact void `TransformMatrix::rotate_matrix_local_y(float)` member, retained by iOS and Android as `tMatrix::RotLocalY(float)`. It rotates the right/forward basis around the matrix's local Y axis.
void __thiscall rotate_matrix_local_y(TransformMatrix *transform, float angle)
{
  double v4; // st7
  double v5; // st6
  double v6; // st6
  double v7; // st6
  double v8; // st7
  float anglea; // [esp+Ch] [ebp+4h]

  anglea = cosine(angle);
  v4 = sine(angle);
  v5 = v4 * transform->basis_right.x + anglea * transform->basis_forward.x;
  transform->basis_right.x = anglea * transform->basis_right.x - v4 * transform->basis_forward.x;
  transform->basis_forward.x = v5;
  v6 = v4 * transform->basis_right.y + anglea * transform->basis_forward.y;
  transform->basis_right.y = anglea * transform->basis_right.y - v4 * transform->basis_forward.y;
  transform->basis_forward.y = v6;
  v7 = anglea * transform->basis_right.z - v4 * transform->basis_forward.z;
  v8 = v4 * transform->basis_right.z + anglea * transform->basis_forward.z;
  transform->basis_right.z = v7;
  transform->basis_forward.z = v8;
}
