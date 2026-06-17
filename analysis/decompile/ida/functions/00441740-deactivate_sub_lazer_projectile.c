/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: deactivate_sub_lazer_projectile @ 0x441740 */
/* selector: deactivate_sub_lazer_projectile */

// Marks a sub-lazer projectile slot inactive after collision or after it leaves the supported path.
__int16 __thiscall sub_441740(_DWORD *this)
{
  char *v2; // ecx
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax

  v2 = (char *)MEMORY[0x4DF904] + 1448;
  v3 = *(this + 1);
  if ( (v3 & 0x200) != 0 )
  {
    if ( (v3 & 0x40) != 0 )
    {
      LOWORD(v4) = report_errorf(aListRemoveNext);
      *(this + 32) = 0;
    }
    else
    {
      v5 = *(this + 3);
      if ( v5 )
        *(_DWORD *)(v5 + 8) = *(this + 2);
      v6 = *(this + 2);
      if ( v6 )
        *(_DWORD *)(v6 + 12) = *(this + 3);
      else
        *((_DWORD *)v2 + 1) = *(this + 3);
      *(this + 3) = *((_DWORD *)v2 + 2);
      *((_DWORD *)v2 + 2) = this;
      v4 = *(this + 1);
      *(this + 32) = 0;
      BYTE1(v4) &= ~2u;
      *(this + 1) = v4;
    }
  }
  else
  {
    LOWORD(v4) = report_errorf(aListRemove);
    *(this + 32) = 0;
  }
  return v4;
}

