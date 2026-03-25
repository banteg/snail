/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_anim_manager @ 0x4447d0 */
/* selector: update_anim_manager */

// Advances one queued presentation animation channel, applying loop, bounce, or clamp flags and starting the next queued entry when the current one finishes.
void __thiscall sub_4447D0(char *this)
{
  int v1; // eax
  int v2; // edx
  bool v3; // zf
  __int16 v4; // ax
  _BYTE *v5; // eax
  double v6; // st7
  double v7; // st7
  _DWORD *v8; // eax
  int v9; // esi
  int v10; // esi
  int v11; // edi
  int v12; // esi
  float v13; // [esp+8h] [ebp-4h]

  v1 = *(_DWORD *)this;
  v2 = 0;
  v3 = *(_DWORD *)this == 0;
  *(this + 16) = 0;
  if ( !v3 )
  {
    if ( v1 == 1 )
    {
      v13 = (*((float *)MEMORY[0x4DF904] + 119186) + *((float *)MEMORY[0x4DF904] + 119186) - 0.2 + 1.0)
          * *((float *)this + 2)
          + *((float *)this + 1);
      *((float *)this + 1) = v13;
      if ( v13 >= 1.0 )
      {
        v4 = **((_WORD **)this + 3);
        if ( (v4 & 1) != 0 )
        {
          *(this + 16) = 1;
          *((float *)this + 1) = v13 - 1.0;
        }
        else if ( (v4 & 4) != 0 )
        {
          *((_DWORD *)this + 1) = 1065336439;
          *((_DWORD *)this + 2) = 0;
          *(this + 16) = 1;
        }
        else if ( (v4 & 2) != 0 )
        {
          *((float *)this + 1) = 2.0 - v13;
          *((float *)this + 2) = *((float *)this + 2) * -1.0;
        }
      }
      if ( *((float *)this + 1) < 0.0 )
      {
        v5 = *((_BYTE **)this + 3);
        if ( (*v5 & 2) != 0 )
        {
          *((float *)this + 1) = -*((float *)this + 1);
          v6 = *((float *)this + 2) * -1.0;
          *(this + 16) = 1;
          *((float *)this + 2) = v6;
        }
        if ( (*v5 & 8) != 0 )
        {
          *((_DWORD *)this + 1) = 0;
          *((_DWORD *)this + 2) = 0;
          *(this + 16) = 1;
        }
      }
      if ( *((float *)this + 1) >= 0.0 )
      {
        if ( *((float *)this + 1) <= 0.99989998 )
          v7 = *((float *)this + 1);
        else
          v7 = 0.99989998;
      }
      else
      {
        v7 = 0.0;
      }
      *((float *)this + 1) = v7;
    }
    if ( *(this + 16) && *((int *)this + 15) > 0 )
    {
      v8 = this + 20;
      if ( *((_DWORD *)this + 5) == -1 )
      {
        v9 = *((_DWORD *)this + 16);
        *((_DWORD *)this + 1) = 0;
        *((_DWORD *)this + 2) = 0;
        *(_DWORD *)(v9 + 4) &= ~0x20u;
      }
      else
      {
        *(_DWORD *)(*((_DWORD *)this + 16) + 4) |= 0x20u;
        v10 = (*v8 << 7) + *((_DWORD *)this + 17) + 36;
        v11 = *(_DWORD *)(*(_DWORD *)v10 + 188);
        *((_DWORD *)this + 1) = 0;
        *((_DWORD *)this + 3) = v11;
        *((_DWORD *)this + 2) = *(_DWORD *)(v11 + 16);
        *(_DWORD *)(*((_DWORD *)this + 16) + 36) = *(_DWORD *)v10;
      }
      v12 = *((_DWORD *)this + 15) - 1;
      *((_DWORD *)this + 15) = v12;
      if ( v12 > 0 )
      {
        do
        {
          ++v2;
          *v8 = v8[1];
          ++v8;
        }
        while ( v2 < *((_DWORD *)this + 15) );
      }
    }
  }
}

