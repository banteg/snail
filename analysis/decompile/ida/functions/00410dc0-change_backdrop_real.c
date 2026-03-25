/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: change_backdrop_real @ 0x410dc0 */
/* selector: change_backdrop_real */

// Commits the pending backdrop selection, refreshes the distortion grid when the world index changes, and copies the current split-vs-single draw flags into the active renderer state. Cross-port Android and iOS symbols match this helper to `cRBackdrop::ChangeReal()`.
char __thiscall sub_410DC0(int this)
{
  int v2; // eax
  char v3; // dl
  int v4; // eax
  char v5; // dl

  v2 = *(_DWORD *)(this + 64);
  if ( v2 )
  {
    if ( v2 != *(_DWORD *)(this + 60) )
    {
      *(_DWORD *)(this + 60) = v2;
      *(_DWORD *)(this + 68) = *(_DWORD *)(this + 72);
    }
    *(_DWORD *)(this + 1736) = 0;
    set_backdrop_distort((float *)this, *(float *)(this + 80));
    v3 = *(_BYTE *)(this + 84);
    LOBYTE(v4) = *(_BYTE *)(this + 57);
    *(_DWORD *)(this + 1624) = 1;
    *(_BYTE *)(this + 85) = v3;
    *(_BYTE *)(this + 56) = v4;
  }
  else
  {
    v5 = *(_BYTE *)(this + 84);
    v4 = *(unsigned __int8 *)(this + 57);
    *(_DWORD *)(this + 1624) = 0;
    *(_BYTE *)(this + 85) = v5;
    *(_BYTE *)(this + 56) = v4;
  }
  return v4;
}

