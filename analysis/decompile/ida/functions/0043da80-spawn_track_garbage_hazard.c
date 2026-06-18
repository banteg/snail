/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_track_garbage_hazard @ 0x43da80 */
/* selector: spawn_track_garbage_hazard */

// Allocates and seeds one live garbage hazard from the active runtime row state. Cross-port Android and iOS symbols match this helper to `cRSubGame::AddGarbage(cRSubLoc*, cRSubGoldy*)`.
Vec3 *__thiscall spawn_track_garbage_hazard(Game *game, TrackRowCell *cell, Player *player)
{
  int slot_index; // eax
  _DWORD *scan_state; // ecx
  Vec3 *result; // eax
  float *slot_base; // esi
  GarbageHazardSlot *slot; // ebp
  float *radius; // ebx
  BodNode *tail; // edi
  BodList *active_list; // eax
  __int64 texture_variant; // rax
  Sprite *sprite; // eax
  int flags; // edx
  float staged_y; // [esp+Ch] [ebp-8h]
  int staged_z_bits; // [esp+10h] [ebp-4h]

  slot_index = 0;
  for ( scan_state = (_DWORD *)&game->garbage_hazards.slots[0].state; *scan_state; scan_state += 49 )
  {
    if ( ++slot_index >= 50 )
      return (Vec3 *)report_warningf(aRunOutOfGarbag);
  }
  slot_base = (float *)((_DWORD *)game + 49 * slot_index);
  slot = (GarbageHazardSlot *)&slot_base[877649];
  slot->next_active = game->garbage_hazards.active_head;
  game->garbage_hazards.active_head = slot;
  radius = (float *)((_DWORD *)game + 49 * slot_index + 877688);
  slot->player = player;
  *radius = (random_float_below(0.40000001) + 1.0) * 0.60000002;
  slot->state = 1;
  set_matrix_identity((TransformMatrix *)&slot->basis_right);
  staged_z_bits = *(_DWORD *)&cell->anchor_position.z;
  staged_y = *radius;
  staged_y = staged_y + cell->anchor_position.y;
  slot->world_position.x = cell->anchor_position.x;
  slot->world_position.y = staged_y;
  *(_DWORD *)&slot->world_position.z = staged_z_bits;
  project_position_onto_track_attachment(game, &slot->world_position, &slot->sprite_y_offset);
  tail = (BodNode *)((_DWORD *)game + 978393);
  active_list = (BodList *)((char *)MEMORY[0x4DF904] + 1448);
  if ( (slot->list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddbefore);
  }
  else
  {
    slot->list_next = (GarbageHazardSlot *)tail;
    if ( active_list->first == (BodNode *)tail )
    {
      tail->list_prev = (BodNode *)slot;
      active_list->first = (BodNode *)slot;
      slot->list_prev = 0;
    }
    else
    {
      slot->list_prev = (GarbageHazardSlot *)tail->list_prev;
      tail->list_prev = (BodNode *)slot;
      slot->list_prev->list_next = slot;
    }
    slot->list_flags |= 0x200u;
  }
  texture_variant = (__int64)((double)next_math_random_value() * -0.00012207031);
  sprite = allocate_sprite(unk_790F30, player->player_slot, 114 - texture_variant, -1, -1);
  slot->sprite = sprite;
  flags = sprite->flags;
  BYTE1(flags) |= 8u;
  sprite->flags = flags;
  slot->sprite->gravity_step = 0.0;
  slot->sprite->progress = 0.0;
  slot->sprite->progress_step = 0.0;
  slot->sprite->size_start = *radius;
  slot->sprite->size_end = *radius;
  result = &slot->sprite->position;
  result->x = slot->world_position.x;
  result->y = slot->world_position.y;
  result->z = slot->world_position.z;
  slot->source_cell = cell;
  slot->hidden = 0;
  return result;
}
