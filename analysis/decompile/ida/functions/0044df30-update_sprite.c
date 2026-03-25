/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_sprite @ 0x44df30 */
/* selector: update_sprite */

void __thiscall sub_44DF30(int this)
{
  int v1; // edx
  double v2; // st7
  unsigned __int8 v4; // c0
  unsigned __int8 v5; // c3
  double v6; // st7
  int v7; // eax
  int v8; // eax
  __int16 v9; // si
  double v10; // st7
  unsigned __int8 v12; // c0
  unsigned __int8 v13; // c3
  int v14; // edx
  int v15; // eax

  v1 = *(_DWORD *)(this + 4);
  if ( (v1 & 0x800) != 0 && unk_790F30 )
    return;
  if ( (v1 & 8) != 0 )
  {
    *(_DWORD *)(this + 4) = v1 & 0xFFFFFFF7;
LABEL_12:
    v7 = *(_DWORD *)(this + 4);
    LOBYTE(v7) = v7 & 0xF7;
    *(_DWORD *)(this + 4) = v7;
    *(_DWORD *)(this + 60) = *(_DWORD *)(this + 72);
    *(_DWORD *)(this + 64) = *(_DWORD *)(this + 76);
    *(_DWORD *)(this + 68) = *(_DWORD *)(this + 80);
    *(float *)(this + 72) = *(float *)(this + 84) + *(float *)(this + 72);
    *(float *)(this + 76) = *(float *)(this + 88) + *(float *)(this + 76);
    *(float *)(this + 80) = *(float *)(this + 92) + *(float *)(this + 80);
    *(float *)(this + 88) = *(float *)(this + 120) + *(float *)(this + 88);
    *(float *)(this + 124) = *(float *)(this + 128) + *(float *)(this + 124);
    v8 = *(_DWORD *)(this + 4);
    if ( *(float *)(this + 116) <= 0.0 )
      BYTE1(v8) &= ~2u;
    else
      BYTE1(v8) |= 2u;
    v9 = v8;
    *(_DWORD *)(this + 4) = v8;
    if ( (v8 & 0x2000) != 0 )
    {
      v10 = *(float *)(this + 176) + *(float *)(this + 172);
      *(float *)(this + 172) = v10;
      if ( !(v12 | v13) )
      {
        v14 = *(_DWORD *)(this + 168) + *(_DWORD *)(this + 164);
        v15 = *(_DWORD *)(this + 160);
        *(float *)(this + 172) = v10 - 1.0;
        *(_DWORD *)(this + 164) = v14;
        if ( (v9 & 0x4000) != 0 )
        {
          if ( v14 == v15 )
          {
            *(_DWORD *)(this + 168) = -1;
            *(_DWORD *)(this + 164) = v15 - 1;
          }
          if ( *(_DWORD *)(this + 164) == -1 )
          {
            *(_DWORD *)(this + 164) = 0;
            *(_DWORD *)(this + 168) = 1;
          }
        }
        else if ( v14 == v15 )
        {
          *(_DWORD *)(this + 164) = 0;
        }
        set_sprite_texture_ref((_DWORD *)this, *(_DWORD *)(this + 156), *(_DWORD *)(this + 164));
      }
    }
    return;
  }
  v2 = *(float *)(this + 108) + *(float *)(this + 104);
  *(float *)(this + 104) = v2;
  if ( v4 | v5 && v2 >= 0.0 )
  {
    if ( *(float *)(this + 116) != 0.0 )
    {
      v6 = *(float *)(this + 116) + *(float *)(this + 112);
      *(float *)(this + 112) = v6;
      if ( v6 > 1.0 )
        *(_DWORD *)(this + 116) = 0;
    }
    goto LABEL_12;
  }
  *(_DWORD *)(this + 104) = 1065353216;
  if ( (v1 & 0x100) == 0 )
    kill_sprite(this);
}

