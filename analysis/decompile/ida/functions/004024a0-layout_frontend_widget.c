/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: layout_frontend_widget @ 0x4024a0 */
/* selector: layout_frontend_widget */

// Recomputes one front-end widget's authored-space position, measured text bounds, and any attached slider-child offsets before the current frame draw.
float *__thiscall sub_4024A0(int this)
{
  float *result; // eax
  int v3; // edx
  _DWORD *v4; // ebx
  float *v5; // edi
  int v6; // eax
  int v7; // ecx
  float v8; // edx
  int v9; // ecx
  double v10; // st7
  double v11; // st7
  double v12; // st7
  float v13; // [esp+10h] [ebp-4h]

  while ( 1 )
  {
    result = *(float **)(this + 416);
    if ( (BYTE1(result) & 8) != 0 )
    {
      v3 = *(_DWORD *)(this + 572);
      v4 = (_DWORD *)(this + 568);
      v5 = (float *)(this + 572);
      *(_DWORD *)(this + 1780) = *(_DWORD *)(this + 568);
      *(_DWORD *)(this + 1784) = v3;
    }
    else if ( ((unsigned int)result & 0x10000) != 0 )
    {
      v6 = *(_DWORD *)(this + 76);
      v7 = *(_DWORD *)(this + 80);
      v4 = (_DWORD *)(this + 568);
      v5 = (float *)(this + 572);
      *(_DWORD *)(this + 584) = *(_DWORD *)(this + 84);
      *(_DWORD *)(this + 568) = v6;
      result = *(float **)(this + 88);
      *(_DWORD *)(this + 572) = v7;
      *(_DWORD *)(this + 588) = result;
    }
    else
    {
      v5 = (float *)(this + 572);
      v4 = (_DWORD *)(this + 568);
      result = layout_and_queue_wrapped_font_text(
                 (char *)(this + 716),
                 *(_DWORD *)(this + 1772),
                 *(_DWORD *)(this + 1776),
                 *(float *)(this + 1780),
                 *(float *)(this + 1784),
                 (float *)(this + 568),
                 (float *)(this + 572),
                 (float *)(this + 584),
                 (float *)(this + 588),
                 *(_DWORD *)(this + 552),
                 BYTE1(byte_4DF934) & 1,
                 *(_DWORD *)(this + 604),
                 *(_DWORD *)(this + 608),
                 0x1000000,
                 this + 492,
                 1,
                 0);
    }
    v8 = *v5;
    *(_DWORD *)(this + 576) = *v4;
    v9 = *(_DWORD *)(this + 416);
    *(float *)(this + 580) = v8;
    if ( (v9 & 0x20000000) != 0 )
      break;
    if ( *(float *)v4 + *(float *)(this + 536) + *(float *)(this + 584) <= 640.0 )
    {
      if ( *(float *)v4 - *(float *)(this + 536) < 0.0 )
        *(_DWORD *)(this + 576) = *(_DWORD *)(this + 536);
    }
    else
    {
      *(float *)(this + 576) = 640.0 - *(float *)(this + 536) - *(float *)(this + 584);
    }
    if ( *(float *)(this + 536) + *v5 <= 480.0 )
    {
      if ( *v5 - *(float *)(this + 536) < 0.0 )
        *(_DWORD *)(this + 580) = *(_DWORD *)(this + 536);
    }
    else
    {
      *(float *)(this + 580) = 480.0 - *(float *)(this + 536);
    }
    v10 = *(float *)(this + 576) - *(float *)v4;
    result = (float *)(v9 & 0x100000);
    *(float *)(this + 608) = v10 + *(float *)(this + 608);
    *(float *)(this + 1780) = v10 + *(float *)(this + 1780);
    *(float *)(this + 1784) = *(float *)(this + 580) - *v5 + *(float *)(this + 1784);
    v11 = *(float *)(this + 576);
    *(float *)v4 = *(float *)(this + 576);
    v13 = *(float *)(this + 580);
    *v5 = v13;
    if ( (v9 & 0x100000) != 0 )
    {
      *(float *)(this + 388) = *(float *)(this + 584) * 0.1 + v11 + 4.0 - 12.0;
      *(float *)(this + 392) = *(float *)(this + 584) * 0.80000001 + v11 - 4.0;
      v12 = *(float *)(this + 588) * 0.5 + v13;
      *(float *)(this + 396) = v12 - 6.0;
      *(float *)(this + 400) = v12 + 32.0 - 6.0;
    }
    if ( !result )
      break;
    *(float *)(*(_DWORD *)(this + 1820) + 572) = *(float *)(this + 580) + 33.0;
    layout_frontend_widget(*(_DWORD *)(this + 1820));
    *(float *)(*(_DWORD *)(this + 1816) + 572) = *(float *)(this + 580) + 33.0;
    layout_frontend_widget(*(_DWORD *)(this + 1816));
    *(float *)(*(_DWORD *)(this + 1824) + 1784) = *(float *)(this + 580) + 49.0;
    this = *(_DWORD *)(this + 1824);
  }
  return result;
}

