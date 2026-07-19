/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_track_garbage_hazard @ 0x43da80 */
/* selector: spawn_track_garbage_hazard */

// Exact void allocator and initializer for one live `SubGarbage` from the active runtime row state. It scans the 50 owned 0xc4-byte records for `SUB_GARBAGE_STATE_INACTIVE` after the pool's borrowed active-chain head, then activates the selected slot; the sole Windows caller discards EAX, while Android leaves incompatible incidental results on success and exhaustion. Android and iOS identify the caller-owned method as `cRSubGame::AddGarbage(cRSubLoc*, cRSubGoldy*)`.
void __thiscall spawn_track_garbage_hazard(SubgameRuntime *game, TrackRowCell *cell, Player *player)
{
  int v3; // eax
  SubGarbageState *i; // ecx
  struct SubGarbageSlotCursor *garbage_slot_cursor; // esi
  SubGarbage *p_garbage; // ebp
  float *p_radius; // ebx
  Player *p_player; // edi
  BodList *p_active_bod_list; // eax
  __int64 v11; // rax
  Sprite *sprite; // eax
  SpriteFlag flags; // edx
  Vec3 *p_position; // eax
  float v15; // [esp+Ch] [ebp-8h]
  float z; // [esp+10h] [ebp-4h]

  v3 = 0;
  for ( i = &game->garbage_hazards.slots[0].state; *i; i += 49 )
  {
    if ( ++v3 >= 50 )
    {
      report_warningf(aRunOutOfGarbag);
      return;
    }
  }
  garbage_slot_cursor = (struct SubGarbageSlotCursor *)((char *)game + 196 * v3);
  garbage_slot_cursor->garbage.next_active = game->garbage_hazards.active_head;
  p_garbage = &garbage_slot_cursor->garbage;
  game->garbage_hazards.active_head = &garbage_slot_cursor->garbage;
  p_radius = &game->garbage_hazards.slots[v3].radius;
  garbage_slot_cursor->garbage.owner_player = player;
  *p_radius = (random_float_below(0.40000001) + 1.0) * 0.60000002;
  garbage_slot_cursor->garbage.state = SUB_GARBAGE_STATE_ACTIVE;
  set_matrix_identity(&garbage_slot_cursor->garbage.body.transform);
  z = cell->anchor_position.z;
  v15 = *p_radius + cell->anchor_position.y;
  garbage_slot_cursor->garbage.body.transform.position.x = cell->anchor_position.x;
  garbage_slot_cursor->garbage.body.transform.position.y = v15;
  garbage_slot_cursor->garbage.body.transform.position.z = z;
  project_position_onto_track_attachment(
    game,
    (Vec3 *)&garbage_slot_cursor->garbage.body.transform.position,
    &garbage_slot_cursor->garbage.attachment_facing_angle);
  p_player = &game->player;
  p_active_bod_list = &g_game_base->active_bod_list;
  if ( (garbage_slot_cursor->garbage.body.bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddbefore);
  }
  else
  {
    garbage_slot_cursor->garbage.body.bod.bod.list_next = &p_player->body.bod.bod;
    if ( (Player *)p_active_bod_list->first == p_player )
    {
      p_player->body.bod.bod.list_prev = &p_garbage->body.bod.bod;
      p_active_bod_list->first = &p_garbage->body.bod.bod;
      garbage_slot_cursor->garbage.body.bod.bod.list_prev = nullptr;
    }
    else
    {
      garbage_slot_cursor->garbage.body.bod.bod.list_prev = p_player->body.bod.bod.list_prev;
      p_player->body.bod.bod.list_prev = &p_garbage->body.bod.bod;
      garbage_slot_cursor->garbage.body.bod.bod.list_prev->list_next = &p_garbage->body.bod.bod;
    }
    garbage_slot_cursor->garbage.body.bod.bod.list_flags |= 0x200u;
  }
  v11 = (__int64)((double)next_math_random_value() * -0.00012207031);
  sprite = allocate_sprite(&g_sprite_manager, garbage_slot_cursor->garbage.owner_player->player_slot, 114 - v11, -1, -1);
  garbage_slot_cursor->garbage.sprite = sprite;
  flags = sprite->flags;
  BYTE1(flags) |= 8u;
  sprite->flags = flags;
  garbage_slot_cursor->garbage.sprite->gravity_step = 0.0;
  garbage_slot_cursor->garbage.sprite->progress = 0.0;
  garbage_slot_cursor->garbage.sprite->progress_step = 0.0;
  garbage_slot_cursor->garbage.sprite->size_start = *p_radius;
  garbage_slot_cursor->garbage.sprite->size_end = *p_radius;
  p_position = &garbage_slot_cursor->garbage.sprite->position;
  p_position->x = garbage_slot_cursor->garbage.body.transform.position.x;
  p_position->y = garbage_slot_cursor->garbage.body.transform.position.y;
  p_position->z = garbage_slot_cursor->garbage.body.transform.position.z;
  garbage_slot_cursor->garbage.source_cell = cell;
  garbage_slot_cursor->garbage.hidden = 0;
}
