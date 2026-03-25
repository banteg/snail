/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: random_signed_float_below @ 0x44dc70 */
/* selector: random_signed_float_below */

// Returns a centered random float in `[-scale, scale)` by shifting the engine RNG around zero before scaling by the supplied magnitude.
double __cdecl sub_44DC70(float a1)
{
  return ((double)j__rand() - 16384.0) * a1 * 0.000061035156;
}

