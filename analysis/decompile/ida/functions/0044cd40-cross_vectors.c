/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: cross_vectors @ 0x44cd40 */
/* selector: cross_vectors */

// Exact void `Vector3::cross_vectors(const Vector3&, const Vector3&)` member: computes the 3D cross product of two const-reference operands through a function-local static temporary and copies it into its receiver, matching iOS and Android `tVector::Cross(const tVector&, const tVector&)`.
void __thiscall cross_vectors(Vec3 *out, const Vec3 *lhs, const Vec3 *rhs)
{
  if ( (LOBYTE(cross_vectors_static_guard[0]) & 1) == 0 )
  {
    LOBYTE(cross_vectors_static_guard[0]) |= 1u;
    atexit(destroy_cross_vectors_static_result);
  }
  cross_vectors_static_result[0] = lhs->y * rhs->z - rhs->y * lhs->z;
  cross_vectors_static_result[1] = lhs->z * rhs->x - lhs->x * rhs->z;
  flt_77FF88[0] = rhs->y * lhs->x - lhs->y * rhs->x;
  out->x = cross_vectors_static_result[0];
  out->y = cross_vectors_static_result[1];
  out->z = flt_77FF88[0];
}
