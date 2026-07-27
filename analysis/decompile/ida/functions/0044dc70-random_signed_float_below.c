/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: random_signed_float_below @ 0x44dc70 */
/* selector: random_signed_float_below */

// Exact Windows `SRAND(float, char*)` implementation: returns a centered random float in `[-scale, scale)` by shifting the engine RNG around zero before scaling by the supplied magnitude. The release body ignores the retained debug-tag argument.
float __cdecl random_signed_float_below(float upper_bound, char *tag)
{
  return ((double)j_rand() - 16384.0) * upper_bound * 0.000061035156;
}
