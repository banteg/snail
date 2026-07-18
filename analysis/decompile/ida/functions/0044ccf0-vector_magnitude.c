/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: vector_magnitude @ 0x44ccf0 */
/* selector: vector_magnitude */

// Exact const `Vector3::vector_magnitude()` member: returns sqrt(x*x + y*y + z*z) as float without mutating its receiver, matching iOS and Android `tVector::Magnitude() const`.
float __thiscall vector_magnitude(const Vec3 *vector)
{
  float v3; // [esp+0h] [ebp-4h]

  v3 = vector->x * vector->x + vector->y * vector->y + vector->z * vector->z;
  return square_root(v3);
}
