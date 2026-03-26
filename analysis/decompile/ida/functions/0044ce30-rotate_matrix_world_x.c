/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: rotate_matrix_world_x @ 0x44ce30 */
/* selector: rotate_matrix_world_x */

void __thiscall rotate_matrix_world_x(TransformMatrix *transform, float angle)
{
  double v4; // st7
  double v5; // st6
  double v6; // st6
  double v7; // st6
  double v8; // st7
  float anglea; // [esp+Ch] [ebp+4h]

  anglea = cosine(angle);
  v4 = sine(angle);
  v5 = v4 * transform->basis_forward.x + anglea * transform->basis_up.x;
  transform->basis_forward.x = anglea * transform->basis_forward.x - v4 * transform->basis_up.x;
  transform->basis_up.x = v5;
  v6 = v4 * transform->basis_forward.y + anglea * transform->basis_up.y;
  transform->basis_forward.y = anglea * transform->basis_forward.y - v4 * transform->basis_up.y;
  transform->basis_up.y = v6;
  v7 = anglea * transform->basis_forward.z - v4 * transform->basis_up.z;
  v8 = v4 * transform->basis_forward.z + anglea * transform->basis_up.z;
  transform->basis_forward.z = v7;
  transform->basis_up.z = v8;
}

