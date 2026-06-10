/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: mark_track_warning_zones @ 0x4354f0 */
/* selector: mark_track_warning_zones */

// Marks warning-zone footprints around hazard-bearing runtime tiles before the fringe-object and cache builders run. Cross-port Android symbols match this pass to `cRSubGame::WarnTrack()`.
int32_t __thiscall mark_track_warning_zones(Game *game)
{
  int v1; // ebx
  int32_t result; // eax
  char *v3; // edx
  int v4; // ebp
  char v5; // al
  int v6; // edi
  int v7; // esi
  int v8; // [esp+4h] [ebp-Ch]
  int32_t v9; // [esp+8h] [ebp-8h]
  int v10; // [esp+Ch] [ebp-4h]

  v1 = 0;
  result = game->runtime_row_count - 1;
  v10 = 0;
  if ( result > 0 )
  {
    result = (int32_t)&game->_pad_74622[3454178];
    do
    {
      v3 = (char *)result;
      v4 = 0;
      v9 = result;
      do
      {
        v5 = *v3;
        if ( *v3 == 2
          || v5 == 3
          || v5 == 4
          || v5 == 5
          || v5 == 6
          || v5 == 7
          || v5 == 8
          || v5 == 9
          || v5 == 10
          || v5 == 11
          || v5 == 12
          || v5 == 13
          || v5 == 14
          || v5 == 23
          || v5 == 25
          || v5 == 33 )
        {
          v6 = v4 + 8 * v1;
          v8 = 6;
          do
          {
            v7 = -1;
            do
            {
              if ( v1 >= 0 && v1 < game->runtime_row_count - 1 && (unsigned int)(v7 + v4) < 8 )
                *(_DWORD *)&game->_pad_74622[84 * v6 + 3454182 + 84 * v7] |= 0x18u;
              ++v7;
            }
            while ( v7 < 1 );
            --v1;
            v6 -= 8;
            --v8;
          }
          while ( v8 );
          v3 = (char *)v9;
          v1 = v10;
        }
        ++v4;
        v3 += 84;
        v9 = (int32_t)v3;
      }
      while ( v4 < 8 );
      result = (int32_t)v3;
      v10 = ++v1;
    }
    while ( v1 < game->runtime_row_count - 1 );
  }
  return result;
}

