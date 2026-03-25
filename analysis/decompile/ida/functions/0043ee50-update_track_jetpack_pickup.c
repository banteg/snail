/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_track_jetpack_pickup @ 0x43ee50 */
/* selector: update_track_jetpack_pickup */

void __thiscall update_track_jetpack_pickup(int this)
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

  if ( !*(_BYTE *)(*(_DWORD *)(this + 140) + 9) )
  {
    v2 = *(_DWORD *)(this + 128);
    if ( v2 )
    {
      v3 = v2 - 1;
      if ( v3 )
      {
        if ( v3 != 1 )
          return;
        v4 = *(_DWORD *)(this + 4);
        *(_DWORD *)(this + 128) = 0;
        v5 = (char *)MEMORY[0x4DF904] + 1448;
        if ( (v4 & 0x200) == 0 )
          goto LABEL_6;
        if ( (v4 & 0x40) != 0 )
        {
LABEL_8:
          report_errorf(aListRemoveNext);
          kill_sprite(*(_DWORD *)(this + 172));
          return;
        }
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
          v12 = *(_DWORD *)(this + 172);
          BYTE1(v11) &= ~2u;
          *(_DWORD *)(this + 4) = v11;
          kill_sprite(v12);
          return;
        }
      }
      else
      {
        if ( *(float *)(this + 112) >= (double)*(float *)(*(_DWORD *)(this + 132) + 10624) )
          return;
        v8 = *(_DWORD *)(this + 4);
        *(_DWORD *)(this + 128) = 0;
        v5 = (char *)MEMORY[0x4DF904] + 1448;
        if ( (v8 & 0x200) == 0 )
        {
LABEL_6:
          report_errorf(aListRemove);
          kill_sprite(*(_DWORD *)(this + 172));
          return;
        }
        if ( (v8 & 0x40) != 0 )
          goto LABEL_8;
        v9 = *(_DWORD *)(this + 12);
        if ( v9 )
          *(_DWORD *)(v9 + 8) = *(_DWORD *)(this + 8);
        v10 = *(_DWORD *)(this + 8);
        if ( v10 )
        {
          *(_DWORD *)(v10 + 12) = *(_DWORD *)(this + 12);
          goto LABEL_21;
        }
      }
      *((_DWORD *)v5 + 1) = *(_DWORD *)(this + 12);
      goto LABEL_21;
    }
  }
}

