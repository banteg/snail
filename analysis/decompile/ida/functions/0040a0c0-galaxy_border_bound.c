/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: galaxy_border_bound @ 0x40a0c0 */
/* selector: galaxy_border_bound */

void __stdcall sub_40A0C0(float *a1, float *a2, float *a3, float *a4, int a5)
{
  double v5; // st7
  double v6; // st7
  double v7; // st7
  double v8; // st7

  if ( *(_DWORD *)(a5 + 604) == 2 )
  {
    v5 = *a2 - *a1;
    if ( v5 < *(float *)(a5 + 584) )
    {
      v6 = *a1 - (*(float *)(a5 + 584) - v5) * 0.5;
      *a1 = v6;
      *a1 = (*(float *)(a5 + 584) - (*a2 - v6)) * 0.5 + v6;
    }
  }
  else
  {
    if ( *(float *)(a5 + 568) < (double)*a1 )
      *a1 = *(float *)(a5 + 568);
    v8 = *(float *)(a5 + 584) + *(float *)(a5 + 568);
    if ( v8 > *a2 )
      *a2 = v8;
  }
  if ( *(float *)(a5 + 572) < (double)*a3 )
    *a3 = *(float *)(a5 + 572);
  v7 = *(float *)(a5 + 588) + *(float *)(a5 + 572);
  if ( v7 > *a4 )
    *a4 = v7;
}

