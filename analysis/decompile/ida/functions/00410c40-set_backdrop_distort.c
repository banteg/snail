/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_backdrop_distort @ 0x410c40 */
/* selector: set_backdrop_distort */

// Seeds the shared backdrop distortion grid and its per-cell phase, speed, and amplitude terms from the script-side Distort scalar. Cross-port Android and iOS symbols match this helper to `cRBackdrop::SetDistort(float)`.
void __thiscall set_backdrop_distort(Backdrop *backdrop, float distort)
{
  int i; // edi
  int j; // esi
  float *v5; // ebx
  uint8_t *v6; // eax

  for ( i = 0; i < 8; ++i )
  {
    for ( j = 0; j < 8; ++j )
    {
      if ( !j || !(i * 8) || j == 7 || i == 7 )
      {
        v6 = &backdrop->bod_base[3 * i + 24 * j];
        *((_DWORD *)v6 + 22) = 0;
        *((_DWORD *)v6 + 23) = 0;
        backdrop->distort_grid[i][j].x_offset = 0.0;
        *((_DWORD *)v6 + 25) = 0;
      }
      else
      {
        v5 = (float *)&backdrop->bod_base[3 * i + 24 * j];
        v5[22] = (double)next_math_random_value() * 0.0001917476;
        v5[23] = 1.0 / (((double)next_math_random_value() * 0.000061035156 + 3.0) * 60.0) * 6.2831855;
        backdrop->distort_grid[i][j].x_offset = ((double)next_math_random_value() - 16384.0) * distort * 0.000061035156;
        v5[25] = ((double)next_math_random_value() - 16384.0) * distort * 0.000061035156;
      }
    }
  }
}
