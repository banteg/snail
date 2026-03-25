/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: advance_timer_counters @ 0x441b90 */
/* selector: advance_timer_counters */

// Accumulates one generic timer record from a 60 Hz-scaled delta, rolls the frame counter at 60, and refreshes the derived hundredths and thousandths fields from the fractional remainder.
__int64 __thiscall sub_441B90(float *this, float a2)
{
  double v2; // st7
  double v3; // st7
  char v5; // c0
  int v6; // edx
  double v7; // st7

  v2 = a2 * 0.016666668;
  *this = v2 + *this;
  v3 = v2 + *(this + 5);
  *(this + 5) = v3;
  if ( !v5 )
  {
    v6 = *((_DWORD *)this + 2) + 1;
    *((_DWORD *)this + 2) = v6;
    *(this + 5) = v3 - 1.0;
    if ( v6 >= 60 )
    {
      *((_DWORD *)this + 2) = v6 - 60;
      ++*((_DWORD *)this + 1);
    }
  }
  v7 = *(this + 5) * 1000.0;
  *((_DWORD *)this + 3) = (__int64)(*(this + 5) * 100.0);
  *((_DWORD *)this + 4) = (__int64)v7;
  return (__int64)v7;
}

