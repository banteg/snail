/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: mark_track_warning_zones @ 0x4354f0 */
/* selector: mark_track_warning_zones */

// Void Windows `cRSubGame::DeSaltTrack()`: stamps the exact hazard tile set's six-row by two-lane salt-and-garbage suppression footprint through the owned `cRSubLoc` runtime grid after `CondenseTrack()` and before fringe construction. Android preserves the tile set, bounds, 0x18 flag update, and dispatcher position. The source-shaped transcription is 98.99% at 99/99 instructions.
void __thiscall mark_track_warning_zones(cRSubGame *game)
{
  int v1; // ebx
  SubLocTileId *p_tile_id; // eax
  SubLocTileId *v3; // edx
  int v4; // ebp
  SubLocTileId v5; // al
  int v6; // edi
  int v7; // esi
  int i; // [esp+4h] [ebp-Ch]
  SubLocTileId *v9; // [esp+8h] [ebp-8h]
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
        if ( *v3 == SUBLOC_TILE_RAMP_LEFT_BRACE
          || v5 == SUBLOC_TILE_RAMP_GREATER
          || v5 == SUBLOC_TILE_RAMP_RIGHT_BRACE
          || v5 == SUBLOC_TILE_RAMP_LEFT_BRACKET
          || v5 == SUBLOC_TILE_RAMP_LESS
          || v5 == SUBLOC_TILE_RAMP_RIGHT_BRACKET
          || v5 == SUBLOC_TILE_RAMP_LEFT_BRACE_RAISED
          || v5 == SUBLOC_TILE_RAMP_GREATER_RAISED
          || v5 == SUBLOC_TILE_RAMP_RIGHT_BRACE_RAISED
          || v5 == SUBLOC_TILE_RAMP_LEFT_BRACE_BACKPATCH
          || v5 == SUBLOC_TILE_RAMP_GREATER_BACKPATCH
          || v5 == SUBLOC_TILE_RAMP_RIGHT_BRACE_BACKPATCH
          || v5 == SUBLOC_TILE_WALL2
          || v5 == SUBLOC_TILE_HEALTH_PICKUP
          || v5 == SUBLOC_TILE_JETPACK_PICKUP
          || v5 == SUBLOC_TILE_GARBAGE_HAZARD )
        {
          v6 = v4 + 8 * v1;
          for ( i = 6; i != 0; --i )
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
          }
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
