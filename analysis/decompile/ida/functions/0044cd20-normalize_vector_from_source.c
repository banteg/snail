/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: normalize_vector_from_source @ 0x44cd20 */
/* selector: normalize_vector_from_source */

// Copies a source vector and normalizes it in place. Android symbols match this helper to `tVector::Normalize(const tVector&)`.
double __thiscall normalize_vector_from_source(Vec3 *out, Vec3 *src)
{
  *out = *src;
  return normalize_vector(out);
}

