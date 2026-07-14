/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: mark_track_warning_zones @ 0x4354f0 */
/* selector: mark_track_warning_zones */

// Void Windows `cRSubGame::WarnTrack()`: stamps each hazard tile's six-row by two-lane warning footprint through the owned `SubLoc` runtime grid before fringe and cache construction. The source-shaped transcription is 98.99% at 99/99 instructions.
void __thiscall mark_track_warning_zones(SubgameRuntime *game)
{
  int v1; // ebx
  uint8_t *p_tile_id; // eax
  uint8_t *v3; // edx
  int v4; // ebp
  uint8_t v5; // al
  int v6; // edi
  int v7; // esi
  int v8; // [esp+4h] [ebp-Ch]
  uint8_t *v9; // [esp+8h] [ebp-8h]
  int v10; // [esp+Ch] [ebp-4h]

  v1 = 0;
  v10 = 0;
  if ( game->runtime_row_count - 1 > 0 )
  {
    p_tile_id = &game->runtime_cells[0][0].tile_id;
    do
    {
      v3 = p_tile_id;
      v4 = 0;
      v9 = p_tile_id;
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
                game->runtime_cells[0][v6 + v7].lane_and_flags |= 0x18u;
              ++v7;
            }
            while ( v7 < 1 );
            --v1;
            v6 -= 8;
            --v8;
          }
          while ( v8 );
          v3 = v9;
          v1 = v10;
        }
        ++v4;
        v3 += 84;
        v9 = v3;
      }
      while ( v4 < 8 );
      p_tile_id = v3;
      v10 = ++v1;
    }
    while ( v1 < game->runtime_row_count - 1 );
  }
}

