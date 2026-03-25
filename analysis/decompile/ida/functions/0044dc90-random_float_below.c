/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: random_float_below @ 0x44dc90 */
/* selector: random_float_below */

// Returns a uniform random float in `[0, upper_bound)` by scaling the engine RNG output with the supplied upper bound.
double __cdecl sub_44DC90(float a1)
{
  return (double)j__rand() * a1 * 0.000030517578;
}

