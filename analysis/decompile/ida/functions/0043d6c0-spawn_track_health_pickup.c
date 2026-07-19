/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_track_health_pickup @ 0x43d6c0 */
/* selector: spawn_track_health_pickup */

// Allocates and seeds one live `SubHealth` from the eight-record owned array. Android and iOS retain `cRSubGame::AddHealth(cRSubLoc*, cRSubGoldy*)`; Android establishes no result, so the Windows reconstruction now keeps the honest void contract instead of exporting incompatible incidental register values.
void __thiscall spawn_track_health_pickup(SubgameRuntime *game, TrackRowCell *cell, Player *player)
{
  int v3; // ebx
  TrackPickupState *i; // eax
  TrackRowCell *v5; // ebp
  SubHealthSlotCursor *health_cursor; // esi
  BodNode *health_node; // eax
  BodNode **p_first; // ecx
  BodNode *first; // edx
  struct BodNode *list_prev; // edx
  uint32_t list_flags; // ecx
  Sprite *sprite; // eax
  SpriteFlag flags; // ecx
  float v15; // [esp+Ch] [ebp-8h]
  float z; // [esp+10h] [ebp-4h]

  v3 = 0;
  for ( i = &game->health_pickups[0].state; *i; i += 29 )
  {
    if ( ++v3 >= 8 )
      return;
  }
  v5 = cell;
  health_cursor = (SubHealthSlotCursor *)((char *)game + 116 * v3);
  health_cursor->health.state = TRACK_PICKUP_STATE_ACTIVE;
  health_cursor->health.owner = player;
  z = cell->anchor_position.z;
  v15 = cell->anchor_position.y + 0.60000002;
  health_cursor->health.bod.position.x = cell->anchor_position.x;
  health_cursor->health.bod.position.y = v15;
  health_cursor->health.bod.position.z = z;
  health_node = &health_cursor->health.bod.bod;
  if ( (health_cursor->health.bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    p_first = &g_game_base->active_bod_list.first;
    first = g_game_base->active_bod_list.first;
    if ( first )
    {
      first->list_prev = health_node;
      (*p_first)->list_prev->list_next = *p_first;
      v5 = cell;
      list_prev = (*p_first)->list_prev;
      *p_first = list_prev;
      list_prev->list_prev = nullptr;
    }
    else
    {
      *p_first = health_node;
      health_cursor->health.bod.bod.list_prev = nullptr;
      (*p_first)->list_next = nullptr;
    }
    list_flags = health_cursor->health.bod.bod.list_flags;
    BYTE1(list_flags) |= 2u;
    health_cursor->health.bod.bod.list_flags = list_flags;
  }
  sprite = allocate_sprite(&g_sprite_manager, player->player_slot, 57, -1, -1);
  health_cursor->health.sprite = sprite;
  flags = sprite->flags;
  BYTE1(flags) |= 8u;
  sprite->flags = flags;
  health_cursor->health.sprite->gravity_step = 0.0;
  health_cursor->health.sprite->progress = 0.0;
  health_cursor->health.sprite->progress_step = 0.0;
  health_cursor->health.sprite->size_start = 0.60000002;
  health_cursor->health.sprite->size_end = 0.60000002;
  health_cursor->health.sprite->position = health_cursor->health.bod.position;
  health_cursor->health.source_cell = v5;
  health_cursor->health.bob_phase = 0.0;
  if ( ((__int64)health_cursor->health.bod.position.z & 1) != 0 )
    health_cursor->health.bob_phase = 0.0;
  else
    health_cursor->health.bob_phase = 0.5;
  game->health_pickups[v3].bob_phase_step = 0.012820513;
}
