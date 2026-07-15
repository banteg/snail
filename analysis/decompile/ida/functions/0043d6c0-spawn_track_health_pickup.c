/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_track_health_pickup @ 0x43d6c0 */
/* selector: spawn_track_health_pickup */

// Allocates and seeds one live `SubHealth` from the eight-record owned array. Android and iOS retain `cRSubGame::AddHealth(cRSubLoc*, cRSubGoldy*)`; Android establishes no result, so the Windows reconstruction now keeps the honest void contract instead of exporting incompatible incidental register values.
void __thiscall spawn_track_health_pickup(SubgameRuntime *game, TrackRowCell *cell, Player *player)
{
  int v3; // ebx
  TrackPickupState *i; // eax
  TrackRowCell *v5; // ebp
  FrameBodBase *v6; // esi
  FrameBodBase *v7; // eax
  FrameBodBase **p_first; // ecx
  FrameBodBase *first; // edx
  FrameBodBase *list_prev; // edx
  uint32_t list_flags; // ecx
  _DWORD *sprite; // eax
  int v13; // ecx
  _DWORD *v14; // ecx
  float v16; // [esp+Ch] [ebp-8h]
  float z; // [esp+10h] [ebp-4h]

  v3 = 0;
  for ( i = &game->health_pickups[0].state; *i; i += 29 )
  {
    if ( ++v3 >= 8 )
      return;
  }
  v5 = cell;
  v6 = (FrameBodBase *)((char *)game + 116 * v3);
  v6[62465].bod.vtable = (void **)1;
  v6[62465].bod.list_flags = (uint32_t)player;
  z = cell->anchor_position.z;
  v16 = cell->anchor_position.y + 0.60000002;
  v6[62464].position.x = cell->anchor_position.x;
  v6[62464].position.y = v16;
  v6[62464].position.z = z;
  v7 = v6 + 62464;
  if ( (v6[62464].bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    p_first = &g_game_base->active_bod_list.first;
    first = g_game_base->active_bod_list.first;
    if ( first )
    {
      first->bod.list_prev = v7;
      (*p_first)->bod.list_prev->bod.list_next = *p_first;
      v5 = cell;
      list_prev = (*p_first)->bod.list_prev;
      *p_first = list_prev;
      list_prev->bod.list_prev = nullptr;
    }
    else
    {
      *p_first = v7;
      v6[62464].bod.list_prev = nullptr;
      (*p_first)->bod.list_next = nullptr;
    }
    list_flags = v6[62464].bod.list_flags;
    BYTE1(list_flags) |= 2u;
    v6[62464].bod.list_flags = list_flags;
  }
  sprite = allocate_sprite(g_sprite_manager, player->player_slot, 57, -1, -1);
  LODWORD(v6[62465].color.g) = sprite;
  v13 = sprite[1];
  BYTE1(v13) |= 8u;
  sprite[1] = v13;
  *(_DWORD *)(LODWORD(v6[62465].color.g) + 120) = 0;
  *(_DWORD *)(LODWORD(v6[62465].color.g) + 104) = 0;
  *(_DWORD *)(LODWORD(v6[62465].color.g) + 108) = 0;
  *(_DWORD *)(LODWORD(v6[62465].color.g) + 96) = 1058642330;
  *(_DWORD *)(LODWORD(v6[62465].color.g) + 100) = 1058642330;
  v14 = (_DWORD *)(LODWORD(v6[62465].color.g) + 72);
  *v14 = LODWORD(v6[62464].position.x);
  v14[1] = LODWORD(v6[62464].position.y);
  v14[2] = LODWORD(v6[62464].position.z);
  LODWORD(v6[62465].color.b) = v5;
  v6[62465].color.a = 0.0;
  if ( ((__int64)v6[62464].position.z & 1) != 0 )
    v6[62465].color.a = 0.0;
  else
    v6[62465].color.a = 0.5;
  game->health_pickups[v3].bob_phase_step = 0.012820513;
}
