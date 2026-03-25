/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_garbage_hazard @ 0x43f130 */
/* selector: destroy_garbage_hazard */

// Removes one live garbage hazard from the active body lists, kills its sprite, and unlinks it from the active garbage chain after collision or expiry. Cross-port Android symbols match this helper to `cRSubGarbage::Kill()`.
int *__thiscall sub_43F130(int *this)
{
  char *v2; // ecx
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int *result; // eax
  int *v9; // ecx

  *(this + 33) = 0;
  v2 = (char *)MEMORY[0x4DF904] + 1448;
  v3 = *(this + 1);
  if ( (v3 & 0x200) != 0 )
  {
    if ( (v3 & 0x40) != 0 )
    {
      report_errorf(aListRemoveNext);
    }
    else
    {
      v4 = *(this + 3);
      if ( v4 )
        *(_DWORD *)(v4 + 8) = *(this + 2);
      v5 = *(this + 2);
      if ( v5 )
        *(_DWORD *)(v5 + 12) = *(this + 3);
      else
        *((_DWORD *)v2 + 1) = *(this + 3);
      *(this + 3) = *((_DWORD *)v2 + 2);
      *((_DWORD *)v2 + 2) = this;
      v6 = *(this + 1);
      BYTE1(v6) &= ~2u;
      *(this + 1) = v6;
    }
  }
  else
  {
    report_errorf(aListRemove);
  }
  kill_sprite(*(this + 45));
  v7 = *(this + 35);
  result = *(int **)(v7 + 3510592);
  if ( result == this )
  {
    result = (int *)*(this + 32);
    *(_DWORD *)(v7 + 3510592) = result;
  }
  else if ( result )
  {
    while ( 1 )
    {
      v9 = (int *)result[32];
      if ( v9 == this )
        break;
      result = (int *)result[32];
      if ( !v9 )
        return result;
    }
    result[32] = *(this + 32);
    *(this + 32) = 0;
  }
  return result;
}

