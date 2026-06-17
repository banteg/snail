/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_salt_hazard @ 0x441c10 */
/* selector: update_salt_hazard */

// Advances one live salt hazard's fade state from the shared track z thresholds, updates its alpha tint, and retires the object from the active list once it crosses the far cutoff.
void __thiscall update_salt_hazard(int this)
{
  int v2; // eax
  int v3; // ecx
  char *v4; // ecx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  double v9; // st7
  char v11; // c0

  v2 = *(_DWORD *)(this + 136);
  if ( !*(_BYTE *)(v2 + 9) )
  {
    v3 = *(_DWORD *)(this + 128) - 1;
    if ( *(_DWORD *)(this + 128) == 1 )
    {
      v9 = 1.0 - (*(float *)(this + 112) - *(float *)(v2 + 3913684)) * 0.021739131;
      *(float *)(this + 140) = v9;
      if ( v11 )
      {
        v9 = 0.0;
      }
      else if ( v9 > 1.0 )
      {
        v9 = 1.0;
      }
      *(float *)(this + 140) = v9;
      set_color_alpha((_DWORD *)(this + 40), 1063675494);
      if ( *(float *)(this + 112) < (double)*(float *)(*(_DWORD *)(this + 136) + 3924196) )
        *(_DWORD *)(this + 128) = 2;
    }
    else if ( v3 == 1 )
    {
      v4 = (char *)MEMORY[0x4DF904] + 1448;
      v5 = *(_DWORD *)(this + 4);
      if ( (v5 & 0x200) != 0 )
      {
        if ( (v5 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
          *(_DWORD *)(this + 128) = 0;
        }
        else
        {
          v6 = *(_DWORD *)(this + 12);
          if ( v6 )
            *(_DWORD *)(v6 + 8) = *(_DWORD *)(this + 8);
          v7 = *(_DWORD *)(this + 8);
          if ( v7 )
            *(_DWORD *)(v7 + 12) = *(_DWORD *)(this + 12);
          else
            *((_DWORD *)v4 + 1) = *(_DWORD *)(this + 12);
          *(_DWORD *)(this + 12) = *((_DWORD *)v4 + 2);
          *((_DWORD *)v4 + 2) = this;
          v8 = *(_DWORD *)(this + 4);
          *(_DWORD *)(this + 128) = 0;
          BYTE1(v8) &= ~2u;
          *(_DWORD *)(this + 4) = v8;
        }
      }
      else
      {
        report_errorf(aListRemove);
        *(_DWORD *)(this + 128) = 0;
      }
    }
  }
}

