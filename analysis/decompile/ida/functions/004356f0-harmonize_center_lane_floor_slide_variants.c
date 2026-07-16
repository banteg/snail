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
  RuntimeCellStrideAnchor *forward_cell_anchor; // esi
  GameRoot *v8; // eax
  int j; // edi
  GameRoot *v10; // eax
  int k; // edi
  RuntimeCellStrideAnchor *backward_cell_anchor; // esi
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
        forward_cell_anchor = (RuntimeCellStrideAnchor *)((char *)v1 + 84 * v5);
        if ( (lane_and_flags & 0x20) == 0 )
        {
          if ( (forward_cell_anchor->next_row_same_lane.lane_and_flags & 0x20) == 0
            && (unsigned __int8)is_sub_loc_floor(&forward_cell_anchor->cell) == 1
            && ((unsigned __int8)is_sub_loc_slide(&forward_cell_anchor->next_row_same_lane) == 1
             || forward_cell_anchor->next_row_same_lane.tile_id == 30) )
          {
            v8 = g_game_base;
            if ( forward_cell_anchor->cell.object == g_game_base->root_bod_catalog.floor_slices.storage[0].object )
            {
              set_bod_object(
                (BodBase *)&forward_cell_anchor->cell,
                (Object *)g_game_base->root_bod_catalog.slide_slices.storage[0].object);
              forward_cell_anchor->cell.lane_and_flags |= 0x40u;
              v8 = g_game_base;
            }
            for ( j = 0; j < 4; ++j )
            {
              if ( forward_cell_anchor->cell.object == v8->root_bod_catalog.floor_corners.storage[j].object )
              {
                set_bod_object(
                  (BodBase *)&forward_cell_anchor->cell,
                  (Object *)v8->root_bod_catalog.slide_corners.storage[j].object);
                forward_cell_anchor->cell.lane_and_flags |= 0x40u;
                v8 = g_game_base;
              }
            }
          }
          if ( (forward_cell_anchor->cell.lane_and_flags & 0x20) == 0
            && (forward_cell_anchor->next_row_same_lane.lane_and_flags & 0x20) == 0
            && (unsigned __int8)is_sub_loc_slide(&forward_cell_anchor->cell) == 1
            && (unsigned __int8)is_sub_loc_floor(&forward_cell_anchor->next_row_same_lane) == 1 )
          {
            v10 = g_game_base;
            if ( forward_cell_anchor->cell.object == g_game_base->root_bod_catalog.slide_slices.storage[0].object )
            {
              set_bod_object(
                (BodBase *)&forward_cell_anchor->cell,
                (Object *)g_game_base->root_bod_catalog.floor_slices.storage[0].object);
              forward_cell_anchor->cell.lane_and_flags |= 0x40u;
              v10 = g_game_base;
            }
            for ( k = 0; k < 4; ++k )
            {
              if ( forward_cell_anchor->cell.object == v10->root_bod_catalog.slide_corners.storage[k].object )
              {
                set_bod_object(
                  (BodBase *)&forward_cell_anchor->cell,
                  (Object *)v10->root_bod_catalog.floor_corners.storage[k].object);
                forward_cell_anchor->cell.lane_and_flags |= 0x40u;
                v10 = g_game_base;
              }
            }
          }
        }
      }
      else if ( v4 == 5 )
      {
        backward_cell_anchor = (RuntimeCellStrideAnchor *)((char *)v1 + 672 * result + 84 * v3);
        if ( (backward_cell_anchor->cell.lane_and_flags & 0x20) == 0 )
        {
          if ( (backward_cell_anchor->previous_row_same_lane.lane_and_flags & 0x20) == 0
            && (unsigned __int8)is_sub_loc_floor(&backward_cell_anchor->cell) == 1
            && ((unsigned __int8)is_sub_loc_slide(&backward_cell_anchor->previous_row_same_lane) == 1
             || backward_cell_anchor->previous_row_same_lane.tile_id == 32) )
          {
            v13 = g_game_base;
            if ( backward_cell_anchor->cell.object == g_game_base->root_bod_catalog.floor_slices.storage[0].object )
            {
              set_bod_object(
                (BodBase *)&backward_cell_anchor->cell,
                (Object *)g_game_base->root_bod_catalog.slide_slices.storage[0].object);
              backward_cell_anchor->cell.lane_and_flags |= 0x40u;
              v13 = g_game_base;
            }
            for ( m = 0; m < 4; ++m )
            {
              if ( backward_cell_anchor->cell.object == v13->root_bod_catalog.floor_corners.storage[m].object )
              {
                set_bod_object(
                  (BodBase *)&backward_cell_anchor->cell,
                  (Object *)v13->root_bod_catalog.slide_corners.storage[m].object);
                backward_cell_anchor->cell.lane_and_flags |= 0x40u;
                v13 = g_game_base;
              }
            }
          }
          if ( (backward_cell_anchor->cell.lane_and_flags & 0x20) == 0
            && (backward_cell_anchor->previous_row_same_lane.lane_and_flags & 0x20) == 0
            && (unsigned __int8)is_sub_loc_slide(&backward_cell_anchor->cell) == 1
            && (unsigned __int8)is_sub_loc_floor(&backward_cell_anchor->previous_row_same_lane) == 1 )
          {
            v15 = g_game_base;
            if ( backward_cell_anchor->cell.object == g_game_base->root_bod_catalog.slide_slices.storage[0].object )
            {
              set_bod_object(
                (BodBase *)&backward_cell_anchor->cell,
                (Object *)g_game_base->root_bod_catalog.floor_slices.storage[0].object);
              backward_cell_anchor->cell.lane_and_flags |= 0x40u;
              v15 = g_game_base;
            }
            for ( n = 0; n < 4; ++n )
            {
              if ( backward_cell_anchor->cell.object == v15->root_bod_catalog.slide_corners.storage[n].object )
              {
                set_bod_object(
                  (BodBase *)&backward_cell_anchor->cell,
                  (Object *)v15->root_bod_catalog.floor_corners.storage[n].object);
                backward_cell_anchor->cell.lane_and_flags |= 0x40u;
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
