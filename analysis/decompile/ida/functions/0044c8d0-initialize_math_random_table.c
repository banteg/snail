/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_math_random_table @ 0x44c8d0 */
/* selector: initialize_math_random_table */

// Fills the shared 0x1fff-entry gameplay random table from the underlying linear-congruential generator and resets the ring index. Android symbols match this helper family to `gRMathRand2Init()`.
int sub_44C8D0()
{
  int *v0; // esi
  int result; // eax

  v0 = &MEMORY[0x787F8C];
  do
  {
    result = rand();
    *v0++ = result;
  }
  while ( (int)v0 < (int)&MEMORY[0x78FF88] );
  MEMORY[0x77FF3C] = 0;
  return result;
}

