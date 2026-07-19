/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: select_track_tile_edge_variants @ 0x435a80 */
/* selector: select_track_tile_edge_variants */

// Void cRSubGame normalization pass that computes neighbor masks and chooses edge or corner variants for special runtime tile classes. Cross-port Android and iOS symbols match this pass to `cRSubGame::SmoothTrack()`.
void __thiscall select_track_tile_edge_variants(SubgameRuntime *game)
{
  int32_t v1; // edi
  SubLocTileId *p_tile_id; // esi
  int i; // ebp
  int v4; // edx
  SubLocTileId v5; // al
  SubLocTileId v6; // al
  Object *object; // edx
  SubLocTileId v8; // al
  SubLocTileId v9; // al
  SubLocTileId v10; // al
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
        *((_BYTE *)p_tile_id + 1) = 0;
        v4 = *((_DWORD *)p_tile_id + 1);
        BYTE1(v4) &= ~0x80u;
        *((_DWORD *)p_tile_id + 1) = v4;
        v5 = *p_tile_id;
        if ( *p_tile_id
          && v5 != SUBLOC_TILE_RING_MARKER
          && v5 != SUBLOC_TILE_UNIVERSE_HOLE
          && v5 != SUBLOC_TILE_PATH_ENTRY_LOWERCASE
          && v5 != SUBLOC_TILE_PATH_ENTRY_UPPERCASE
          && v5 != SUBLOC_TILE_WALL2 )
        {
          if ( !i || (unsigned __int8)is_sub_loc_empty((TrackRowCell *)(p_tile_id - 144)) )
            *((_BYTE *)p_tile_id + 1) |= 8u;
          if ( i == 7 || (unsigned __int8)is_sub_loc_empty((TrackRowCell *)(p_tile_id + 24)) )
            *((_BYTE *)p_tile_id + 1) |= 4u;
          if ( !v1 || (unsigned __int8)is_sub_loc_empty((TrackRowCell *)(p_tile_id - 732)) )
            *((_BYTE *)p_tile_id + 1) |= 1u;
          if ( v1 >= game->runtime_row_count - 1 || (unsigned __int8)is_sub_loc_empty((TrackRowCell *)(p_tile_id + 612)) )
            *((_BYTE *)p_tile_id + 1) |= 2u;
          switch ( *((_BYTE *)p_tile_id + 1) )
          {
            case 5:
              *((_DWORD *)p_tile_id + 1) |= 0x8000u;
              v8 = *p_tile_id;
              if ( *p_tile_id == SUBLOC_TILE_FLOOR_DOT
                || v8 == SUBLOC_TILE_FLOOR_VARIANT_14
                || v8 == SUBLOC_TILE_FLOOR_DASH
                || v8 == SUBLOC_TILE_FLOOR_VARIANT_1B
                || v8 == SUBLOC_TILE_GARBAGE_HAZARD
                || v8 == SUBLOC_TILE_SALT_HAZARD )
              {
                set_bod_object(
                  (BodBase *)(p_tile_id - 60),
                  g_game_base->root_bod_catalog.floor_corners.storage[1].object);
              }
              else if ( v8 != SUBLOC_TILE_TRAMPOLINE
                     && v8 != SUBLOC_TILE_WALL2
                     && !(unsigned __int8)is_sub_loc_ramp((TrackRowCell *)(p_tile_id - 60)) )
              {
                set_bod_object(
                  (BodBase *)(p_tile_id - 60),
                  g_game_base->root_bod_catalog.slide_corners.storage[1].object);
              }
              break;
            case 6:
              *((_DWORD *)p_tile_id + 1) |= 0x8000u;
              v10 = *p_tile_id;
              if ( *p_tile_id == SUBLOC_TILE_FLOOR_DOT
                || v10 == SUBLOC_TILE_FLOOR_VARIANT_14
                || v10 == SUBLOC_TILE_FLOOR_DASH
                || v10 == SUBLOC_TILE_FLOOR_VARIANT_1B
                || v10 == SUBLOC_TILE_GARBAGE_HAZARD
                || v10 == SUBLOC_TILE_SALT_HAZARD )
              {
                object = g_game_base->root_bod_catalog.floor_corners.storage[3].object;
                goto LABEL_67;
              }
              if ( v10 != SUBLOC_TILE_TRAMPOLINE
                && v10 != SUBLOC_TILE_WALL2
                && !(unsigned __int8)is_sub_loc_ramp((TrackRowCell *)(p_tile_id - 60)) )
              {
                set_bod_object(
                  (BodBase *)(p_tile_id - 60),
                  g_game_base->root_bod_catalog.slide_corners.storage[3].object);
              }
              break;
            case 9:
              *((_DWORD *)p_tile_id + 1) |= 0x8000u;
              v6 = *p_tile_id;
              if ( *p_tile_id == SUBLOC_TILE_FLOOR_DOT
                || v6 == SUBLOC_TILE_FLOOR_VARIANT_14
                || v6 == SUBLOC_TILE_FLOOR_DASH
                || v6 == SUBLOC_TILE_FLOOR_VARIANT_1B
                || v6 == SUBLOC_TILE_GARBAGE_HAZARD
                || v6 == SUBLOC_TILE_SALT_HAZARD )
              {
                object = g_game_base->root_bod_catalog.floor_corners.storage[0].object;
LABEL_67:
                set_bod_object((BodBase *)(p_tile_id - 60), object);
              }
              else if ( v6 != SUBLOC_TILE_TRAMPOLINE
                     && v6 != SUBLOC_TILE_WALL2
                     && !(unsigned __int8)is_sub_loc_ramp((TrackRowCell *)(p_tile_id - 60)) )
              {
                set_bod_object(
                  (BodBase *)(p_tile_id - 60),
                  g_game_base->root_bod_catalog.slide_corners.storage[0].object);
              }
              break;
            case 0xA:
              *((_DWORD *)p_tile_id + 1) |= 0x8000u;
              v9 = *p_tile_id;
              if ( *p_tile_id == SUBLOC_TILE_FLOOR_DOT
                || v9 == SUBLOC_TILE_FLOOR_VARIANT_14
                || v9 == SUBLOC_TILE_FLOOR_DASH
                || v9 == SUBLOC_TILE_FLOOR_VARIANT_1B
                || v9 == SUBLOC_TILE_GARBAGE_HAZARD
                || v9 == SUBLOC_TILE_SALT_HAZARD )
              {
                set_bod_object(
                  (BodBase *)(p_tile_id - 60),
                  g_game_base->root_bod_catalog.floor_corners.storage[2].object);
              }
              else if ( v9 != SUBLOC_TILE_TRAMPOLINE
                     && v9 != SUBLOC_TILE_WALL2
                     && !(unsigned __int8)is_sub_loc_ramp((TrackRowCell *)(p_tile_id - 60)) )
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
