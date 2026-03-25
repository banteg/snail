/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: change_backdrop @ 0x410d50 */
/* selector: change_backdrop */

// Binds one parsed background script entry into the shared backdrop renderer, including its texture handles, Distort scalar, and split-vs-single draw mode. Cross-port Android and iOS symbols match this helper to `cRBackdrop::Change(cRLandscape*, bool)`.
char __thiscall sub_410D50(int this, int a2, char a3)
{
  char result; // al
  int v4; // edx
  int v5; // esi

  result = a2;
  v4 = 0;
  v5 = *(_DWORD *)(a2 + 132);
  if ( *(_BYTE *)(a2 + 136) )
  {
    if ( v5 )
    {
      v4 = 1;
      *(_BYTE *)(this + 57) = 1;
      *(_BYTE *)(this + 76) = 1;
      *(_DWORD *)(this + 64) = *(_DWORD *)(a2 + 132);
      *(_DWORD *)(this + 72) = *(_DWORD *)(a2 + 132) + 1;
LABEL_6:
      *(_DWORD *)(this + 80) = *(_DWORD *)(a2 + 288);
      result = a3;
      *(_BYTE *)(this + 84) = a3;
    }
  }
  else if ( v5 )
  {
    *(_BYTE *)(this + 57) = 0;
    v4 = 1;
    *(_BYTE *)(this + 76) = 1;
    *(_DWORD *)(this + 64) = *(_DWORD *)(a2 + 132);
    goto LABEL_6;
  }
  *(_DWORD *)(this + 1624) = v4;
  return result;
}

