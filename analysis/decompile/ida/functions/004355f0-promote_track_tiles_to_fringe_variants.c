/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: promote_track_tiles_to_fringe_variants @ 0x4355f0 */
/* selector: promote_track_tiles_to_fringe_variants */

int32_t __thiscall promote_track_tiles_to_fringe_variants(Game *game)
{
  int32_t result; // eax
  uint8_t *v2; // esi
  int v3; // ebp
  char *v4; // eax
  int i; // edi
  int j; // edi
  int32_t v7; // [esp+0h] [ebp-8h]

  result = game->runtime_row_count - 1;
  v7 = 0;
  if ( result > 0 )
  {
    v2 = &game->_pad_74622[3454154];
    do
    {
      v3 = 8;
      do
      {
        *((_DWORD *)v2 + 7) &= ~0x20u;
        if ( is_sub_loc_empty(v2 + 636) )
        {
          v4 = (char *)MEMORY[0x4DF904];
          for ( i = 0; i < 448; i += 56 )
          {
            if ( *(_DWORD *)v2 == *(_DWORD *)&v4[i + 280500] || *(_DWORD *)v2 == *(_DWORD *)&v4[i + 281396] )
            {
              set_bod_object((_DWORD *)v2 - 9, *(_DWORD *)&v4[i + 280948]);
              *((_DWORD *)v2 + 7) |= 0x20u;
              v4 = (char *)MEMORY[0x4DF904];
            }
          }
          for ( j = 0; j < 224; j += 56 )
          {
            if ( *(_DWORD *)v2 == *(_DWORD *)&v4[j + 279100] || *(_DWORD *)v2 == *(_DWORD *)&v4[j + 279548] )
            {
              set_bod_object((_DWORD *)v2 - 9, *(_DWORD *)&v4[j + 279324]);
              *((_DWORD *)v2 + 7) |= 0x20u;
              v4 = (char *)MEMORY[0x4DF904];
            }
          }
        }
        v2 += 84;
        --v3;
      }
      while ( v3 );
      result = v7 + 1;
      v7 = result;
    }
    while ( result < game->runtime_row_count - 1 );
  }
  return result;
}

