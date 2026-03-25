/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: clear_active_landscape_entries @ 0x418a30 */
/* selector: clear_active_landscape_entries */

// Clears the active 10-slot landscape-entry runtime pool by unlinking every live entry from the shared body list and zeroing its startup-delay lane. `destroy_subgame` uses it when the current landscape set is torn down.
__int16 __thiscall sub_418A30(_DWORD *this)
{
  _DWORD *v1; // esi
  int v2; // ebp
  int v3; // eax
  char *v4; // ecx
  int v5; // eax
  int v6; // eax

  v1 = this + 3;
  v2 = 10;
  do
  {
    v3 = *(v1 - 2);
    if ( (v3 & 0x200) != 0 )
    {
      v1[29] = 0;
      v4 = (char *)MEMORY[0x4DF904] + 1448;
      v5 = *(v1 - 2);
      if ( (v5 & 0x200) != 0 )
      {
        if ( (v5 & 0x40) != 0 )
        {
          LOWORD(v3) = report_errorf(aListRemoveNext);
        }
        else
        {
          if ( *v1 )
            *(_DWORD *)(*v1 + 8) = *(v1 - 1);
          v6 = *(v1 - 1);
          if ( v6 )
            *(_DWORD *)(v6 + 12) = *v1;
          else
            *((_DWORD *)v4 + 1) = *v1;
          *v1 = *((_DWORD *)v4 + 2);
          *((_DWORD *)v4 + 2) = v1 - 3;
          v3 = *(v1 - 2);
          BYTE1(v3) &= ~2u;
          *(v1 - 2) = v3;
        }
      }
      else
      {
        LOWORD(v3) = report_errorf(aListRemove);
      }
    }
    v1 += 36;
    --v2;
  }
  while ( v2 );
  return v3;
}

