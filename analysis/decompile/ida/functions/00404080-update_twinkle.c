/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_twinkle @ 0x404080 */
/* selector: update_twinkle */

void __thiscall sub_404080(float *this)
{
  double v2; // st7
  unsigned __int8 v4; // c0
  unsigned __int8 v5; // c3
  double v6; // st7
  double v7; // st7
  double v8; // st7
  int v9; // eax
  double v10; // st7
  int v11; // eax
  int v12; // edi
  double v13; // st7
  double v14; // st6
  int v15; // edi
  int v16; // [esp+8h] [ebp-8h]

  v2 = *(this + 6) + *(this + 7);
  *(this + 6) = v2;
  if ( v4 | v5 )
  {
    if ( v2 < 0.0 )
      *(this + 6) = v2 + 6.2831855;
  }
  else
  {
    *(this + 6) = v2 - 6.2831855;
  }
  switch ( *(_DWORD *)this )
  {
    case 1:
      v9 = *(_DWORD *)(*((_DWORD *)this + 11) + 416);
      if ( (v9 & 2) != 0 && (v9 & 0x8000) == 0 )
      {
        v10 = *(this + 2) + *(this + 3);
        *(this + 2) = v10;
        if ( v10 > 1.0 )
        {
          *(_DWORD *)this = 2;
          *(this + 4) = 0.0;
          *(this + 5) = 0.89999998;
          *(this + 6) = ((double)next_math_random_value() - 16384.0) * 0.0001917476;
          if ( ((double)next_math_random_value() - 16384.0) * 0.000061035156 >= 0.0 )
            v16 = ((double)next_math_random_value() - 16384.0) * 0.000061035156 != 0.0;
          else
            v16 = -1;
          v11 = next_math_random_value();
          *(this + 2) = 0.0;
          v12 = *((_DWORD *)this + 11);
          *(this + 3) = 1.0;
          *(this + 7) = 1.0 / ((((double)v11 - 16384.0) * 0.000061035156 + 5.0) * 60.0) * (double)v16 * 6.2831855;
          v13 = (double)next_math_random_value() * (*(float *)(v12 + 584) * 0.80000001) * 0.000030517578
              + *(float *)(v12 + 568);
          v14 = *(float *)(v12 + 584) * 0.1;
          v15 = *((_DWORD *)this + 11);
          *(this + 8) = v13 + v14;
          *(this + 9) = (double)next_math_random_value() * (*(float *)(v15 + 588) * 0.80000001) * 0.000030517578
                      + *(float *)(v15 + 588) * 0.1
                      + *(float *)(v15 + 572);
          *(this + 10) = ((double)next_math_random_value() - 16384.0) * 0.00073242188 + 25.0;
        }
      }
      break;
    case 2:
      v7 = (*(this + 5) - *(this + 4)) * 0.1 + *(this + 4);
      *(this + 4) = v7;
      v8 = *(this + 5) - v7;
      if ( v8 < 0.0 )
        v8 = -v8;
      if ( v8 < 0.0099999998 )
      {
        *(this + 5) = 0.0;
        *(_DWORD *)this = 4;
      }
      draw_twinkle();
      break;
    case 4:
      *(this + 4) = (*(this + 5) - *(this + 4)) * 0.1 + *(this + 4);
      draw_twinkle();
      v6 = *(this + 5) - *(this + 4);
      if ( v6 < 0.0 )
        v6 = -v6;
      if ( v6 < 0.0099999998 )
      {
        *(_DWORD *)this = 1;
        *(this + 4) = 0.0;
        *(this + 2) = 0.0;
        *(this + 3) = 1.0 / (((double)next_math_random_value() * 0.000030517578 + 0.0099999998) * 60.0);
      }
      break;
  }
}

