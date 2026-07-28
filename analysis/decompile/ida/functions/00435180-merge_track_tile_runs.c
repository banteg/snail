/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: merge_track_tile_runs @ 0x435180 */
/* selector: merge_track_tile_runs */

// Authored void `cRSubGame::CondenseTrack()`: collapses horizontal floor and slide runs into the matching `RootBodCatalog` slice length, maps tile-0x0e runs onto the pillar mesh bank, and clears render/contact flags on continuation `cRSubLoc` cells. The iOS and Android epilogues establish no result and their zero-row paths leave incompatible incidental values in the return register, independently resolving the Windows ABI. Reusing each consumed run length for cleanup raises the source-shaped transcription to 67.50% at 284/276 instructions without synthetic dependencies.
void __thiscall merge_track_tile_runs(cRSubGame *game)
{
  cRSubGame *v1; // esi
  int32_t v2; // edx
  uint32_t *seed_lane_flags; // eax
  int i; // ecx
  uint32_t v5; // ebp
  uint32_t *cell_lane_flags; // ebx
  int v7; // ebp
  cRSubLoc *cell; // edi
  int v9; // esi
  int v10; // edx
  uint8_t *floor_tile_cursor; // ecx
  uint8_t v12; // al
  int v13; // eax
  int v14; // esi
  uint32_t *floor_cleanup_lane_flags; // eax
  int v16; // ecx
  int v17; // esi
  uint32_t *slide_lane_flags_cursor; // edi
  uint32_t v19; // eax
  int v20; // esi
  uint32_t *slide_cleanup_lane_flags; // eax
  int v22; // ebp
  uint32_t v23; // edx
  SubLocTileId tile_id; // al
  uint8_t *wall_tile_cursor; // edx
  int v26; // esi
  uint32_t v27; // eax
  int v28; // ecx
  uint32_t v29; // edx
  uint32_t v30; // ecx
  int v31; // esi
  uint32_t *wall_cleanup_lane_flags; // eax
  int v33; // ecx
  uint32_t v34; // eax
  int32_t v35; // [esp+8h] [ebp-10h]
  int v37; // [esp+10h] [ebp-8h]
  uint32_t *row_attachment_flags; // [esp+14h] [ebp-4h]

  v1 = game;
  v2 = 0;
  if ( game->runtime_row_count > 0 )
  {
    seed_lane_flags = &game->runtime_cells[0][0].lane_and_flags;
    do
    {
      for ( i = 8; i != 0; --i )
      {
        v5 = *seed_lane_flags;
        seed_lane_flags += 21;
        *(seed_lane_flags - 21) = v5 | 0x6000;
      }
      ++v2;
    }
    while ( v2 < v1->runtime_row_count );
  }
  v35 = 0;
  if ( v1->runtime_row_count > 0 )
  {
    row_attachment_flags = &v1->runtime_rows[0].attachment_body.bod.list_flags;
    cell_lane_flags = &v1->runtime_cells[0][0].lane_and_flags;
    do
    {
      v7 = 0;
      v37 = 0;
      while ( 1 )
      {
        cell = CONTAINING_RECORD(cell_lane_flags, cRSubLoc, lane_and_flags);
        if ( (unsigned __int8)is_sub_loc_floor((cRSubLoc *)(cell_lane_flags - 16)) == 0
          || (BYTE1(*cell_lane_flags) & 0x80u) != 0
          || (*cell_lane_flags & 0x40) != 0 )
        {
          if ( (unsigned __int8)is_sub_loc_slide((cRSubLoc *)(cell_lane_flags - 16)) == 0
            || (BYTE1(*cell_lane_flags) & 0x80u) != 0
            || (*cell_lane_flags & 0x40) != 0 )
          {
            tile_id = cell->tile_id;
            wall_tile_cursor = (uint8_t *)&cell->tile_id;
            if ( tile_id == SUBLOC_TILE_WALL2 )
            {
              v27 = *cell_lane_flags;
              v26 = 0;
              BYTE1(v27) = BYTE1(*cell_lane_flags) & 0xF0 | 1;
              *cell_lane_flags = v27;
              v28 = v7;
              do
              {
                if ( *wall_tile_cursor != 14 )
                  break;
                if ( (v27 & 0x4000) != 0x4000 )
                  break;
                wall_tile_cursor += 84;
                BYTE1(v27) = BYTE1(v27) & 0xF0 | 1;
                ++v26;
                ++v28;
                *cell_lane_flags = v27;
              }
              while ( v28 < 8 );
              if ( v26 > 1 )
              {
                set_bod_object(
                  (BodBase *)(cell_lane_flags - 16),
                  g_game_base->root_bod_catalog.unknown_18_21[v26 + 3].object);
                v29 = *cell_lane_flags;
                BYTE1(v29) = BYTE1(*cell_lane_flags) & 0xF0;
                v30 = v29 | ((v26 & 0xF) << 8);
                v31 = v26 - 1;
                *cell_lane_flags = v30;
                if ( v31 > 0 )
                {
                  wall_cleanup_lane_flags = &game->runtime_cells[v35][v7 + v31].lane_and_flags;
                  do
                  {
                    v33 = *(wall_cleanup_lane_flags - 15);
                    wall_cleanup_lane_flags -= 21;
                    wall_cleanup_lane_flags[6] = v33 & 0xFFFFFFDF;
                    --v31;
                    wall_cleanup_lane_flags[21] &= 0xFFFF9FFF;
                  }
                  while ( v31 != 0 );
                }
              }
            }
            else if ( tile_id == SUBLOC_TILE_EMPTY || tile_id == SUBLOC_TILE_RING_MARKER )
            {
              v34 = *cell_lane_flags;
              BYTE1(v34) = BYTE1(*cell_lane_flags) & 0xDF;
              *cell_lane_flags = v34;
              if ( v1->level_mode == 2 )
              {
                set_bod_object((BodBase *)(cell_lane_flags - 16), g_game_base->root_bod_catalog.universe_hole.object);
              }
              else
              {
                BYTE1(v34) &= ~0x40u;
                *cell_lane_flags = v34;
              }
            }
          }
          else
          {
            v17 = 0;
            slide_lane_flags_cursor = cell_lane_flags;
            do
            {
              if ( (unsigned __int8)is_sub_loc_slide((cRSubLoc *)(slide_lane_flags_cursor - 16)) == 0 )
                break;
              v19 = *slide_lane_flags_cursor;
              if ( (BYTE1(*slide_lane_flags_cursor) & 0x80u) != 0 )
                break;
              if ( (v19 & 0x4000) == 0 )
                break;
              if ( (v19 & 0x60) != 0 )
                break;
              ++v17;
              slide_lane_flags_cursor += 21;
              ++v7;
            }
            while ( v7 < 8 );
            if ( v17 > 1 )
            {
              set_bod_object(
                (BodBase *)(cell_lane_flags - 16),
                g_game_base->root_bod_catalog.warning_slices.storage[v17 + 7].object);
              v20 = v17 - 1;
              if ( v20 > 0 )
              {
                slide_cleanup_lane_flags = &game->runtime_cells[v35][v37 + v20].lane_and_flags;
                do
                {
                  v22 = *(slide_cleanup_lane_flags - 15);
                  slide_cleanup_lane_flags -= 21;
                  slide_cleanup_lane_flags[6] = v22 & 0xFFFFFFDF;
                  --v20;
                  slide_cleanup_lane_flags[21] &= 0xFFFF9FFF;
                }
                while ( v20 != 0 );
              }
            }
            v7 = v37;
          }
        }
        else
        {
          v9 = 0;
          v10 = v7;
          floor_tile_cursor = (uint8_t *)&cell->tile_id;
          do
          {
            v12 = *floor_tile_cursor;
            if ( *floor_tile_cursor != 1 && v12 != 21 && v12 != 27 && v12 != 33 && v12 != 34 )
              break;
            v13 = *((_DWORD *)floor_tile_cursor + 1);
            if ( (v13 & 0x8000) != 0 )
              break;
            if ( (v13 & 0x4000) == 0 )
              break;
            if ( (v13 & 0x60) != 0 )
              break;
            ++v9;
            floor_tile_cursor += 84;
            ++v10;
          }
          while ( v10 < 8 );
          if ( v9 > 1 )
          {
            set_bod_object((BodBase *)(cell_lane_flags - 16), g_game_base->root_bod_catalog.pillars[v9 + 7].object);
            v14 = v9 - 1;
            if ( v14 > 0 )
            {
              floor_cleanup_lane_flags = &game->runtime_cells[v35][v7 + v14].lane_and_flags;
              do
              {
                v16 = *(floor_cleanup_lane_flags - 15);
                floor_cleanup_lane_flags -= 21;
                floor_cleanup_lane_flags[6] = v16 & 0xFFFFFFDF;
                --v14;
                floor_cleanup_lane_flags[21] &= 0xFFFF9FFF;
              }
              while ( v14 != 0 );
            }
          }
        }
        if ( (*(_BYTE *)(row_attachment_flags - 45) & 4) != 0 )
        {
          *(cell_lane_flags - 15) &= 0xFFFFFDDD;
          v23 = *cell_lane_flags;
          BYTE1(v23) = BYTE1(*cell_lane_flags) & 0xBF;
          *cell_lane_flags = v23;
          *row_attachment_flags &= ~0x20u;
        }
        ++v7;
        cell_lane_flags += 21;
        v37 = v7;
        if ( v7 >= 8 )
          break;
        v1 = game;
      }
      v1 = game;
      row_attachment_flags += 61;
      ++v35;
    }
    while ( v35 < game->runtime_row_count );
  }
}
