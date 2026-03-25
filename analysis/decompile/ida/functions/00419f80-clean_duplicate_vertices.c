/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: clean_duplicate_vertices @ 0x419f80 */
/* selector: clean_duplicate_vertices */

int __thiscall sub_419F80(int *this, int a2)
{
  int result; // eax
  int v3; // ebx
  int v4; // edi
  int v5; // esi
  int v6; // edx
  int v7; // eax

  result = *this;
  v3 = 0;
  if ( *this > 0 )
  {
    v4 = 0;
    do
    {
      v5 = v3;
      if ( v3 < result )
      {
        v6 = v4;
        do
        {
          v7 = *(this + 1);
          if ( *(_WORD *)(v6 + v7) == *(_WORD *)(v4 + v7 + 2) )
            *(_WORD *)(v6 + v7 + 8) = 0;
          ++v5;
          v6 += 10;
        }
        while ( v5 < *this );
      }
      result = *this;
      ++v3;
      v4 += 10;
    }
    while ( v3 < *this );
  }
  return result;
}

