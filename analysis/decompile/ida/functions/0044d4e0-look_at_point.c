/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: look_at_point @ 0x44d4e0 */
/* selector: look_at_point */

TransformMatrix *__thiscall look_at_point(TransformMatrix *transform, Vec3 *target)
{
  Vec3 v3; // [esp+Ch] [ebp-Ch] BYREF
  Vec3 v4; // 0:^4.12

  v4.x = target->x - transform->position.x;
  v4.y = target->y - transform->position.y;
  v4.z = target->z - transform->position.z;
  v3 = v4;
  return (TransformMatrix *)set_matrix_z_direction(transform, &v3);
}

