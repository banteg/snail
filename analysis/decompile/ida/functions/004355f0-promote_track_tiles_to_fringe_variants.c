/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: promote_track_tiles_to_fringe_variants @ 0x4355f0 */
/* selector: promote_track_tiles_to_fringe_variants */

int __thiscall sub_4355F0(_DWORD *this)
{
  int result; // eax
  _DWORD *v2; // esi
  int v3; // ebp
  char *v4; // eax
  int i; // edi
  int j; // edi
  int v7; // [esp+0h] [ebp-8h]

  result = *(this + 21) - 1;
  v7 = 0;
  if ( result > 0 )
  {
    v2 = this + 982715;
    do
    {
      v3 = 8;
      do
      {
        v2[7] &= ~0x20u;
        if ( is_open_neighbor_tile_family((_BYTE *)v2 + 636) )
        {
          v4 = (char *)MEMORY[0x4DF904];
          for ( i = 0; i < 448; i += 56 )
          {
            if ( *v2 == *(_DWORD *)&v4[i + 280500] || *v2 == *(_DWORD *)&v4[i + 281396] )
            {
              set_bod_object(v2 - 9, *(_DWORD *)&v4[i + 280948]);
              v2[7] |= 0x20u;
              v4 = (char *)MEMORY[0x4DF904];
            }
          }
          for ( j = 0; j < 224; j += 56 )
          {
            if ( *v2 == *(_DWORD *)&v4[j + 279100] || *v2 == *(_DWORD *)&v4[j + 279548] )
            {
              set_bod_object(v2 - 9, *(_DWORD *)&v4[j + 279324]);
              v2[7] |= 0x20u;
              v4 = (char *)MEMORY[0x4DF904];
            }
          }
        }
        v2 += 21;
        --v3;
      }
      while ( v3 );
      result = v7 + 1;
      v7 = result;
    }
    while ( result < *(this + 21) - 1 );
  }
  return result;
}

