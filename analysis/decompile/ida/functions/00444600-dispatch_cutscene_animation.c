/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: dispatch_cutscene_animation @ 0x444600 */
/* selector: dispatch_cutscene_animation */

// Either queues one cutscene or presentation animation id onto the player-side channel or begins it immediately, resetting the live slot state when the immediate path wins.
int __thiscall sub_444600(int this, int a2, char a3, int a4)
{
  _WORD *v4; // eax
  int v5; // edx
  double v7; // st7
  char v8; // c0
  double v9; // st7
  int v10; // edx
  double v12; // st7
  char v13; // c0
  int v14; // eax
  int v15; // ecx
  int result; // eax

  if ( a3 )
  {
    v4 = *(_WORD **)(*(_DWORD *)((a2 << 7) + this + 368) + 188);
    *(_DWORD *)(this + 272) = v4;
    if ( a4 != -1 )
      *v4 = a4;
    v5 = *(_DWORD *)(this + 272);
    if ( (*(_BYTE *)v5 & 8) != 0 )
    {
      v7 = *(float *)(v5 + 16);
      if ( v8 )
        v7 = -v7;
      v9 = -v7;
      *(float *)(this + 268) = v9;
      *(float *)(this + 264) = v9 + 1.0;
    }
    else
    {
      v10 = *(_DWORD *)(this + 272);
      *(_DWORD *)(this + 264) = 0;
      v12 = *(float *)(v10 + 16);
      if ( v13 )
        v12 = -v12;
      *(float *)(this + 268) = v12;
    }
    v14 = *(_DWORD *)((a2 << 7) + this + 368);
    *(_DWORD *)(this + 320) = 0;
    *(_DWORD *)(this + 36) = v14;
    v15 = *(_DWORD *)(this + 324);
    result = *(_DWORD *)(v15 + 4);
    LOBYTE(result) = result | 0x20;
    *(_DWORD *)(v15 + 4) = result;
  }
  else
  {
    *(_DWORD *)(this + 4 * *(_DWORD *)(this + 320) + 280) = a2;
    result = *(_DWORD *)(this + 320) + 1;
    *(_DWORD *)(this + 320) = result;
  }
  return result;
}

