/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: next_math_random_value @ 0x44c900 */
/* selector: next_math_random_value */

// Advances the shared gameplay random-table index modulo 0x1fff and returns the next cached 15-bit value. Android symbols match this helper family to the shared `Rand()` / `gRMathRand2()` accessors.
int sub_44C900()
{
  MEMORY[0x77FF3C] = (MEMORY[0x77FF3C] + 1) % 0x1FFF;
  return MEMORY[0x787F8C][MEMORY[0x77FF3C]];
}

