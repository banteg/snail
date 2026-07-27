/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_math_random_table @ 0x44c8d0 */
/* selector: initialize_math_random_table */

// Exact void Windows `gRMathRand2Init()` platform implementation: fills the shared 0x1fff-entry gameplay random table from the underlying generator and resets the ring index.
void __cdecl initialize_math_random_table()
{
  int *v0; // esi

  v0 = g_math_random_table;
  do
    *v0++ = rand();
  while ( (int)v0 < (int)&g_sound_effect_manager );
  g_math_random_index = 0;
}
