/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: look_at_point @ 0x44d4e0 */
/* selector: look_at_point */

void __thiscall look_at_point(TransformMatrix *transform, const Vec3 *target)
{
  Vec3 v2; // [esp+Ch] [ebp-Ch] BYREF
  Vec3 v3; // 0:^4.12

  v3.x = target->x - transform->position.x;
  v3.y = target->y - transform->position.y;
  v3.z = target->z - transform->position.z;
  v2 = v3;
  set_matrix_z_direction(transform, &v2);
}

