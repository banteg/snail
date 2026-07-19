/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: select_track_tile_edge_variants @ 0x435a80 */
/* selector: select_track_tile_edge_variants */

// Void cRSubGame normalization pass that computes neighbor masks and chooses edge or corner variants for special runtime tile classes. Cross-port Android and iOS symbols match this pass to `cRSubGame::SmoothTrack()`.
void __thiscall select_track_tile_edge_variants(SubgameRuntime *game)
{
  int32_t v1; // edi
  uint8_t *p_tile_id; // esi
  int i; // ebp
  int v4; // edx
  uint8_t v5; // al
  uint8_t v6; // al
  Object *object; // edx
  uint8_t v8; // al
  uint8_t v9; // al
  uint8_t v10; // al
  int32_t v11; // [esp+4h] [ebp-8h]

  v1 = 0;
  v11 = 0;
  if ( game->runtime_row_count > 0 )
  {
    p_tile_id = &game->runtime_cells[0][0].tile_id;
    do
    {
      for ( i = 0; i < 8; ++i )
      {
        p_tile_id[1] = 0;
        v4 = *((_DWORD *)p_tile_id + 1);
        BYTE1(v4) &= ~0x80u;
        *((_DWORD *)p_tile_id + 1) = v4;
        v5 = *p_tile_id;
        if ( *p_tile_id && v5 != 35 && v5 != 28 && v5 != 29 && v5 != 30 && v5 != 14 )
        {
          if ( !i || (unsigned __int8)is_sub_loc_empty((TrackRowCell *)(p_tile_id - 144)) )
            p_tile_id[1] |= 8u;
          if ( i == 7 || (unsigned __int8)is_sub_loc_empty((TrackRowCell *)(p_tile_id + 24)) )
            p_tile_id[1] |= 4u;
          if ( !v1 || (unsigned __int8)is_sub_loc_empty((TrackRowCell *)(p_tile_id - 732)) )
            p_tile_id[1] |= 1u;
          if ( v1 >= game->runtime_row_count - 1 || (unsigned __int8)is_sub_loc_empty((TrackRowCell *)(p_tile_id + 612)) )
            p_tile_id[1] |= 2u;
          switch ( p_tile_id[1] )
          {
            case 5u:
              *((_DWORD *)p_tile_id + 1) |= 0x8000u;
              v8 = *p_tile_id;
              if ( *p_tile_id == 1 || v8 == 20 || v8 == 21 || v8 == 27 || v8 == 33 || v8 == 34 )
              {
                set_bod_object(
                  (BodBase *)(p_tile_id - 60),
                  g_game_base->root_bod_catalog.floor_corners.storage[1].object);
              }
              else if ( v8 != 22 && v8 != 14 && !(unsigned __int8)is_sub_loc_ramp((TrackRowCell *)(p_tile_id - 60)) )
              {
                set_bod_object(
                  (BodBase *)(p_tile_id - 60),
                  g_game_base->root_bod_catalog.slide_corners.storage[1].object);
              }
              break;
            case 6u:
              *((_DWORD *)p_tile_id + 1) |= 0x8000u;
              v10 = *p_tile_id;
              if ( *p_tile_id == 1 || v10 == 20 || v10 == 21 || v10 == 27 || v10 == 33 || v10 == 34 )
              {
                object = g_game_base->root_bod_catalog.floor_corners.storage[3].object;
                goto LABEL_67;
              }
              if ( v10 != 22 && v10 != 14 && !(unsigned __int8)is_sub_loc_ramp((TrackRowCell *)(p_tile_id - 60)) )
                set_bod_object(
                  (BodBase *)(p_tile_id - 60),
                  g_game_base->root_bod_catalog.slide_corners.storage[3].object);
              break;
            case 9u:
              *((_DWORD *)p_tile_id + 1) |= 0x8000u;
              v6 = *p_tile_id;
              if ( *p_tile_id == 1 || v6 == 20 || v6 == 21 || v6 == 27 || v6 == 33 || v6 == 34 )
              {
                object = g_game_base->root_bod_catalog.floor_corners.storage[0].object;
LABEL_67:
                set_bod_object((BodBase *)(p_tile_id - 60), object);
              }
              else if ( v6 != 22 && v6 != 14 && !(unsigned __int8)is_sub_loc_ramp((TrackRowCell *)(p_tile_id - 60)) )
              {
                set_bod_object(
                  (BodBase *)(p_tile_id - 60),
                  g_game_base->root_bod_catalog.slide_corners.storage[0].object);
              }
              break;
            case 0xAu:
              *((_DWORD *)p_tile_id + 1) |= 0x8000u;
              v9 = *p_tile_id;
              if ( *p_tile_id == 1 || v9 == 20 || v9 == 21 || v9 == 27 || v9 == 33 || v9 == 34 )
              {
                set_bod_object(
                  (BodBase *)(p_tile_id - 60),
                  g_game_base->root_bod_catalog.floor_corners.storage[2].object);
              }
              else if ( v9 != 22 && v9 != 14 && !(unsigned __int8)is_sub_loc_ramp((TrackRowCell *)(p_tile_id - 60)) )
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
        v1 = v11;
        p_tile_id += 84;
      }
      v1 = v11 + 1;
      v11 = v1;
    }
    while ( v1 < game->runtime_row_count );
  }
}
