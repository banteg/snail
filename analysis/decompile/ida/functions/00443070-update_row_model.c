/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_row_model @ 0x443070 */
/* selector: update_row_model */

void __thiscall update_row_model(int this)
{
  int v1; // eax
  char *v2; // edx
  int v3; // eax
  int v4; // eax
  int v5; // eax

  *(float *)(this + 104) = *(float *)(this + 128) + *(float *)(this + 104);
  *(float *)(this + 108) = *(float *)(this + 132) + *(float *)(this + 108);
  *(float *)(this + 112) = *(float *)(this + 136) + *(float *)(this + 112);
  if ( *(float *)(*(_DWORD *)(this + 36) + 184) + *((float *)MEMORY[0x4DF904] + 1100223) > *(float *)(this + 112) )
  {
    v1 = *(_DWORD *)(this + 4);
    v2 = (char *)MEMORY[0x4DF904] + 1448;
    if ( (v1 & 0x200) != 0 )
    {
      if ( (v1 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        v3 = *(_DWORD *)(this + 12);
        if ( v3 )
          *(_DWORD *)(v3 + 8) = *(_DWORD *)(this + 8);
        v4 = *(_DWORD *)(this + 8);
        if ( v4 )
          *(_DWORD *)(v4 + 12) = *(_DWORD *)(this + 12);
        else
          *((_DWORD *)v2 + 1) = *(_DWORD *)(this + 12);
        *(_DWORD *)(this + 12) = *((_DWORD *)v2 + 2);
        *((_DWORD *)v2 + 2) = this;
        v5 = *(_DWORD *)(this + 4);
        BYTE1(v5) &= ~2u;
        *(_DWORD *)(this + 4) = v5;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
  }
}

