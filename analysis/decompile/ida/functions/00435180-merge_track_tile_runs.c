/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: merge_track_tile_runs @ 0x435180 */
/* selector: merge_track_tile_runs */

// Authored `cRSubGame::CondenseTrack()`: collapses horizontal floor and slide runs into the matching `RootBodCatalog` slice length, maps tile-0x0e runs onto the pillar mesh bank, and clears render/contact flags on continuation `SubLoc` cells. Reusing each consumed run length for cleanup raises the source-shaped transcription to 67.50% at 284/276 instructions without synthetic dependencies.
int32_t __thiscall merge_track_tile_runs(SubgameRuntime *game)
{
  SubgameRuntime *v1; // esi
  int32_t v2; // edx
  uint32_t *p_lane_and_flags; // eax
  int v4; // ecx
  uint32_t v5; // ebp
  int32_t result; // eax
  int *v7; // ebx
  int v8; // ebp
  int *v9; // edi
  int v10; // esi
  int v11; // edx
  _DWORD *v12; // ecx
  char v13; // al
  int v14; // eax
  int v15; // esi
  uint32_t *v16; // eax
  int v17; // ecx
  int v18; // esi
  int *v19; // edi
  int v20; // eax
  int v21; // esi
  uint32_t *v22; // eax
  int v23; // ebp
  int v24; // edx
  char v25; // al
  _BYTE *v26; // edx
  int v27; // esi
  int v28; // eax
  int v29; // ecx
  int v30; // edx
  int v31; // ecx
  int v32; // esi
  uint32_t *v33; // eax
  int v34; // ecx
  int v35; // eax
  int32_t v36; // [esp+8h] [ebp-10h]
  int v38; // [esp+10h] [ebp-8h]
  _DWORD *v39; // [esp+14h] [ebp-4h]

  v1 = game;
  v2 = 0;
  if ( game->runtime_row_count > 0 )
  {
    p_lane_and_flags = &game->runtime_cells[0][0].lane_and_flags;
    do
    {
      v4 = 8;
      do
      {
        v5 = *p_lane_and_flags;
        p_lane_and_flags += 21;
        --v4;
        *(p_lane_and_flags - 21) = v5 | 0x6000;
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
    v39 = (_DWORD *)((char *)&unk_5CCB7C + (_DWORD)v1);
    v7 = (int *)&v1->runtime_cells[0][0].lane_and_flags;
    do
    {
      v8 = 0;
      v38 = 0;
      while ( 1 )
      {
        v9 = v7 - 16;
        if ( !(unsigned __int8)is_sub_loc_floor((TrackRowCell *)(v7 - 16))
          || (BYTE1(*v7) & 0x80u) != 0
          || (*v7 & 0x40) != 0 )
        {
          if ( !(unsigned __int8)is_sub_loc_slide((TrackRowCell *)(v7 - 16))
            || (BYTE1(*v7) & 0x80u) != 0
            || (*v7 & 0x40) != 0 )
          {
            v25 = *((_BYTE *)v9 + 60);
            v26 = v9 + 15;
            if ( v25 == 14 )
            {
              v28 = *v7;
              v27 = 0;
              BYTE1(v28) = BYTE1(*v7) & 0xF0 | 1;
              *v7 = v28;
              v29 = v8;
              do
              {
                if ( *v26 != 14 )
                  break;
                if ( (v28 & 0x4000) != 0x4000 )
                  break;
                v26 += 84;
                BYTE1(v28) = BYTE1(v28) & 0xF0 | 1;
                ++v27;
                ++v29;
                *v7 = v28;
              }
              while ( v29 < 8 );
              if ( v27 > 1 )
              {
                set_bod_object(v7 - 16, *(_DWORD *)&g_game_base->unknown_00067c[56 * v27 + 278336]);
                v30 = *v7;
                BYTE1(v30) = BYTE1(*v7) & 0xF0;
                v31 = v30 | ((v27 & 0xF) << 8);
                v32 = v27 - 1;
                *v7 = v31;
                if ( v32 > 0 )
                {
                  v33 = &game->runtime_cells[v36][v8 + v32].lane_and_flags;
                  do
                  {
                    v34 = *(v33 - 15);
                    v33 -= 21;
                    v33[6] = v34 & 0xFFFFFFDF;
                    --v32;
                    v33[21] &= 0xFFFF9FFF;
                  }
                  while ( v32 );
                }
              }
            }
            else if ( !v25 || v25 == 35 )
            {
              v35 = *v7;
              BYTE1(v35) = BYTE1(*v7) & 0xDF;
              *v7 = v35;
              if ( v1->level_mode == 2 )
              {
                set_bod_object(v7 - 16, *(_DWORD *)&g_game_base->unknown_00067c[277160]);
              }
              else
              {
                BYTE1(v35) &= ~0x40u;
                *v7 = v35;
              }
            }
          }
          else
          {
            v18 = 0;
            v19 = v7;
            do
            {
              if ( !(unsigned __int8)is_sub_loc_slide((TrackRowCell *)(v19 - 16)) )
                break;
              v20 = *v19;
              if ( (BYTE1(*v19) & 0x80u) != 0 )
                break;
              if ( (v20 & 0x4000) == 0 )
                break;
              if ( (v20 & 0x60) != 0 )
                break;
              ++v18;
              v19 += 21;
              ++v8;
            }
            while ( v8 < 8 );
            if ( v18 > 1 )
            {
              set_bod_object(v7 - 16, *(_DWORD *)&g_game_base->unknown_00067c[56 * v18 + 279680]);
              v21 = v18 - 1;
              if ( v21 > 0 )
              {
                v22 = &game->runtime_cells[v36][v38 + v21].lane_and_flags;
                do
                {
                  v23 = *(v22 - 15);
                  v22 -= 21;
                  v22[6] = v23 & 0xFFFFFFDF;
                  --v21;
                  v22[21] &= 0xFFFF9FFF;
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
          v12 = v9 + 15;
          do
          {
            v13 = *(_BYTE *)v12;
            if ( *(_BYTE *)v12 != 1 && v13 != 21 && v13 != 27 && v13 != 33 && v13 != 34 )
              break;
            v14 = v12[1];
            if ( (v14 & 0x8000) != 0 )
              break;
            if ( (v14 & 0x4000) == 0 )
              break;
            if ( (v14 & 0x60) != 0 )
              break;
            ++v10;
            v12 += 21;
            ++v11;
          }
          while ( v11 < 8 );
          if ( v10 > 1 )
          {
            set_bod_object(v7 - 16, *(_DWORD *)&g_game_base->unknown_00067c[56 * v10 + 278784]);
            v15 = v10 - 1;
            if ( v15 > 0 )
            {
              v16 = &game->runtime_cells[v36][v8 + v15].lane_and_flags;
              do
              {
                v17 = *(v16 - 15);
                v16 -= 21;
                v16[6] = v17 & 0xFFFFFFDF;
                --v15;
                v16[21] &= 0xFFFF9FFF;
              }
              while ( v15 );
            }
          }
        }
        if ( (*(_BYTE *)(v39 - 45) & 4) != 0 )
        {
          *(v7 - 15) &= 0xFFFFFDDD;
          v24 = *v7;
          BYTE1(v24) = BYTE1(*v7) & 0xBF;
          *v7 = v24;
          *v39 &= ~0x20u;
        }
        ++v8;
        v7 += 21;
        v38 = v8;
        if ( v8 >= 8 )
          break;
        v1 = game;
      }
      v1 = game;
      v39 += 61;
      result = game->runtime_row_count;
      ++v36;
    }
    while ( v36 < result );
  }
  return result;
}
