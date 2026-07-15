/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_track_jetpack_pickup @ 0x43d890 */
/* selector: spawn_track_jetpack_pickup */

// Seeds the owned `JetPack` singleton from the active runtime cell. Android and iOS retain `cRSubGame::AddJetPack(cRSubLoc*, cRSubGoldy*)`; Android establishes no result, so the Windows reconstruction keeps the honest void contract rather than exporting incompatible incidental register values.
void __thiscall spawn_track_jetpack_pickup(SubgameRuntime *game, TrackRowCell *cell, Player *player)
{
  TrackPickupState *p_state; // eax
  int v4; // edx
  char *v5; // esi
  float *v6; // ebx
  uint32_t v7; // eax
  double v8; // st7
  FrameBodBase *v9; // ecx
  FrameBodBase **p_first; // eax
  FrameBodBase *first; // edx
  FrameBodBase *list_prev; // edx
  int v13; // eax
  _DWORD *sprite; // eax
  int v15; // ecx
  _DWORD *v16; // edx
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
  v5 = (char *)game + 412 * v4;
  *((_DWORD *)v5 + 874407) = 1;
  *((_DWORD *)v5 + 874408) = player;
  v6 = (float *)(v5 + 3497588);
  z = cell->anchor_position.z;
  v17 = cell->anchor_position.y + 1.5;
  *((_DWORD *)v5 + 874397) = LODWORD(cell->anchor_position.x);
  *((float *)v5 + 874398) = v17;
  *((float *)v5 + 874399) = z;
  v7 = cell->lane_and_flags & 7;
  if ( v7 == 3 && cell[-1].tile_id == 14 && cell[2].tile_id == 14 )
  {
    v8 = *v6 + 0.5;
  }
  else
  {
    if ( v7 != 4 || cell[-2].tile_id != 14 || cell[1].tile_id != 14 )
      goto LABEL_14;
    v8 = *v6 - 0.5;
  }
  *v6 = v8;
LABEL_14:
  v9 = (FrameBodBase *)(v5 + 3497572);
  if ( (*((_DWORD *)v5 + 874394) & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    p_first = &g_game_base->active_bod_list.first;
    first = g_game_base->active_bod_list.first;
    if ( first )
    {
      first->bod.list_prev = v9;
      (*p_first)->bod.list_prev->bod.list_next = *p_first;
      list_prev = (*p_first)->bod.list_prev;
      *p_first = list_prev;
      list_prev->bod.list_prev = nullptr;
    }
    else
    {
      *p_first = v9;
      *((_DWORD *)v5 + 874395) = 0;
      (*p_first)->bod.list_next = nullptr;
    }
    v13 = *((_DWORD *)v5 + 874394);
    BYTE1(v13) |= 2u;
    *((_DWORD *)v5 + 874394) = v13;
  }
  sprite = allocate_sprite(g_sprite_manager, player->player_slot, 124, -1, -1);
  *((_DWORD *)v5 + 874418) = sprite;
  v15 = sprite[1];
  BYTE1(v15) |= 8u;
  sprite[1] = v15;
  *(_DWORD *)(*((_DWORD *)v5 + 874418) + 120) = 0;
  *(_DWORD *)(*((_DWORD *)v5 + 874418) + 104) = 0;
  *(_DWORD *)(*((_DWORD *)v5 + 874418) + 108) = 0;
  *(_DWORD *)(*((_DWORD *)v5 + 874418) + 96) = 1069547520;
  *(_DWORD *)(*((_DWORD *)v5 + 874418) + 100) = 1069547520;
  v16 = (_DWORD *)(*((_DWORD *)v5 + 874418) + 72);
  *v16 = *(_DWORD *)v6;
  v16[1] = *((_DWORD *)v5 + 874398);
  v16[2] = *((_DWORD *)v5 + 874399);
  *((_DWORD *)v5 + 874419) = cell;
  *((_DWORD *)v5 + 874420) = 0;
  if ( ((__int64)*((float *)v5 + 874399) & 1) != 0 )
    *((_DWORD *)v5 + 874420) = 0;
  else
    *((_DWORD *)v5 + 874420) = 1056964608;
  *((_DWORD *)v5 + 874421) = 1012010273;
}
