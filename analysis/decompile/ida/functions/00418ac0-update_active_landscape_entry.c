/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_active_landscape_entry @ 0x418ac0 */
/* selector: update_active_landscape_entry */

// Advances one active landscape-entry runtime by counting down its activation delay, shifting its lateral offset, and toggling its shared visibility bit as it moves into or out of the backdrop camera band.
char __thiscall update_active_landscape_entry(int this)
{
  int v1; // eax
  int v2; // edx
  int v3; // esi

  LOBYTE(v1) = (_BYTE)MEMORY[0x4DF904];
  if ( !*((_BYTE *)MEMORY[0x4DF904] + 476705) )
  {
    v1 = *(_DWORD *)(this + 128);
    if ( v1 )
    {
      if ( !--v1 )
      {
        v2 = *(_DWORD *)(this + 36);
        v3 = *(_DWORD *)(this + 140);
        if ( *(float *)(v3 + 112) - 10.0 > *(float *)(v2 + 184) + *(float *)(this + 112) )
          *(float *)(this + 112) = *(float *)(this + 136) * 3.0 + *(float *)(this + 112);
        v1 = *(_DWORD *)(this + 4);
        if ( *((float *)MEMORY[0x4DF904] + 3) + *(float *)(v3 + 112) >= *(float *)(v2 + 172) + *(float *)(this + 112) )
          LOBYTE(v1) = v1 | 0x20;
        else
          LOBYTE(v1) = v1 & 0xDF;
        *(_DWORD *)(this + 4) = v1;
      }
    }
  }
  return v1;
}

