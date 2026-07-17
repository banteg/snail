/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_track_garbage_hazard @ 0x43da80 */
/* selector: spawn_track_garbage_hazard */

// Exact void allocator and initializer for one live `SubGarbage` from the active runtime row state. It scans the 50 owned 0xc4-byte records after the pool's borrowed active-chain head; the sole Windows caller discards EAX, while Android leaves incompatible incidental results on success and exhaustion. Android and iOS identify the caller-owned method as `cRSubGame::AddGarbage(cRSubLoc*, cRSubGoldy*)`.
void __thiscall spawn_track_garbage_hazard(SubgameRuntime *game, TrackRowCell *cell, Player *player)
{
  int v3; // eax
  int32_t *i; // ecx
  char *v6; // esi
  struct BodNode *v7; // ebp
  float *p_radius; // ebx
  Player *p_player; // edi
  BodList *p_active_bod_list; // eax
  __int64 v11; // rax
  _DWORD *sprite; // eax
  int v13; // edx
  _DWORD *v14; // eax
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
  v6 = (char *)game + 196 * v3;
  *((_DWORD *)v6 + 877681) = game->garbage_hazards.active_head;
  v7 = (struct BodNode *)(v6 + 3510596);
  game->garbage_hazards.active_head = (SubGarbage *)(v6 + 3510596);
  p_radius = &game->garbage_hazards.slots[v3].radius;
  *((_DWORD *)v6 + 877697) = player;
  *p_radius = (random_float_below(0.40000001) + 1.0) * 0.60000002;
  *((_DWORD *)v6 + 877682) = 1;
  set_matrix_identity((TransformMatrix *)(v6 + 3510652));
  z = cell->anchor_position.z;
  v15 = *p_radius + cell->anchor_position.y;
  *((_DWORD *)v6 + 877675) = LODWORD(cell->anchor_position.x);
  *((float *)v6 + 877676) = v15;
  *((float *)v6 + 877677) = z;
  project_position_onto_track_attachment(game, (float *)v6 + 877675, (float *)v6 + 877689);
  p_player = &game->player;
  p_active_bod_list = &g_game_base->active_bod_list;
  if ( (*((_DWORD *)v6 + 877650) & 0x200) != 0 )
  {
    report_errorf(aListAddbefore);
  }
  else
  {
    *((_DWORD *)v6 + 877652) = p_player;
    if ( (Player *)p_active_bod_list->first == p_player )
    {
      p_player->body.bod.bod.list_prev = v7;
      p_active_bod_list->first = v7;
      *((_DWORD *)v6 + 877651) = 0;
    }
    else
    {
      *((_DWORD *)v6 + 877651) = p_player->body.bod.bod.list_prev;
      p_player->body.bod.bod.list_prev = v7;
      *(_DWORD *)(*((_DWORD *)v6 + 877651) + 12) = v7;
    }
    *((_DWORD *)v6 + 877650) |= 0x200u;
  }
  v11 = (__int64)((double)next_math_random_value() * -0.00012207031);
  sprite = allocate_sprite(g_sprite_manager, *(_DWORD *)(*((_DWORD *)v6 + 877697) + 896), 114 - v11, -1, -1);
  *((_DWORD *)v6 + 877694) = sprite;
  v13 = sprite[1];
  BYTE1(v13) |= 8u;
  sprite[1] = v13;
  *(_DWORD *)(*((_DWORD *)v6 + 877694) + 120) = 0;
  *(_DWORD *)(*((_DWORD *)v6 + 877694) + 104) = 0;
  *(_DWORD *)(*((_DWORD *)v6 + 877694) + 108) = 0;
  *(float *)(*((_DWORD *)v6 + 877694) + 96) = *p_radius;
  *(float *)(*((_DWORD *)v6 + 877694) + 100) = *p_radius;
  v14 = (_DWORD *)(*((_DWORD *)v6 + 877694) + 72);
  *v14 = *((_DWORD *)v6 + 877675);
  v14[1] = *((_DWORD *)v6 + 877676);
  v14[2] = *((_DWORD *)v6 + 877677);
  *((_DWORD *)v6 + 877695) = cell;
  v6[3510784] = 0;
}
