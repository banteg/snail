/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_active_bod @ 0x433e80 */
/* selector: update_active_bod */

// Implements the default active-bod subtype callback by recycling a live bod to the free list once its world-z plus the native 24-unit buffer falls behind the current subgame cutoff.
void __thiscall sub_433E80(int this)
{
  int v1; // eax
  char *v2; // edx
  int v3; // eax
  int v4; // eax
  int v5; // eax

  if ( *(float *)(this + 56) + 24.0 < *((float *)MEMORY[0x4DF904] + 1100223) )
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

