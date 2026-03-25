/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: rotate_matrix_world_z @ 0x44cf50 */
/* selector: rotate_matrix_world_z */

int32_t __thiscall rotate_matrix_world_z(PathTemplateTransform *transform, float angle)
{
  int32_t result; // eax
  double v5; // st7
  double v6; // st6
  double v7; // st6
  double v8; // st6
  double v9; // st7
  float anglea; // [esp+Ch] [ebp+4h]

  anglea = cosine(angle);
  v5 = sine(angle);
  v6 = anglea * transform->basis_right.x + v5 * transform->basis_up.x;
  transform->basis_up.x = anglea * transform->basis_up.x - v5 * transform->basis_right.x;
  transform->basis_right.x = v6;
  v7 = v5 * transform->basis_up.y + anglea * transform->basis_right.y;
  transform->basis_up.y = anglea * transform->basis_up.y - v5 * transform->basis_right.y;
  transform->basis_right.y = v7;
  v8 = anglea * transform->basis_up.z - v5 * transform->basis_right.z;
  v9 = v5 * transform->basis_up.z + anglea * transform->basis_right.z;
  transform->basis_up.z = v8;
  transform->basis_right.z = v9;
  return result;
}

