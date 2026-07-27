/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: random_float_below @ 0x44dc90 */
/* selector: random_float_below */

// Exact Windows `RAND(float, char*)` implementation: returns a uniform random float in `[0, upper_bound)` by scaling the engine RNG output with the supplied upper bound. The release body ignores the retained debug-tag argument.
float __cdecl random_float_below(float upper_bound, char *tag)
{
  return (double)j_rand() * upper_bound * 0.000030517578;
}
