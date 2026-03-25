/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: calc_subgame_rate @ 0x4404d0 */
/* selector: calc_subgame_rate */

void __thiscall sub_4404D0(int this)
{
  double v2; // st7
  int v3; // eax
  double v4; // st7
  double v5; // st7
  int v6; // edx
  double v7; // st7
  float v8; // [esp+0h] [ebp-Ch]
  float v9; // [esp+8h] [ebp-4h]

  if ( *(_DWORD *)(this + 60) != 2 )
  {
    *(_DWORD *)(this + 56) = *(_DWORD *)(this + 48);
    return;
  }
  v2 = *(float *)(this + 3913684) / (double)*(int *)(this + 88);
  if ( v2 >= 0.0 )
  {
    if ( v2 > 1.0 )
      v2 = 1.0;
  }
  else
  {
    v2 = 0.0;
  }
  v3 = *(_DWORD *)(this + 64);
  if ( v3 == 1 || v3 == 3 )
  {
    v5 = v2 * 0.55000001;
    goto LABEL_12;
  }
  if ( v3 != 4 )
  {
    v5 = v2 * 0.2;
LABEL_12:
    v4 = v5 + *(float *)(this + 48);
    goto LABEL_13;
  }
  v4 = v2 * 0.40000001 + *(float *)(this + 48) + 0.2;
LABEL_13:
  v6 = *(_DWORD *)(this + 3914536);
  *(float *)(this + 56) = v4;
  if ( v6 == 2 )
  {
    if ( v3 == 1 || (v9 = 0.60000002, v3 == 4) )
      v9 = 0.40000001;
    if ( *(float *)(this + 3914568) < 0.25 || *(float *)(this + 3914568) > 0.75 )
    {
      v8 = *(float *)(this + 3914568) * 12.566371 + 1.5707964;
      v7 = (1.0 - sine(v8)) * 0.5 * v9;
    }
    else
    {
      v7 = v9;
    }
    *(float *)(this + 56) = v7 + *(float *)(this + 56);
  }
  if ( *(_DWORD *)(this + 3923648) == 1 )
    *(float *)(this + 56) = *(float *)(this + 3924160) * 0.5 + *(float *)(this + 56);
}

