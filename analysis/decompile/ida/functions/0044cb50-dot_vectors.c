/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: dot_vectors @ 0x44cb50 */
/* selector: dot_vectors */

// Exact static `Vector3::dot_vectors(const Vector3&, const Vector3&)` overload: computes the 3D dot product of two const-reference operands and returns it as double, matching Android `tVector::Dot(const tVector&, const tVector&)`.
double __stdcall dot_vectors(const Vec3 *lhs, const Vec3 *rhs)
{
  return lhs->z * rhs->z + lhs->y * rhs->y + lhs->x * rhs->x;
}
