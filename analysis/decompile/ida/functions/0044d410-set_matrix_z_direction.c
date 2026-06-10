/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_matrix_z_direction @ 0x44d410 */
/* selector: set_matrix_z_direction */

void __thiscall set_matrix_z_direction(TransformMatrix *transform, const Vec3 *direction)
{
  bool v3; // c3
  float x; // ecx
  float y; // edx
  float v6; // eax
  float z; // ecx
  Vec3 vector; // [esp+8h] [ebp-18h] BYREF
  Vec3 out; // [esp+14h] [ebp-Ch] BYREF

  if ( normalize_vector_from_source(&out, direction) != 0.0 )
  {
    v3 = out.x == 0.0;
    x = out.x;
    y = out.y;
    transform->basis_forward.z = out.z;
    transform->basis_forward.x = x;
    transform->basis_forward.y = y;
    if ( v3 && out.z == 0.0 )
    {
      vector.x = 1.0;
      vector.z = 0.0;
    }
    else
    {
      vector.z = -out.x;
      vector.x = out.z;
    }
    vector.y = 0.0;
    normalize_vector(&vector);
    v6 = vector.y;
    z = vector.z;
    transform->basis_right.x = vector.x;
    transform->basis_right.y = v6;
    transform->basis_right.z = z;
    cross_vectors((Vec3 *)&transform->basis_up, &out, &vector);
  }
}

