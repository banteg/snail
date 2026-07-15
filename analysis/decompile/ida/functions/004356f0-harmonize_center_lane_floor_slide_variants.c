/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: harmonize_center_lane_floor_slide_variants @ 0x4356f0 */
/* selector: harmonize_center_lane_floor_slide_variants */

// Normalizes center-lane floor and slide seam variants after the main edge pass: a floor current cell beside a slide neighbor is promoted to the matching slide object, while a slide current cell beside a floor neighbor is restored to the floor object. Cross-port Android and iOS symbols match this pass to `cRSubGame::SlideSmoothTrack()`.
int32_t __thiscall harmonize_center_lane_floor_slide_variants(SubgameRuntime *game)
{
  SubgameRuntime *v1; // esi
  int32_t result; // eax
  int v3; // ecx
  int v4; // edx
  int v5; // ecx
  char lane_and_flags; // al
  char *v7; // esi
  GameRoot *v8; // eax
  int j; // edi
  GameRoot *v10; // eax
  int k; // edi
  char *v12; // esi
  GameRoot *v13; // eax
  int m; // edi
  GameRoot *v15; // eax
  int n; // edi
  int32_t i; // [esp+4h] [ebp-10h]
  int v18; // [esp+8h] [ebp-Ch]
  int v20; // [esp+10h] [ebp-4h]

  v1 = game;
  result = 0;
  for ( i = 0; result < game->runtime_row_count - 1; i = result )
  {
    v3 = 0;
    v4 = result & 7;
    v18 = 0;
    v20 = v4;
    while ( 1 )
    {
      if ( v4 == 3 )
      {
        v5 = v3 + 8 * result;
        lane_and_flags = v1->runtime_cells[0][v5].lane_and_flags;
        v7 = (char *)v1 + 84 * v5;
        if ( (lane_and_flags & 0x20) == 0 )
        {
          if ( (v7[3931560] & 0x20) == 0
            && (unsigned __int8)is_sub_loc_floor((TrackRowCell *)(v7 + 3930824)) == 1
            && ((unsigned __int8)is_sub_loc_slide((TrackRowCell *)(v7 + 3931496)) == 1 || v7[3931556] == 30) )
          {
            v8 = g_game_base;
            if ( *((_DWORD *)v7 + 982715) == *(_DWORD *)&g_game_base->unknown_000b48[277612] )
            {
              set_bod_object((_DWORD *)v7 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[278508]);
              *((_DWORD *)v7 + 982722) |= 0x40u;
              v8 = g_game_base;
            }
            for ( j = 0; j < 224; j += 56 )
            {
              if ( *((_DWORD *)v7 + 982715) == *(_DWORD *)&v8->unknown_000b48[j + 276212] )
              {
                set_bod_object((_DWORD *)v7 + 982706, *(_DWORD *)&v8->unknown_000b48[j + 276660]);
                *((_DWORD *)v7 + 982722) |= 0x40u;
                v8 = g_game_base;
              }
            }
          }
          if ( (v7[3930888] & 0x20) == 0
            && (v7[3931560] & 0x20) == 0
            && (unsigned __int8)is_sub_loc_slide((TrackRowCell *)(v7 + 3930824)) == 1
            && (unsigned __int8)is_sub_loc_floor((TrackRowCell *)(v7 + 3931496)) == 1 )
          {
            v10 = g_game_base;
            if ( *((_DWORD *)v7 + 982715) == *(_DWORD *)&g_game_base->unknown_000b48[278508] )
            {
              set_bod_object((_DWORD *)v7 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[277612]);
              *((_DWORD *)v7 + 982722) |= 0x40u;
              v10 = g_game_base;
            }
            for ( k = 0; k < 224; k += 56 )
            {
              if ( *((_DWORD *)v7 + 982715) == *(_DWORD *)&v10->unknown_000b48[k + 276660] )
              {
                set_bod_object((_DWORD *)v7 + 982706, *(_DWORD *)&v10->unknown_000b48[k + 276212]);
                *((_DWORD *)v7 + 982722) |= 0x40u;
                v10 = g_game_base;
              }
            }
          }
        }
      }
      else if ( v4 == 5 )
      {
        v12 = (char *)v1 + 672 * result + 84 * v3;
        if ( (v12[3930888] & 0x20) == 0 )
        {
          if ( (v12[3930216] & 0x20) == 0
            && (unsigned __int8)is_sub_loc_floor((TrackRowCell *)(v12 + 3930824)) == 1
            && ((unsigned __int8)is_sub_loc_slide((TrackRowCell *)(v12 + 3930152)) == 1 || v12[3930212] == 32) )
          {
            v13 = g_game_base;
            if ( *((_DWORD *)v12 + 982715) == *(_DWORD *)&g_game_base->unknown_000b48[277612] )
            {
              set_bod_object((_DWORD *)v12 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[278508]);
              *((_DWORD *)v12 + 982722) |= 0x40u;
              v13 = g_game_base;
            }
            for ( m = 0; m < 224; m += 56 )
            {
              if ( *((_DWORD *)v12 + 982715) == *(_DWORD *)&v13->unknown_000b48[m + 276212] )
              {
                set_bod_object((_DWORD *)v12 + 982706, *(_DWORD *)&v13->unknown_000b48[m + 276660]);
                *((_DWORD *)v12 + 982722) |= 0x40u;
                v13 = g_game_base;
              }
            }
          }
          if ( (v12[3930888] & 0x20) == 0
            && (v12[3930216] & 0x20) == 0
            && (unsigned __int8)is_sub_loc_slide((TrackRowCell *)(v12 + 3930824)) == 1
            && (unsigned __int8)is_sub_loc_floor((TrackRowCell *)(v12 + 3930152)) == 1 )
          {
            v15 = g_game_base;
            if ( *((_DWORD *)v12 + 982715) == *(_DWORD *)&g_game_base->unknown_000b48[278508] )
            {
              set_bod_object((_DWORD *)v12 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[277612]);
              *((_DWORD *)v12 + 982722) |= 0x40u;
              v15 = g_game_base;
            }
            for ( n = 0; n < 224; n += 56 )
            {
              if ( *((_DWORD *)v12 + 982715) == *(_DWORD *)&v15->unknown_000b48[n + 276660] )
              {
                set_bod_object((_DWORD *)v12 + 982706, *(_DWORD *)&v15->unknown_000b48[n + 276212]);
                *((_DWORD *)v12 + 982722) |= 0x40u;
                v15 = g_game_base;
              }
            }
          }
        }
      }
      v3 = ++v18;
      if ( v18 >= 8 )
        break;
      v4 = v20;
      v1 = game;
      result = i;
    }
    v1 = game;
    result = i + 1;
  }
  return result;
}
