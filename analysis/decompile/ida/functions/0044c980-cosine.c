/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: cosine @ 0x44c980 */
/* selector: cosine */

// Computes one cosine value through the shared gameplay trigonometry wrapper. Android symbols match this helper to `Cos(float)`.
double __cdecl sub_44C980(float a1)
{
  int v1; // ecx
  long double v2; // st7

  v1 = (__int64)(a1 * 0.15915494 * 8192.0) & 0x1FFF;
  v2 = MEMORY[0x777F3C][v1] - cos(a1);
  if ( v2 < 0.0 )
    v2 = -v2;
  if ( v2 > 0.02 )
  {
    while ( 1 )
      ;
  }
  return MEMORY[0x777F3C][v1];
}

