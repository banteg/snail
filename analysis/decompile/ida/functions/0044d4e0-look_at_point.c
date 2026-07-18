/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: look_at_point @ 0x44d4e0 */
/* selector: look_at_point */

// Exact void `TransformMatrix::look_at_point(const Vector3&)` method: subtracts the matrix position from a world-space target and forwards the resulting direction to SetZDir, matching mobile `tMatrix::LookAt(tVector const&)`.
void __thiscall look_at_point(TransformMatrix *transform, const Vec3 *target)
{
  Vec3 direction; // [esp+Ch] [ebp-Ch] BYREF
  Vec3 v3; // 0:^4.12

  v3.x = target->x - transform->position.x;
  v3.y = target->y - transform->position.y;
  v3.z = target->z - transform->position.z;
  direction = v3;
  set_matrix_z_direction(transform, &direction);
}
