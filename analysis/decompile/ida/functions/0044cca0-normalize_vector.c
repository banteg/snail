/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: normalize_vector @ 0x44cca0 */
/* selector: normalize_vector */

double __fastcall normalize_vector(Vec3 *vector)
{
  double result; // st7
  float v3; // [esp+0h] [ebp-8h]

  v3 = dot_vectors(&vector->x, &vector->x);
  result = square_root(v3);
  if ( result == 0.0 )
    return 0.0;
  vector->x = 1.0 / result * vector->x;
  vector->y = 1.0 / result * vector->y;
  vector->z = 1.0 / result * vector->z;
  return result;
}

