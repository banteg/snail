/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_track_fringe_objects @ 0x434be0 */
/* selector: build_track_fringe_objects */

// Windows `cRSubGame::FringeEdgeTrack()`: allocates directional `Fringe` objects around runtime SubLoc cells for the post-build renderer, borrowing them from the embedded 7000-entry cRFringeManager pool at `data_4df904 + 0x3d01d4`. Android preserves the owner and method name.
int32_t __thiscall build_track_fringe_objects(SubgameRuntime *game)
{
  SubgameRuntime *v1; // ebp
  int v2; // ebx
  SubRow *row; // edx
  TrackRowCell *cell; // esi
  uint8_t open_edge_mask; // cl
  int v6; // edi
  uint8_t tile_id; // al
  int v8; // ebp
  FringeObject *fringe_front_new; // eax
  int v10; // ebp
  FringeObject *fringe_right_new; // eax
  int v12; // ebp
  FringeObject *fringe_left_new; // eax
  int v14; // ebp
  FringeObject *fringe_back_new; // eax
  FringeObject *fringe_front; // eax
  FringeObject *fringe_back; // eax
  FringeObject *fringe_right; // eax
  FringeObject *fringe_left; // eax
  bool v20; // cc
  int v23; // [esp+Ch] [ebp-4Ch]
  int v24; // [esp+10h] [ebp-48h]
  SubRow *row_cursor; // [esp+14h] [ebp-44h]
  tColour out; // [esp+18h] [ebp-40h] BYREF
  tColour v27; // [esp+28h] [ebp-30h] BYREF
  tColour v28; // [esp+38h] [ebp-20h] BYREF
  tColour v29; // [esp+48h] [ebp-10h] BYREF

  v1 = game;
  initialize_fringe_manager(&g_game_base->subgame.fringe_manager);
  v2 = 0;
  v24 = 0;
  if ( v1->runtime_row_count > 0 )
  {
    row = v1->runtime_rows;
    cell = v1->runtime_cells[0];
    row_cursor = v1->runtime_rows;
    do
    {
      v23 = 8;
      do
      {
        open_edge_mask = cell->open_edge_mask;
        v6 = 0;
        switch ( open_edge_mask )
        {
          case 9u:
            v6 = 1;
            break;
          case 5u:
            v6 = 3;
            break;
          case 0xAu:
            v6 = 2;
            break;
          case 6u:
            v6 = 4;
            break;
        }
        tile_id = cell->tile_id;
        if ( tile_id == 2 || tile_id == 8 || tile_id == 5 )
          v6 = 5;
        if ( tile_id == 3 || tile_id == 9 || tile_id == 11 || tile_id == 12 || tile_id == 13 || tile_id == 6 )
          v6 = 6;
        if ( tile_id == 4 || tile_id == 10 || tile_id == 7 )
          v6 = 7;
        if ( (row->flags & 4) != 0 || !open_edge_mask || tile_id == 32 || (g_runtime_config.render_flags & 0x20) == 0 )
        {
          cell->fringe_front = nullptr;
          cell->fringe_right = nullptr;
          cell->fringe_left = nullptr;
LABEL_64:
          cell->fringe_back = nullptr;
          goto LABEL_65;
        }
        if ( !is_neighbor_cell_solid(v1, cell, 0, 0) )
          goto LABEL_65;
        if ( is_neighbor_cell_solid(v1, cell, 0, 1) )
        {
          cell->fringe_front = nullptr;
        }
        else
        {
          if ( !is_neighbor_cell_solid(v1, cell, 1, 1) )
            v2 = !is_neighbor_cell_solid(v1, cell, 1, 0) + 1;
          if ( is_neighbor_cell_solid(v1, cell, -1, 1) )
            v8 = 0;
          else
            v8 = !is_neighbor_cell_solid(v1, cell, -1, 0) + 1;
          fringe_front_new = allocate_fringe_object(&g_game_base->subgame.fringe_manager);
          cell->fringe_front = fringe_front_new;
          set_bod_object(
            &fringe_front_new->bod,
            g_game_base->root_bod_catalog.fringe_catalog.entries[0][0][8 * v6][12 * v6 + 2 * v2 + v8 + v2].object);
          cell->fringe_front->bod.bod.list_flags |= 0x20u;
          cell->fringe_front->bod.position = cell->anchor_position;
          v1 = game;
          v2 = 0;
          cell->fringe_front->bod.color = *get_track_skirt_color(&g_game_base->subgame, &out);
        }
        if ( is_neighbor_cell_solid(v1, cell, 1, 0) )
        {
          cell->fringe_right = nullptr;
        }
        else
        {
          if ( !is_neighbor_cell_solid(v1, cell, 1, -1) )
            v2 = !is_neighbor_cell_solid(v1, cell, 0, -1) + 1;
          if ( is_neighbor_cell_solid(v1, cell, 1, 1) )
            v10 = 0;
          else
            v10 = !is_neighbor_cell_solid(v1, cell, 0, 1) + 1;
          fringe_right_new = allocate_fringe_object(&g_game_base->subgame.fringe_manager);
          cell->fringe_right = fringe_right_new;
          set_bod_object(
            &fringe_right_new->bod,
            g_game_base->root_bod_catalog.fringe_catalog.entries[0][1][8 * v6][12 * v6 + 2 * v2 + v10 + v2].object);
          cell->fringe_right->bod.bod.list_flags |= 0x20u;
          cell->fringe_right->bod.position = cell->anchor_position;
          v1 = game;
          v2 = 0;
          cell->fringe_right->bod.color = *get_track_skirt_color(&g_game_base->subgame, &v27);
        }
        if ( is_neighbor_cell_solid(v1, cell, -1, 0) )
        {
          cell->fringe_left = nullptr;
        }
        else
        {
          if ( !is_neighbor_cell_solid(v1, cell, -1, 1) )
            v2 = !is_neighbor_cell_solid(v1, cell, 0, 1) + 1;
          if ( is_neighbor_cell_solid(v1, cell, -1, -1) )
            v12 = 0;
          else
            v12 = !is_neighbor_cell_solid(v1, cell, 0, -1) + 1;
          fringe_left_new = allocate_fringe_object(&g_game_base->subgame.fringe_manager);
          cell->fringe_left = fringe_left_new;
          set_bod_object(
            &fringe_left_new->bod,
            g_game_base->root_bod_catalog.fringe_catalog.entries[0][2][8 * v6][12 * v6 + 2 * v2 + v12 + v2].object);
          cell->fringe_left->bod.bod.list_flags |= 0x20u;
          cell->fringe_left->bod.position = cell->anchor_position;
          v1 = game;
          v2 = 0;
          cell->fringe_left->bod.color = *get_track_skirt_color(&g_game_base->subgame, &v28);
        }
        if ( is_neighbor_cell_solid(v1, cell, 0, -1) )
          goto LABEL_64;
        if ( !is_neighbor_cell_solid(v1, cell, -1, -1) )
          v2 = !is_neighbor_cell_solid(v1, cell, -1, 0) + 1;
        if ( is_neighbor_cell_solid(v1, cell, 1, -1) )
          v14 = 0;
        else
          v14 = !is_neighbor_cell_solid(v1, cell, 1, 0) + 1;
        fringe_back_new = allocate_fringe_object(&g_game_base->subgame.fringe_manager);
        cell->fringe_back = fringe_back_new;
        set_bod_object(
          &fringe_back_new->bod,
          g_game_base->root_bod_catalog.fringe_catalog.entries[0][3][8 * v6][12 * v6 + 2 * v2 + v14 + v2].object);
        cell->fringe_back->bod.bod.list_flags |= 0x20u;
        cell->fringe_back->bod.position = cell->anchor_position;
        v1 = game;
        v2 = 0;
        cell->fringe_back->bod.color = *get_track_skirt_color(&g_game_base->subgame, &v29);
LABEL_65:
        row = row_cursor;
        if ( (row_cursor->flags & 4) != 0 )
        {
          fringe_front = cell->fringe_front;
          if ( fringe_front )
            fringe_front->bod.bod.list_flags &= ~0x20u;
          fringe_back = cell->fringe_back;
          if ( fringe_back )
            fringe_back->bod.bod.list_flags &= ~0x20u;
          fringe_right = cell->fringe_right;
          if ( fringe_right )
            fringe_right->bod.bod.list_flags &= ~0x20u;
          fringe_left = cell->fringe_left;
          if ( fringe_left )
            fringe_left->bod.bod.list_flags &= ~0x20u;
        }
        ++cell;
        --v23;
      }
      while ( v23 );
      row = row_cursor + 1;
      v20 = ++v24 < v1->runtime_row_count;
      ++row_cursor;
    }
    while ( v20 );
  }
  return debug_report_stub();
}
