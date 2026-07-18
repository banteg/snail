/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: rotate_matrix_world_z @ 0x44cf50 */
/* database symbol: rotate_matrix_local_z */
/* selector: rotate_matrix_world_z */

// Stable Windows harness identity for the exact void `TransformMatrix::rotate_matrix_local_z(float)` member, retained by iOS and Android as `tMatrix::RotLocalZ(float)`. It rotates the right/up basis around the matrix's local Z axis.
void __thiscall rotate_matrix_local_z(TransformMatrix *transform, float angle)
{
  double v4; // st7
  double v5; // st6
  double v6; // st6
  double v7; // st6
  double v8; // st7
  float anglea; // [esp+Ch] [ebp+4h]

  anglea = cosine(angle);
  v4 = sine(angle);
  v5 = anglea * transform->basis_right.x + v4 * transform->basis_up.x;
  transform->basis_up.x = anglea * transform->basis_up.x - v4 * transform->basis_right.x;
  transform->basis_right.x = v5;
  v6 = v4 * transform->basis_up.y + anglea * transform->basis_right.y;
  transform->basis_up.y = anglea * transform->basis_up.y - v4 * transform->basis_right.y;
  transform->basis_right.y = v6;
  v7 = anglea * transform->basis_up.z - v4 * transform->basis_right.z;
  v8 = v4 * transform->basis_up.z + anglea * transform->basis_right.z;
  transform->basis_up.z = v7;
  transform->basis_right.z = v8;
}
