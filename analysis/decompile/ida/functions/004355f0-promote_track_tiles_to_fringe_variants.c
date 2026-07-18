/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: promote_track_tiles_to_fringe_variants @ 0x4355f0 */
/* selector: promote_track_tiles_to_fringe_variants */

int32_t __thiscall promote_track_tiles_to_fringe_variants(SubgameRuntime *game)
{
  int32_t result; // eax
  void **p_object; // esi
  int v3; // ebp
  GameRoot *v4; // eax
  int i; // edi
  int j; // edi
  int32_t v7; // [esp+0h] [ebp-8h]

  result = game->runtime_row_count - 1;
  v7 = 0;
  if ( result > 0 )
  {
    p_object = &game->runtime_cells[0][0].object;
    do
    {
      v3 = 8;
      do
      {
        p_object[7] = (void *)((unsigned int)p_object[7] & 0xFFFFFFDF);
        if ( (unsigned __int8)is_sub_loc_empty((TrackRowCell *)(p_object + 159)) )
        {
          v4 = g_game_base;
          for ( i = 0; i < 8; ++i )
          {
            if ( *p_object == v4->root_bod_catalog.floor_slices.storage[i].object
              || *p_object == v4->root_bod_catalog.slide_slices.storage[i].object )
            {
              set_bod_object((BodBase *)(p_object - 9), v4->root_bod_catalog.warning_slices.storage[i].object);
              p_object[7] = (void *)((unsigned int)p_object[7] | 0x20);
              v4 = g_game_base;
            }
          }
          for ( j = 0; j < 4; ++j )
          {
            if ( *p_object == v4->root_bod_catalog.floor_corners.storage[j].object
              || *p_object == v4->root_bod_catalog.slide_corners.storage[j].object )
            {
              set_bod_object((BodBase *)(p_object - 9), v4->root_bod_catalog.warning_corners.storage[j].object);
              p_object[7] = (void *)((unsigned int)p_object[7] | 0x20);
              v4 = g_game_base;
            }
          }
        }
        p_object += 21;
        --v3;
      }
      while ( v3 );
      result = v7 + 1;
      v7 = result;
    }
    while ( result < game->runtime_row_count - 1 );
  }
  return result;
}
