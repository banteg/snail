/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_backdrop_distort @ 0x410c40 */
/* selector: set_backdrop_distort */

// Seeds the shared backdrop distortion grid and its per-cell phase, speed, and amplitude terms from the script-side Distort scalar. Cross-port Android and iOS symbols match this helper to `cRBackdrop::SetDistort(float)`.
void __thiscall set_backdrop_distort(cRBackdrop *backdrop, float distort)
{
  int i; // edi
  int j; // esi
  float *v5; // ebx
  void **v6; // eax

  for ( i = 0; i < 64; i += 8 )
  {
    for ( j = 0; j < 8; ++j )
    {
      if ( j == 0 || i == 0 || j == 7 || i == 56 )
      {
        v6 = &backdrop->bod.bod.vtable + 6 * i + 6 * j;
        v6[22] = nullptr;
        v6[23] = nullptr;
        backdrop->distort_grid[i / 8u][j].x_offset = 0.0;
        v6[25] = nullptr;
      }
      else
      {
        v5 = (float *)((char *)backdrop + 24 * i + 24 * j);
        v5[22] = (double)next_math_random_value() * 0.0001917476;
        v5[23] = 1.0 / (((double)next_math_random_value() * 0.000061035156 + 3.0) * 60.0) * 6.2831855;
        backdrop->distort_grid[i / 8u][j].x_offset = ((double)next_math_random_value() - 16384.0)
                                                   * distort
                                                   * 0.000061035156;
        v5[25] = ((double)next_math_random_value() - 16384.0) * distort * 0.000061035156;
      }
    }
  }
}
