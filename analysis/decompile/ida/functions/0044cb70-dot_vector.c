/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: dot_vector @ 0x44cb70 */
/* selector: dot_vector */

// Exact float-returning `Vector3::dot_vector(const Vector3&)` member: computes the 3D dot product against one const-reference operand, matching iOS and Android `tVector::Dot(const tVector&)`.
float __thiscall dot_vector(const Vec3 *vector, const Vec3 *rhs)
{
  return rhs->z * vector->z + rhs->y * vector->y + rhs->x * vector->x;
}
