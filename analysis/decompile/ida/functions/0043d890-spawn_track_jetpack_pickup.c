/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_track_jetpack_pickup @ 0x43d890 */
/* selector: spawn_track_jetpack_pickup */

// Seeds the owned `JetPack` singleton from the active runtime cell. Android and iOS retain `cRSubGame::AddJetPack(cRSubLoc*, cRSubGoldy*)`; Android establishes no result, so the Windows reconstruction keeps the honest void contract rather than exporting incompatible incidental register values.
void __thiscall spawn_track_jetpack_pickup(SubgameRuntime *game, TrackRowCell *cell, Player *player)
{
  TrackPickupState *p_state; // eax
  int v4; // edx
  JetPackSlotCursor *jetpack_cursor; // esi
  float *position_x; // ebx
  uint32_t v7; // eax
  double v8; // st7
  BodNode *jetpack_node; // ecx
  BodNode **p_first; // eax
  BodNode *first; // edx
  struct BodNode *list_prev; // edx
  uint32_t list_flags; // eax
  Sprite *sprite; // eax
  SpriteFlag flags; // ecx
  Vec3 *sprite_position; // edx
  float v17; // [esp+Ch] [ebp-8h]
  float z; // [esp+10h] [ebp-4h]

  p_state = &game->jetpack_pickup.state;
  v4 = 0;
  while ( *p_state )
  {
    ++v4;
    p_state += 103;
    if ( v4 >= 1 )
      return;
  }
  jetpack_cursor = (JetPackSlotCursor *)((char *)game + 412 * v4);
  jetpack_cursor->jetpack.state = TRACK_PICKUP_STATE_ACTIVE;
  jetpack_cursor->jetpack.owner = player;
  position_x = &jetpack_cursor->jetpack.bod.position.x;
  z = cell->anchor_position.z;
  v17 = cell->anchor_position.y + 1.5;
  jetpack_cursor->jetpack.bod.position.x = cell->anchor_position.x;
  jetpack_cursor->jetpack.bod.position.y = v17;
  jetpack_cursor->jetpack.bod.position.z = z;
  v7 = cell->lane_and_flags & 7;
  if ( v7 == 3 && cell[-1].tile_id == SUBLOC_TILE_WALL2 && cell[2].tile_id == SUBLOC_TILE_WALL2 )
  {
    v8 = *position_x + 0.5;
  }
  else
  {
    if ( v7 != 4 || cell[-2].tile_id != SUBLOC_TILE_WALL2 || cell[1].tile_id != SUBLOC_TILE_WALL2 )
      goto LABEL_14;
    v8 = *position_x - 0.5;
  }
  *position_x = v8;
LABEL_14:
  jetpack_node = &jetpack_cursor->jetpack.bod.bod;
  if ( (jetpack_cursor->jetpack.bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    p_first = &g_game_base->active_bod_list.first;
    first = g_game_base->active_bod_list.first;
    if ( first )
    {
      first->list_prev = jetpack_node;
      (*p_first)->list_prev->list_next = *p_first;
      list_prev = (*p_first)->list_prev;
      *p_first = list_prev;
      list_prev->list_prev = nullptr;
    }
    else
    {
      *p_first = jetpack_node;
      jetpack_cursor->jetpack.bod.bod.list_prev = nullptr;
      (*p_first)->list_next = nullptr;
    }
    list_flags = jetpack_cursor->jetpack.bod.bod.list_flags;
    BYTE1(list_flags) |= 2u;
    jetpack_cursor->jetpack.bod.bod.list_flags = list_flags;
  }
  sprite = allocate_sprite(&g_sprite_manager, player->player_slot, 124, -1, -1);
  jetpack_cursor->jetpack.sprite = sprite;
  flags = sprite->flags;
  BYTE1(flags) |= 8u;
  sprite->flags = flags;
  jetpack_cursor->jetpack.sprite->gravity_step = 0.0;
  jetpack_cursor->jetpack.sprite->progress = 0.0;
  jetpack_cursor->jetpack.sprite->progress_step = 0.0;
  jetpack_cursor->jetpack.sprite->size_start = 1.5;
  jetpack_cursor->jetpack.sprite->size_end = 1.5;
  sprite_position = &jetpack_cursor->jetpack.sprite->position;
  sprite_position->x = *position_x;
  sprite_position->y = jetpack_cursor->jetpack.bod.position.y;
  sprite_position->z = jetpack_cursor->jetpack.bod.position.z;
  jetpack_cursor->jetpack.source_cell = cell;
  jetpack_cursor->jetpack.bob_phase = 0.0;
  if ( ((__int64)jetpack_cursor->jetpack.bod.position.z & 1) != 0 )
    jetpack_cursor->jetpack.bob_phase = 0.0;
  else
    jetpack_cursor->jetpack.bob_phase = 0.5;
  jetpack_cursor->jetpack.bob_phase_step = 0.012820513;
}
