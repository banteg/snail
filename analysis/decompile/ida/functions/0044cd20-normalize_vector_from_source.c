/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: normalize_vector_from_source @ 0x44cd20 */
/* selector: normalize_vector_from_source */

// Exact float-returning `Vector3::normalize_vector_from_source(const Vector3&)` member: copies a const-reference source into its receiver, normalizes it, and returns the prior magnitude. Android retains `tVector::Normalize(const tVector&)`.
float __thiscall normalize_vector_from_source(Vec3 *out, const Vec3 *src)
{
  *out = *src;
  return normalize_vector(out);
}
