/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: promote_track_tiles_to_fringe_variants @ 0x4355f0 */
/* selector: promote_track_tiles_to_fringe_variants */

// Void cRSubGame normalization pass that promotes floor/slide runtime cells to their warning-fringe object variants when the same lane in the next row is open. Its sole caller consumes only the grid mutation; the count-derived EAX residue is incidental.
void __thiscall promote_track_tiles_to_fringe_variants(SubgameRuntime *game)
{
  void **p_object; // esi
  int v2; // ebp
  GameRoot *v3; // eax
  int i; // edi
  int j; // edi
  int v6; // [esp+0h] [ebp-8h]

  v6 = 0;
  if ( game->runtime_row_count - 1 > 0 )
  {
    p_object = &game->runtime_cells[0][0].object;
    do
    {
      v2 = 8;
      do
      {
        p_object[7] = (void *)((unsigned int)p_object[7] & 0xFFFFFFDF);
        if ( (unsigned __int8)is_sub_loc_empty((TrackRowCell *)(p_object + 159)) )
        {
          v3 = g_game_base;
          for ( i = 0; i < 8; ++i )
          {
            if ( *p_object == v3->root_bod_catalog.floor_slices.storage[i].object
              || *p_object == v3->root_bod_catalog.slide_slices.storage[i].object )
            {
              set_bod_object((BodBase *)(p_object - 9), v3->root_bod_catalog.warning_slices.storage[i].object);
              p_object[7] = (void *)((unsigned int)p_object[7] | 0x20);
              v3 = g_game_base;
            }
          }
          for ( j = 0; j < 4; ++j )
          {
            if ( *p_object == v3->root_bod_catalog.floor_corners.storage[j].object
              || *p_object == v3->root_bod_catalog.slide_corners.storage[j].object )
            {
              set_bod_object((BodBase *)(p_object - 9), v3->root_bod_catalog.warning_corners.storage[j].object);
              p_object[7] = (void *)((unsigned int)p_object[7] | 0x20);
              v3 = g_game_base;
            }
          }
        }
        p_object += 21;
        --v2;
      }
      while ( v2 );
      ++v6;
    }
    while ( v6 < game->runtime_row_count - 1 );
  }
}
