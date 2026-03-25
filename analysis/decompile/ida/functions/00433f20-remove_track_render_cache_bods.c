/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: remove_track_render_cache_bods @ 0x433f20 */
/* selector: remove_track_render_cache_bods */

// Unlinks the fixed 143x5 track-render cache bod grid from the shared active-bod list during subgame teardown.
int __thiscall sub_433F20(char *this)
{
  char *v1; // esi
  int v2; // edi
  char *v3; // ecx
  int v4; // eax
  int v5; // eax
  int result; // eax
  int v7; // [esp+10h] [ebp-4h]

  v1 = this + 100;
  v7 = 143;
  do
  {
    v2 = 5;
    do
    {
      if ( (*((_DWORD *)v1 - 2) & 0x200) != 0 )
      {
        v3 = (char *)MEMORY[0x4DF904] + 1448;
        v4 = *((_DWORD *)v1 - 2);
        if ( (v4 & 0x200) != 0 )
        {
          if ( (v4 & 0x40) != 0 )
          {
            report_errorf(aListRemoveNext);
          }
          else
          {
            if ( *(_DWORD *)v1 )
              *(_DWORD *)(*(_DWORD *)v1 + 8) = *((_DWORD *)v1 - 1);
            v5 = *((_DWORD *)v1 - 1);
            if ( v5 )
              *(_DWORD *)(v5 + 12) = *(_DWORD *)v1;
            else
              *((_DWORD *)v3 + 1) = *(_DWORD *)v1;
            *(_DWORD *)v1 = *((_DWORD *)v3 + 2);
            *((_DWORD *)v3 + 2) = v1 - 12;
            *((_DWORD *)v1 - 2) &= ~0x200u;
          }
        }
        else
        {
          report_errorf(aListRemove);
        }
      }
      v1 += 60;
      --v2;
    }
    while ( v2 );
    result = --v7;
  }
  while ( v7 );
  return result;
}

