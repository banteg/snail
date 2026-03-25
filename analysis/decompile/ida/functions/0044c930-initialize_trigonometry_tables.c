/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_trigonometry_tables @ 0x44c930 */
/* selector: initialize_trigonometry_tables */

// Builds the shared cosine and sine lookup tables used by the gameplay math wrappers during startup, then resets the companion random table state.
int sub_44C930()
{
  int v0; // eax
  double v1; // st7
  long double v2; // st7
  int v4; // [esp+0h] [ebp-4h]

  v0 = 0;
  v4 = 0;
  do
  {
    v1 = (double)v4;
    v4 = ++v0;
    v2 = v1 * 0.00012207031 * 6.2831855;
    MEMORY[0x777F38][v0] = cos(v2);
    MEMORY[0x77FF88][v0] = sin(v2);
  }
  while ( v0 < 0x2000 );
  return initialize_math_random_table();
}

