/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_track_fringe_objects @ 0x434be0 */
/* selector: build_track_fringe_objects */

// Windows `cRSubGame::FringeEdgeTrack()`: allocates directional `Fringe` objects around runtime SubLoc cells for the post-build renderer, borrowing them from the embedded 7000-entry cRFringeManager pool at `data_4df904 + 0x3d01d4`. Android preserves the owner and method name.
int32_t __thiscall build_track_fringe_objects(SubgameRuntime *game)
{
  SubgameRuntime *v1; // ebp
  int v2; // ebx
  char *v3; // edx
  TrackRowCell *v4; // esi
  uint8_t open_edge_mask; // cl
  int v6; // edi
  uint8_t tile_id; // al
  int v8; // ebp
  FringeObject *fringe_object; // eax
  Vec3 *p_position; // eax
  int v11; // ebp
  FringeObject *v12; // eax
  Vec3 *v13; // eax
  int v14; // ebp
  FringeObject *v15; // eax
  Vec3 *v16; // eax
  int v17; // ebp
  FringeObject *v18; // eax
  Vec3 *v19; // eax
  FringeObject *fringe_front; // eax
  FringeObject *fringe_back; // eax
  FringeObject *fringe_right; // eax
  FringeObject *fringe_left; // eax
  bool v24; // cc
  int v27; // [esp+Ch] [ebp-4Ch]
  int v28; // [esp+10h] [ebp-48h]
  char *v29; // [esp+14h] [ebp-44h]
  tColour out; // [esp+18h] [ebp-40h] BYREF
  tColour v31; // [esp+28h] [ebp-30h] BYREF
  tColour v32; // [esp+38h] [ebp-20h] BYREF
  tColour v33; // [esp+48h] [ebp-10h] BYREF

  v1 = game;
  initialize_fringe_manager(&g_game_base->subgame.unknown_000044[3521400]);
  v2 = 0;
  v28 = 0;
  if ( v1->runtime_row_count > 0 )
  {
    v3 = &byte_5CCAC8[(_DWORD)v1];
    v4 = v1->runtime_cells[0];
    v29 = &byte_5CCAC8[(_DWORD)v1];
    do
    {
      v27 = 8;
      do
      {
        open_edge_mask = v4->open_edge_mask;
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
        tile_id = v4->tile_id;
        if ( tile_id == 2 || tile_id == 8 || tile_id == 5 )
          v6 = 5;
        if ( tile_id == 3 || tile_id == 9 || tile_id == 11 || tile_id == 12 || tile_id == 13 || tile_id == 6 )
          v6 = 6;
        if ( tile_id == 4 || tile_id == 10 || tile_id == 7 )
          v6 = 7;
        if ( (*v3 & 4) != 0 || !open_edge_mask || tile_id == 32 || (g_runtime_config.render_flags & 0x20) == 0 )
        {
          v4->fringe_front = nullptr;
          v4->fringe_right = nullptr;
          v4->fringe_left = nullptr;
LABEL_64:
          v4->fringe_back = nullptr;
          goto LABEL_65;
        }
        if ( !is_neighbor_cell_solid(v1, v4, 0, 0) )
          goto LABEL_65;
        if ( is_neighbor_cell_solid(v1, v4, 0, 1) )
        {
          v4->fringe_front = nullptr;
        }
        else
        {
          if ( !is_neighbor_cell_solid(v1, v4, 1, 1) )
            v2 = !is_neighbor_cell_solid(v1, v4, 1, 0) + 1;
          if ( is_neighbor_cell_solid(v1, v4, -1, 1) )
            v8 = 0;
          else
            v8 = !is_neighbor_cell_solid(v1, v4, -1, 0) + 1;
          fringe_object = (FringeObject *)allocate_fringe_object(&g_game_base->subgame.unknown_000044[3521400]);
          v4->fringe_front = fringe_object;
          set_bod_object(
            fringe_object,
            *(_DWORD *)&g_game_base->unknown_000b48[1344 * v6 + 279180 + 672 * v6 + 112 * v2 + 56 * v8 + 56 * v2]);
          v4->fringe_front->bod.list_flags |= 0x20u;
          p_position = &v4->fringe_front->position;
          p_position->x = v4->anchor_position.x;
          p_position->y = v4->anchor_position.y;
          p_position->z = v4->anchor_position.z;
          v1 = game;
          v2 = 0;
          v4->fringe_front->color = *get_track_skirt_color((SubgameRuntime *)&g_game_base->subgame, &out);
        }
        if ( is_neighbor_cell_solid(v1, v4, 1, 0) )
        {
          v4->fringe_right = nullptr;
        }
        else
        {
          if ( !is_neighbor_cell_solid(v1, v4, 1, -1) )
            v2 = !is_neighbor_cell_solid(v1, v4, 0, -1) + 1;
          if ( is_neighbor_cell_solid(v1, v4, 1, 1) )
            v11 = 0;
          else
            v11 = !is_neighbor_cell_solid(v1, v4, 0, 1) + 1;
          v12 = (FringeObject *)allocate_fringe_object(&g_game_base->subgame.unknown_000044[3521400]);
          v4->fringe_right = v12;
          set_bod_object(
            v12,
            *(_DWORD *)&g_game_base->unknown_000b48[1344 * v6 + 279684 + 672 * v6 + 112 * v2 + 56 * v11 + 56 * v2]);
          v4->fringe_right->bod.list_flags |= 0x20u;
          v13 = &v4->fringe_right->position;
          v13->x = v4->anchor_position.x;
          v13->y = v4->anchor_position.y;
          v13->z = v4->anchor_position.z;
          v1 = game;
          v2 = 0;
          v4->fringe_right->color = *get_track_skirt_color((SubgameRuntime *)&g_game_base->subgame, &v31);
        }
        if ( is_neighbor_cell_solid(v1, v4, -1, 0) )
        {
          v4->fringe_left = nullptr;
        }
        else
        {
          if ( !is_neighbor_cell_solid(v1, v4, -1, 1) )
            v2 = !is_neighbor_cell_solid(v1, v4, 0, 1) + 1;
          if ( is_neighbor_cell_solid(v1, v4, -1, -1) )
            v14 = 0;
          else
            v14 = !is_neighbor_cell_solid(v1, v4, 0, -1) + 1;
          v15 = (FringeObject *)allocate_fringe_object(&g_game_base->subgame.unknown_000044[3521400]);
          v4->fringe_left = v15;
          set_bod_object(
            v15,
            *(_DWORD *)&g_game_base->unknown_000b48[1344 * v6 + 280188 + 672 * v6 + 112 * v2 + 56 * v14 + 56 * v2]);
          v4->fringe_left->bod.list_flags |= 0x20u;
          v16 = &v4->fringe_left->position;
          v16->x = v4->anchor_position.x;
          v16->y = v4->anchor_position.y;
          v16->z = v4->anchor_position.z;
          v1 = game;
          v2 = 0;
          v4->fringe_left->color = *get_track_skirt_color((SubgameRuntime *)&g_game_base->subgame, &v32);
        }
        if ( is_neighbor_cell_solid(v1, v4, 0, -1) )
          goto LABEL_64;
        if ( !is_neighbor_cell_solid(v1, v4, -1, -1) )
          v2 = !is_neighbor_cell_solid(v1, v4, -1, 0) + 1;
        if ( is_neighbor_cell_solid(v1, v4, 1, -1) )
          v17 = 0;
        else
          v17 = !is_neighbor_cell_solid(v1, v4, 1, 0) + 1;
        v18 = (FringeObject *)allocate_fringe_object(&g_game_base->subgame.unknown_000044[3521400]);
        v4->fringe_back = v18;
        set_bod_object(
          v18,
          *(_DWORD *)&g_game_base->unknown_000b48[1344 * v6 + 280692 + 672 * v6 + 112 * v2 + 56 * v17 + 56 * v2]);
        v4->fringe_back->bod.list_flags |= 0x20u;
        v19 = &v4->fringe_back->position;
        v19->x = v4->anchor_position.x;
        v19->y = v4->anchor_position.y;
        v19->z = v4->anchor_position.z;
        v1 = game;
        v2 = 0;
        v4->fringe_back->color = *get_track_skirt_color((SubgameRuntime *)&g_game_base->subgame, &v33);
LABEL_65:
        v3 = v29;
        if ( (*v29 & 4) != 0 )
        {
          fringe_front = v4->fringe_front;
          if ( fringe_front )
            fringe_front->bod.list_flags &= ~0x20u;
          fringe_back = v4->fringe_back;
          if ( fringe_back )
            fringe_back->bod.list_flags &= ~0x20u;
          fringe_right = v4->fringe_right;
          if ( fringe_right )
            fringe_right->bod.list_flags &= ~0x20u;
          fringe_left = v4->fringe_left;
          if ( fringe_left )
            fringe_left->bod.list_flags &= ~0x20u;
        }
        ++v4;
        --v27;
      }
      while ( v27 );
      v3 = v29 + 244;
      v24 = ++v28 < v1->runtime_row_count;
      v29 += 244;
    }
    while ( v24 );
  }
  return debug_report_stub();
}
