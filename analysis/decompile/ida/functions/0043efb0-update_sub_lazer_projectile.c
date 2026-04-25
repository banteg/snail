/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_sub_lazer_projectile @ 0x43efb0 */
/* selector: update_sub_lazer_projectile */

// Advances one live SubLazer projectile slot: integrates motion, handles state 1→2→cleanup via list-remove and `kill_sprite`, and modulates the sprite y by `sin(phase*2π)*0.3`. Historically labelled `update_wall2_ambient_hazard`; the Wall2 tile is the emitter, the slot itself is a projectile.
void __thiscall update_wall2_ambient_hazard(int this)
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  char *v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // ecx
  double v13; // st7
  unsigned __int8 v15; // c0
  unsigned __int8 v16; // c3
  float v17; // [esp+0h] [ebp-Ch]

  if ( !*(_BYTE *)(*(_DWORD *)(this + 68) + 9) )
  {
    v2 = *(_DWORD *)(this + 56);
    if ( v2 )
    {
      v3 = v2 - 1;
      if ( v3 )
      {
        if ( v3 == 1 )
        {
          v4 = *(_DWORD *)(this + 4);
          *(_DWORD *)(this + 56) = 0;
          v5 = (char *)MEMORY[0x4DF904] + 1448;
          if ( (v4 & 0x200) == 0 )
          {
LABEL_6:
            report_errorf(aListRemove);
            kill_sprite(*(_DWORD *)(this + 100));
            return;
          }
          if ( (v4 & 0x40) != 0 )
            goto LABEL_8;
          v6 = *(_DWORD *)(this + 12);
          if ( v6 )
            *(_DWORD *)(v6 + 8) = *(_DWORD *)(this + 8);
          v7 = *(_DWORD *)(this + 8);
          if ( v7 )
          {
            *(_DWORD *)(v7 + 12) = *(_DWORD *)(this + 12);
LABEL_21:
            *(_DWORD *)(this + 12) = *((_DWORD *)v5 + 2);
            *((_DWORD *)v5 + 2) = this;
            v11 = *(_DWORD *)(this + 4);
            v12 = *(_DWORD *)(this + 100);
            BYTE1(v11) &= ~2u;
            *(_DWORD *)(this + 4) = v11;
            kill_sprite(v12);
            return;
          }
          goto LABEL_20;
        }
      }
      else if ( *(float *)(this + 24) < (double)*(float *)(*(_DWORD *)(this + 60) + 10624) )
      {
        v8 = *(_DWORD *)(this + 4);
        *(_DWORD *)(this + 56) = 0;
        v5 = (char *)MEMORY[0x4DF904] + 1448;
        if ( (v8 & 0x200) == 0 )
          goto LABEL_6;
        if ( (v8 & 0x40) != 0 )
        {
LABEL_8:
          report_errorf(aListRemoveNext);
          kill_sprite(*(_DWORD *)(this + 100));
          return;
        }
        v9 = *(_DWORD *)(this + 12);
        if ( v9 )
          *(_DWORD *)(v9 + 8) = *(_DWORD *)(this + 8);
        v10 = *(_DWORD *)(this + 8);
        if ( v10 )
        {
          *(_DWORD *)(v10 + 12) = *(_DWORD *)(this + 12);
          goto LABEL_21;
        }
LABEL_20:
        *((_DWORD *)v5 + 1) = *(_DWORD *)(this + 12);
        goto LABEL_21;
      }
      v13 = *(float *)(this + 112) + *(float *)(this + 108);
      *(float *)(this + 108) = v13;
      if ( !(v15 | v16) )
        *(float *)(this + 108) = v13 - 1.0;
      v17 = *(float *)(this + 108) * 6.2831855;
      *(float *)(*(_DWORD *)(this + 100) + 76) = sine(v17) * 0.30000001 + *(float *)(this + 20);
    }
  }
}

