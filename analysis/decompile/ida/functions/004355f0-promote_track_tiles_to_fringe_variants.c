/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: promote_track_tiles_to_fringe_variants @ 0x4355f0 */
/* selector: promote_track_tiles_to_fringe_variants */

// Void Windows `cRSubGame::WarnTrack()`: promotes floor and slide runtime cells to their warning object variants when the same lane in the next row is empty. Android preserves the two object-family scans, replacement banks, 0x20 marker, and dispatcher position between `SmoothTrack()` and `SlideSmoothTrack()`. Its sole Windows caller consumes only the grid mutation; the count-derived EAX residue is incidental.
void __thiscall promote_track_tiles_to_fringe_variants(SubgameRuntime *game)
{
  Object **p_object; // esi
  int i; // ebp
  GameRoot *v3; // eax
  int j; // edi
  int k; // edi
  int v6; // [esp+0h] [ebp-8h]

  v6 = 0;
  if ( game->runtime_row_count - 1 > 0 )
  {
    p_object = &game->runtime_cells[0][0].object;
    do
    {
      for ( i = 8; i != 0; --i )
      {
        p_object[7] = (Object *)((unsigned int)p_object[7] & 0xFFFFFFDF);
        if ( (unsigned __int8)is_sub_loc_empty((cRSubLoc *)(p_object + 159)) != 0 )
        {
          v3 = g_game_base;
          for ( j = 0; j < 8; ++j )
          {
            if ( *p_object == v3->root_bod_catalog.floor_slices.storage[j].object
              || *p_object == v3->root_bod_catalog.slide_slices.storage[j].object )
            {
              set_bod_object((BodBase *)(p_object - 9), v3->root_bod_catalog.warning_slices.storage[j].object);
              p_object[7] = (Object *)((unsigned int)p_object[7] | 0x20);
              v3 = g_game_base;
            }
          }
          for ( k = 0; k < 4; ++k )
          {
            if ( *p_object == v3->root_bod_catalog.floor_corners.storage[k].object
              || *p_object == v3->root_bod_catalog.slide_corners.storage[k].object )
            {
              set_bod_object((BodBase *)(p_object - 9), v3->root_bod_catalog.warning_corners.storage[k].object);
              p_object[7] = (Object *)((unsigned int)p_object[7] | 0x20);
              v3 = g_game_base;
            }
          }
        }
        p_object += 21;
      }
      ++v6;
    }
    while ( v6 < game->runtime_row_count - 1 );
  }
}
