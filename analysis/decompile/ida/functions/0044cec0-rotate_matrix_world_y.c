/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: rotate_matrix_world_y @ 0x44cec0 */
/* selector: rotate_matrix_world_y */

int32_t __thiscall rotate_matrix_world_y(TransformMatrix *transform, float angle)
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
  v6 = v5 * transform->basis_right.x + anglea * transform->basis_forward.x;
  transform->basis_right.x = anglea * transform->basis_right.x - v5 * transform->basis_forward.x;
  transform->basis_forward.x = v6;
  v7 = v5 * transform->basis_right.y + anglea * transform->basis_forward.y;
  transform->basis_right.y = anglea * transform->basis_right.y - v5 * transform->basis_forward.y;
  transform->basis_forward.y = v7;
  v8 = anglea * transform->basis_right.z - v5 * transform->basis_forward.z;
  v9 = v5 * transform->basis_right.z + anglea * transform->basis_forward.z;
  transform->basis_right.z = v8;
  transform->basis_forward.z = v9;
  return result;
}

