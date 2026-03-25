/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_intro_screen @ 0x419920 */
/* selector: destroy_intro_screen */

// Unlinks each intro or credits crawl renderable from the active body lists and returns it to the shared free list before the text screen exits. Cross-port Android symbols match this helper to `cRIntro::UnInit()`.
int __thiscall sub_419920(int *this)
{
  int result; // eax
  int v3; // edi
  _DWORD *v4; // esi
  int v5; // eax
  char *v6; // ecx
  int v7; // eax
  int v8; // eax

  byte_4DF934 = *(this + 3);
  if ( *((_BYTE *)MEMORY[0x4DF904] + 781) == 1 )
    *((_DWORD *)MEMORY[0x4DF904] + 110) = 20;
  else
    *((_DWORD *)MEMORY[0x4DF904] + 110) = 3;
  result = *(this + 5);
  v3 = 0;
  if ( result > 0 )
  {
    v4 = this + 9;
    do
    {
      v5 = *(v4 - 2);
      v6 = (char *)MEMORY[0x4DF904] + 1448;
      if ( (v5 & 0x200) != 0 )
      {
        if ( (v5 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          if ( *v4 )
            *(_DWORD *)(*v4 + 8) = *(v4 - 1);
          v7 = *(v4 - 1);
          if ( v7 )
            *(_DWORD *)(v7 + 12) = *v4;
          else
            *((_DWORD *)v6 + 1) = *v4;
          *v4 = *((_DWORD *)v6 + 2);
          *((_DWORD *)v6 + 2) = v4 - 3;
          v8 = *(v4 - 2);
          BYTE1(v8) &= ~2u;
          *(v4 - 2) = v8;
        }
      }
      else
      {
        report_errorf(aListRemove);
      }
      result = *(this + 5);
      ++v3;
      v4 += 36;
    }
    while ( v3 < result );
  }
  return result;
}

