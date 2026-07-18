/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: normalize_vector @ 0x44cca0 */
/* selector: normalize_vector */

// Exact float-returning `Vector3::normalize_vector()` member: normalizes its receiver in place and returns the prior magnitude, matching iOS and Android `tVector::Normalize()`.
float __thiscall normalize_vector(Vec3 *vector)
{
  long double v2; // st7
  float v4; // [esp+0h] [ebp-8h]

  v4 = dot_vectors(vector, vector);
  v2 = square_root(v4);
  if ( v2 == 0.0 )
  {
    return 0.0;
  }
  else
  {
    vector->x = 1.0 / v2 * vector->x;
    vector->y = 1.0 / v2 * vector->y;
    vector->z = 1.0 / v2 * vector->z;
  }
  return v2;
}
