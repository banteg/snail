/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: merge_track_tile_runs @ 0x435180 */
/* selector: merge_track_tile_runs */

// Authored `cRSubGame::CondenseTrack()`: collapses horizontal floor and slide runs into the matching `RootBodCatalog` slice length, maps tile-0x0e runs onto the pillar mesh bank, and clears render/contact flags on continuation `SubLoc` cells. Reusing each consumed run length for cleanup raises the source-shaped transcription to 67.50% at 284/276 instructions without synthetic dependencies.
int32_t __thiscall merge_track_tile_runs(SubgameRuntime *game)
{
  SubgameRuntime *v1; // esi
  int32_t v2; // edx
  uint32_t *seed_lane_flags; // eax
  int v4; // ecx
  uint32_t v5; // ebp
  int32_t result; // eax
  uint32_t *cell_lane_flags; // ebx
  int v8; // ebp
  TrackRowCell *cell; // edi
  int v10; // esi
  int v11; // edx
  uint8_t *floor_tile_cursor; // ecx
  uint8_t v13; // al
  int v14; // eax
  int v15; // esi
  uint32_t *floor_cleanup_lane_flags; // eax
  int v17; // ecx
  int v18; // esi
  uint32_t *slide_lane_flags_cursor; // edi
  uint32_t v20; // eax
  int v21; // esi
  uint32_t *slide_cleanup_lane_flags; // eax
  int v23; // ebp
  uint32_t v24; // edx
  uint8_t tile_id; // al
  uint8_t *wall_tile_cursor; // edx
  int v27; // esi
  uint32_t v28; // eax
  int v29; // ecx
  uint32_t v30; // edx
  uint32_t v31; // ecx
  int v32; // esi
  uint32_t *wall_cleanup_lane_flags; // eax
  int v34; // ecx
  uint32_t v35; // eax
  int32_t v36; // [esp+8h] [ebp-10h]
  int v38; // [esp+10h] [ebp-8h]
  uint32_t *row_attachment_flags; // [esp+14h] [ebp-4h]

  v1 = game;
  v2 = 0;
  if ( game->runtime_row_count > 0 )
  {
    seed_lane_flags = &game->runtime_cells[0][0].lane_and_flags;
    do
    {
      v4 = 8;
      do
      {
        v5 = *seed_lane_flags;
        seed_lane_flags += 21;
        --v4;
        *(seed_lane_flags - 21) = v5 | 0x6000;
      }
      while ( v4 );
      ++v2;
    }
    while ( v2 < v1->runtime_row_count );
  }
  result = v1->runtime_row_count;
  v36 = 0;
  if ( result > 0 )
  {
    row_attachment_flags = (uint32_t *)((char *)&unk_5CCB7C + (_DWORD)v1);
    cell_lane_flags = &v1->runtime_cells[0][0].lane_and_flags;
    do
    {
      v8 = 0;
      v38 = 0;
      while ( 1 )
      {
        cell = CONTAINING_RECORD(cell_lane_flags, TrackRowCell, lane_and_flags);
        if ( !(unsigned __int8)is_sub_loc_floor((TrackRowCell *)(cell_lane_flags - 16))
          || (BYTE1(*cell_lane_flags) & 0x80u) != 0
          || (*cell_lane_flags & 0x40) != 0 )
        {
          if ( !(unsigned __int8)is_sub_loc_slide((TrackRowCell *)(cell_lane_flags - 16))
            || (BYTE1(*cell_lane_flags) & 0x80u) != 0
            || (*cell_lane_flags & 0x40) != 0 )
          {
            tile_id = cell->tile_id;
            wall_tile_cursor = &cell->tile_id;
            if ( tile_id == 14 )
            {
              v28 = *cell_lane_flags;
              v27 = 0;
              BYTE1(v28) = BYTE1(*cell_lane_flags) & 0xF0 | 1;
              *cell_lane_flags = v28;
              v29 = v8;
              do
              {
                if ( *wall_tile_cursor != 14 )
                  break;
                if ( (v28 & 0x4000) != 0x4000 )
                  break;
                wall_tile_cursor += 84;
                BYTE1(v28) = BYTE1(v28) & 0xF0 | 1;
                ++v27;
                ++v29;
                *cell_lane_flags = v28;
              }
              while ( v29 < 8 );
              if ( v27 > 1 )
              {
                set_bod_object(
                  (BodBase *)(cell_lane_flags - 16),
                  g_game_base->root_bod_catalog.unknown_18_21[v27 + 3].object);
                v30 = *cell_lane_flags;
                BYTE1(v30) = BYTE1(*cell_lane_flags) & 0xF0;
                v31 = v30 | ((v27 & 0xF) << 8);
                v32 = v27 - 1;
                *cell_lane_flags = v31;
                if ( v32 > 0 )
                {
                  wall_cleanup_lane_flags = &game->runtime_cells[v36][v8 + v32].lane_and_flags;
                  do
                  {
                    v34 = *(wall_cleanup_lane_flags - 15);
                    wall_cleanup_lane_flags -= 21;
                    wall_cleanup_lane_flags[6] = v34 & 0xFFFFFFDF;
                    --v32;
                    wall_cleanup_lane_flags[21] &= 0xFFFF9FFF;
                  }
                  while ( v32 );
                }
              }
            }
            else if ( !tile_id || tile_id == 35 )
            {
              v35 = *cell_lane_flags;
              BYTE1(v35) = BYTE1(*cell_lane_flags) & 0xDF;
              *cell_lane_flags = v35;
              if ( v1->level_mode == 2 )
              {
                set_bod_object((BodBase *)(cell_lane_flags - 16), g_game_base->root_bod_catalog.universe_hole.object);
              }
              else
              {
                BYTE1(v35) &= ~0x40u;
                *cell_lane_flags = v35;
              }
            }
          }
          else
          {
            v18 = 0;
            slide_lane_flags_cursor = cell_lane_flags;
            do
            {
              if ( !(unsigned __int8)is_sub_loc_slide((TrackRowCell *)(slide_lane_flags_cursor - 16)) )
                break;
              v20 = *slide_lane_flags_cursor;
              if ( (BYTE1(*slide_lane_flags_cursor) & 0x80u) != 0 )
                break;
              if ( (v20 & 0x4000) == 0 )
                break;
              if ( (v20 & 0x60) != 0 )
                break;
              ++v18;
              slide_lane_flags_cursor += 21;
              ++v8;
            }
            while ( v8 < 8 );
            if ( v18 > 1 )
            {
              set_bod_object(
                (BodBase *)(cell_lane_flags - 16),
                g_game_base->root_bod_catalog.warning_slices.storage[v18 + 7].object);
              v21 = v18 - 1;
              if ( v21 > 0 )
              {
                slide_cleanup_lane_flags = &game->runtime_cells[v36][v38 + v21].lane_and_flags;
                do
                {
                  v23 = *(slide_cleanup_lane_flags - 15);
                  slide_cleanup_lane_flags -= 21;
                  slide_cleanup_lane_flags[6] = v23 & 0xFFFFFFDF;
                  --v21;
                  slide_cleanup_lane_flags[21] &= 0xFFFF9FFF;
                }
                while ( v21 );
              }
            }
            v8 = v38;
          }
        }
        else
        {
          v10 = 0;
          v11 = v8;
          floor_tile_cursor = &cell->tile_id;
          do
          {
            v13 = *floor_tile_cursor;
            if ( *floor_tile_cursor != 1 && v13 != 21 && v13 != 27 && v13 != 33 && v13 != 34 )
              break;
            v14 = *((_DWORD *)floor_tile_cursor + 1);
            if ( (v14 & 0x8000) != 0 )
              break;
            if ( (v14 & 0x4000) == 0 )
              break;
            if ( (v14 & 0x60) != 0 )
              break;
            ++v10;
            floor_tile_cursor += 84;
            ++v11;
          }
          while ( v11 < 8 );
          if ( v10 > 1 )
          {
            set_bod_object((BodBase *)(cell_lane_flags - 16), g_game_base->root_bod_catalog.pillars[v10 + 7].object);
            v15 = v10 - 1;
            if ( v15 > 0 )
            {
              floor_cleanup_lane_flags = &game->runtime_cells[v36][v8 + v15].lane_and_flags;
              do
              {
                v17 = *(floor_cleanup_lane_flags - 15);
                floor_cleanup_lane_flags -= 21;
                floor_cleanup_lane_flags[6] = v17 & 0xFFFFFFDF;
                --v15;
                floor_cleanup_lane_flags[21] &= 0xFFFF9FFF;
              }
              while ( v15 );
            }
          }
        }
        if ( (*(_BYTE *)(row_attachment_flags - 45) & 4) != 0 )
        {
          *(cell_lane_flags - 15) &= 0xFFFFFDDD;
          v24 = *cell_lane_flags;
          BYTE1(v24) = BYTE1(*cell_lane_flags) & 0xBF;
          *cell_lane_flags = v24;
          *row_attachment_flags &= ~0x20u;
        }
        ++v8;
        cell_lane_flags += 21;
        v38 = v8;
        if ( v8 >= 8 )
          break;
        v1 = game;
      }
      v1 = game;
      row_attachment_flags += 61;
      result = game->runtime_row_count;
      ++v36;
    }
    while ( v36 < result );
  }
  return result;
}
