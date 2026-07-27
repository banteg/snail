/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_trigonometry_tables @ 0x44c930 */
/* selector: initialize_trigonometry_tables */

// Windows `RMathInit()` platform implementation: builds the shared cosine and sine lookup tables used by the gameplay math wrappers during startup, then invokes `gRMathRand2Init()`. Mobile performs the same phases with different table extents and also initializes its color defaults.
void __cdecl initialize_trigonometry_tables()
{
  int v0; // eax
  double v1; // st7
  long double v2; // st7
  int v3; // [esp+0h] [ebp-4h]

  v0 = 0;
  v3 = 0;
  do
  {
    v1 = (double)v3;
    v3 = ++v0;
    v2 = v1 * 0.00012207031 * 6.2831855;
    cross_vectors_static_guard[v0] = cos(v2);
    flt_77FF88[v0] = sin(v2);
  }
  while ( v0 < 0x2000 );
  initialize_math_random_table();
}
