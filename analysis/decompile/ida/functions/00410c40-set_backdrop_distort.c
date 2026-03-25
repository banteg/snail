/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_backdrop_distort @ 0x410c40 */
/* selector: set_backdrop_distort */

// Seeds the shared backdrop distortion grid and its per-cell phase, speed, and amplitude terms from the script-side Distort scalar. Cross-port Android and iOS symbols match this helper to `cRBackdrop::SetDistort(float)`.
float *__thiscall sub_410C40(float *this, float a2)
{
  int i; // edi
  int j; // esi
  float *v5; // ebx
  float *result; // eax

  for ( i = 0; i < 64; i += 8 )
  {
    for ( j = 0; j < 8; ++j )
    {
      if ( !j || !i || j == 7 || i == 56 )
      {
        result = this + 6 * i + 6 * j;
        result[22] = 0.0;
        result[23] = 0.0;
        *(this + 6 * i + 6 * j + 24) = 0.0;
        result[25] = 0.0;
      }
      else
      {
        v5 = this + 6 * i + 6 * j;
        v5[22] = (double)next_math_random_value() * 0.0001917476;
        v5[23] = 1.0 / (((double)next_math_random_value() * 0.000061035156 + 3.0) * 60.0) * 6.2831855;
        *(this + 6 * i + 6 * j + 24) = ((double)next_math_random_value() - 16384.0) * a2 * 0.000061035156;
        result = (float *)next_math_random_value();
        v5[25] = ((double)(int)result - 16384.0) * a2 * 0.000061035156;
      }
    }
  }
  return result;
}

