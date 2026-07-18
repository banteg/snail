/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: select_track_tile_edge_variants @ 0x435a80 */
/* selector: select_track_tile_edge_variants */

// Computes neighbor masks and chooses edge or corner variants for special runtime tile classes. Cross-port Android and iOS symbols match this pass to `cRSubGame::SmoothTrack()`.
int32_t __thiscall select_track_tile_edge_variants(SubgameRuntime *game)
{
  int32_t result; // eax
  int32_t v2; // edi
  uint8_t *p_tile_id; // esi
  int i; // ebp
  int v5; // edx
  uint8_t v6; // al
  uint8_t v7; // al
  Object *object; // edx
  uint8_t v9; // al
  uint8_t v10; // al
  uint8_t v11; // al
  int32_t v12; // [esp+4h] [ebp-8h]

  result = game->runtime_row_count;
  v2 = 0;
  v12 = 0;
  if ( result > 0 )
  {
    p_tile_id = &game->runtime_cells[0][0].tile_id;
    do
    {
      for ( i = 0; i < 8; ++i )
      {
        p_tile_id[1] = 0;
        v5 = *((_DWORD *)p_tile_id + 1);
        BYTE1(v5) &= ~0x80u;
        *((_DWORD *)p_tile_id + 1) = v5;
        v6 = *p_tile_id;
        if ( *p_tile_id && v6 != 35 && v6 != 28 && v6 != 29 && v6 != 30 && v6 != 14 )
        {
          if ( !i || (unsigned __int8)is_sub_loc_empty((TrackRowCell *)(p_tile_id - 144)) )
            p_tile_id[1] |= 8u;
          if ( i == 7 || (unsigned __int8)is_sub_loc_empty((TrackRowCell *)(p_tile_id + 24)) )
            p_tile_id[1] |= 4u;
          if ( !v2 || (unsigned __int8)is_sub_loc_empty((TrackRowCell *)(p_tile_id - 732)) )
            p_tile_id[1] |= 1u;
          if ( v2 >= game->runtime_row_count - 1 || (unsigned __int8)is_sub_loc_empty((TrackRowCell *)(p_tile_id + 612)) )
            p_tile_id[1] |= 2u;
          switch ( p_tile_id[1] )
          {
            case 5u:
              *((_DWORD *)p_tile_id + 1) |= 0x8000u;
              v9 = *p_tile_id;
              if ( *p_tile_id == 1 || v9 == 20 || v9 == 21 || v9 == 27 || v9 == 33 || v9 == 34 )
              {
                set_bod_object(
                  (BodBase *)(p_tile_id - 60),
                  g_game_base->root_bod_catalog.floor_corners.storage[1].object);
              }
              else if ( v9 != 22 && v9 != 14 && !(unsigned __int8)is_sub_loc_ramp((TrackRowCell *)(p_tile_id - 60)) )
              {
                set_bod_object(
                  (BodBase *)(p_tile_id - 60),
                  g_game_base->root_bod_catalog.slide_corners.storage[1].object);
              }
              break;
            case 6u:
              *((_DWORD *)p_tile_id + 1) |= 0x8000u;
              v11 = *p_tile_id;
              if ( *p_tile_id == 1 || v11 == 20 || v11 == 21 || v11 == 27 || v11 == 33 || v11 == 34 )
              {
                object = g_game_base->root_bod_catalog.floor_corners.storage[3].object;
                goto LABEL_67;
              }
              if ( v11 != 22 && v11 != 14 && !(unsigned __int8)is_sub_loc_ramp((TrackRowCell *)(p_tile_id - 60)) )
                set_bod_object(
                  (BodBase *)(p_tile_id - 60),
                  g_game_base->root_bod_catalog.slide_corners.storage[3].object);
              break;
            case 9u:
              *((_DWORD *)p_tile_id + 1) |= 0x8000u;
              v7 = *p_tile_id;
              if ( *p_tile_id == 1 || v7 == 20 || v7 == 21 || v7 == 27 || v7 == 33 || v7 == 34 )
              {
                object = g_game_base->root_bod_catalog.floor_corners.storage[0].object;
LABEL_67:
                set_bod_object((BodBase *)(p_tile_id - 60), object);
              }
              else if ( v7 != 22 && v7 != 14 && !(unsigned __int8)is_sub_loc_ramp((TrackRowCell *)(p_tile_id - 60)) )
              {
                set_bod_object(
                  (BodBase *)(p_tile_id - 60),
                  g_game_base->root_bod_catalog.slide_corners.storage[0].object);
              }
              break;
            case 0xAu:
              *((_DWORD *)p_tile_id + 1) |= 0x8000u;
              v10 = *p_tile_id;
              if ( *p_tile_id == 1 || v10 == 20 || v10 == 21 || v10 == 27 || v10 == 33 || v10 == 34 )
              {
                set_bod_object(
                  (BodBase *)(p_tile_id - 60),
                  g_game_base->root_bod_catalog.floor_corners.storage[2].object);
              }
              else if ( v10 != 22 && v10 != 14 && !(unsigned __int8)is_sub_loc_ramp((TrackRowCell *)(p_tile_id - 60)) )
              {
                set_bod_object(
                  (BodBase *)(p_tile_id - 60),
                  g_game_base->root_bod_catalog.slide_corners.storage[2].object);
              }
              break;
            default:
              break;
          }
        }
        v2 = v12;
        p_tile_id += 84;
      }
      result = (int32_t)game;
      v2 = v12 + 1;
      v12 = v2;
    }
    while ( v2 < game->runtime_row_count );
  }
  return result;
}
