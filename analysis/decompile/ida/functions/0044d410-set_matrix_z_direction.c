/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_matrix_z_direction @ 0x44d410 */
/* selector: set_matrix_z_direction */

int32_t __thiscall set_matrix_z_direction(TransformMatrix *transform, Vec3 *direction)
{
  double v3; // st7
  bool v4; // c0
  char v5; // c2
  bool v6; // c3
  __int16 v7; // fps
  int32_t result; // eax
  bool v9; // c3
  float x; // ecx
  float y; // edx
  float v12; // eax
  float z; // ecx
  Vec3 v14; // [esp+8h] [ebp-18h] BYREF
  Vec3 v15; // [esp+14h] [ebp-Ch] BYREF

  v3 = normalize_vector_from_source(&v15, direction);
  v4 = v3 < 0.0;
  v5 = 0;
  v6 = v3 == 0.0;
  LOWORD(result) = v7;
  if ( v3 != 0.0 )
  {
    v9 = v15.x == 0.0;
    x = v15.x;
    y = v15.y;
    transform->basis_forward.z = v15.z;
    transform->basis_forward.x = x;
    transform->basis_forward.y = y;
    if ( v9 && v15.z == 0.0 )
    {
      v14.x = 1.0;
      v14.z = 0.0;
    }
    else
    {
      v14.z = -v15.x;
      v14.x = v15.z;
    }
    v14.y = 0.0;
    normalize_vector(&v14);
    v12 = v14.y;
    z = v14.z;
    transform->basis_right.x = v14.x;
    transform->basis_right.y = v12;
    transform->basis_right.z = z;
    return cross_vectors((Vec3 *)&transform->basis_up, &v15, &v14);
  }
  return result;
}

