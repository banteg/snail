/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_matrix_z_direction @ 0x44d410 */
/* selector: set_matrix_z_direction */

void __thiscall set_matrix_z_direction(TransformMatrix *transform, Vec3 *direction)
{
  bool v3; // c3
  float x; // ecx
  float y; // edx
  float v6; // eax
  float z; // ecx
  Vec3 v8; // [esp+8h] [ebp-18h] BYREF
  Vec3 v9; // [esp+14h] [ebp-Ch] BYREF

  if ( normalize_vector_from_source(&v9, direction) != 0.0 )
  {
    v3 = v9.x == 0.0;
    x = v9.x;
    y = v9.y;
    transform->basis_forward.z = v9.z;
    transform->basis_forward.x = x;
    transform->basis_forward.y = y;
    if ( v3 && v9.z == 0.0 )
    {
      v8.x = 1.0;
      v8.z = 0.0;
    }
    else
    {
      v8.z = -v9.x;
      v8.x = v9.z;
    }
    v8.y = 0.0;
    normalize_vector(&v8);
    v6 = v8.y;
    z = v8.z;
    transform->basis_right.x = v8.x;
    transform->basis_right.y = v6;
    transform->basis_right.z = z;
    cross_vectors((Vec3 *)&transform->basis_up, &v9, &v8);
  }
}

