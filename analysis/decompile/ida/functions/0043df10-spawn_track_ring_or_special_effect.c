/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_track_ring_or_special_effect @ 0x43df10 */
/* selector: spawn_track_ring_or_special_effect */

// Void Windows `cRSubGame::AddRing(...)`: dispatches authored Ring=* rows into the ring, explode, or slow particle effect families and immediately invokes the selected SubRing's slot-zero AI callback. All five Windows callers discard EAX; the independent iOS body likewise returns from failure paths without establishing a result.
void __thiscall spawn_track_ring_or_special_effect(
        SubgameRuntime *game,
        TrackRowCell *cell,
        int32_t requested_kind,
        Player *player,
        float ring_speed)
{
  int v5; // eax
  SubRingState *i; // ecx
  char *v8; // esi
  int32_t v9; // ebp
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  double v14; // st7
  double v15; // st7
  double v16; // st7
  int v17; // eax
  SubRing *v18; // esi
  FrameBodBase **p_first; // eax
  FrameBodBase *first; // ecx
  FrameBodBase *list_prev; // ecx
  float v22; // [esp+10h] [ebp-10h]
  float v23; // [esp+18h] [ebp-8h]
  float v24; // [esp+18h] [ebp-8h]
  float v25; // [esp+18h] [ebp-8h]
  float v26; // [esp+18h] [ebp-8h]
  float v27; // [esp+18h] [ebp-8h]
  float v28; // [esp+18h] [ebp-8h]
  float v29; // [esp+1Ch] [ebp-4h]
  float v30; // [esp+1Ch] [ebp-4h]
  float v31; // [esp+1Ch] [ebp-4h]
  float z; // [esp+1Ch] [ebp-4h]
  float v33; // [esp+1Ch] [ebp-4h]
  float v34; // [esp+1Ch] [ebp-4h]

  v5 = 0;
  for ( i = &game->ring_effects.slots[0].state; *i; i += 126 )
  {
    if ( ++v5 >= 2 )
      return;
  }
  v8 = (char *)game + 504 * v5;
  v22 = 1.0
      / ((2.0 - game->base_subgame_rate * 0.30000001)
       * 60.0)
      * ((double)player->movement_flag_selector
       * 0.125)
      * game->subgame_rate
      * 6.2831855;
  set_matrix_identity((TransformMatrix *)(v8 + 3520452));
  v9 = requested_kind;
  *((_DWORD *)v8 + 880132) = player;
  if ( requested_kind == 4
    && (random_float_below(1.0) > 0.93000001 || random_float_below(1.0) > 0.5 && game->level_mode == 4) )
  {
    v9 = 3;
  }
  switch ( v9 )
  {
    case 0:
    case 4:
      v25 = cell->anchor_position.y + 2.5;
      v14 = cell->anchor_position.z + 6.0;
      *((_DWORD *)v8 + 880125) = LODWORD(cell->anchor_position.x);
      v31 = v14;
      *((float *)v8 + 880126) = v25;
      *((float *)v8 + 880127) = v31;
      v15 = random_float_below(1.0);
      *((float *)v8 + 880125) = (v15 - 0.5 + v15 - 0.5) * 3.0;
      goto LABEL_13;
    case 1:
    case 3:
      v24 = cell->anchor_position.y + 2.5;
      v12 = cell->anchor_position.z + 6.0;
      *((_DWORD *)v8 + 880125) = LODWORD(cell->anchor_position.x);
      v30 = v12;
      *((float *)v8 + 880126) = v24;
      *((float *)v8 + 880127) = v30;
      v13 = random_float_below(1.0);
      *((float *)v8 + 880125) = (v13 - 0.5 + v13 - 0.5) * 3.0;
      goto LABEL_13;
    case 2:
      v23 = cell->anchor_position.y + 3.5;
      v10 = cell->anchor_position.z + 17.0;
      *((_DWORD *)v8 + 880125) = LODWORD(cell->anchor_position.x);
      v29 = v10;
      *((float *)v8 + 880126) = v23;
      *((float *)v8 + 880127) = v29;
      v11 = random_float_below(1.0);
      *((float *)v8 + 880125) = (v11 - 0.5 + v11 - 0.5) * 3.0;
LABEL_13:
      *((float *)v8 + 880219) = random_float_below(1.0) * 6.2831855;
      *((float *)v8 + 880220) = v22;
      break;
    case 5:
      z = cell->anchor_position.z;
      v26 = cell->anchor_position.y + 2.5;
      *((_DWORD *)v8 + 880125) = LODWORD(cell->anchor_position.x);
      *((float *)v8 + 880126) = v26;
      *((float *)v8 + 880127) = z;
      goto LABEL_19;
    case 6:
      v33 = cell->anchor_position.z;
      v27 = cell->anchor_position.y + 2.5;
      *((_DWORD *)v8 + 880125) = LODWORD(cell->anchor_position.x);
      *((float *)v8 + 880126) = v27;
      *((float *)v8 + 880127) = v33;
      goto LABEL_19;
    case 7:
    case 8:
      v16 = cell->anchor_position.y + 2.5;
      v34 = cell->anchor_position.z;
      *((_DWORD *)v8 + 880125) = LODWORD(cell->anchor_position.x);
      v28 = v16;
      *((float *)v8 + 880126) = v28;
      *((float *)v8 + 880127) = v34;
LABEL_19:
      *((float *)v8 + 880219) = random_float_below(1.0) * 6.2831855;
      *((float *)v8 + 880220) = 1.0 / (ring_speed * 60.0) * game->subgame_rate * 6.2831855;
      break;
    default:
      break;
  }
  if ( get_track_grid_cell_at_world_position(game, (Vec3 *)v8 + 293375)->tile_id != 14 )
  {
    *((_DWORD *)v8 + 880133) = v9;
    *((_DWORD *)v8 + 880134) = player->lives;
    *((_DWORD *)v8 + 880131) = 1;
    if ( random_float_below(1.0) > 0.5 )
      *((float *)v8 + 880220) = *((float *)v8 + 880220) * -1.0;
    v17 = *((_DWORD *)v8 + 880100);
    v18 = (SubRing *)(v8 + 3520396);
    if ( (v17 & 0x200) != 0 )
    {
      report_errorf(aListAdd);
    }
    else
    {
      p_first = &g_game_base->active_bod_list.first;
      first = g_game_base->active_bod_list.first;
      if ( first )
      {
        first->bod.list_prev = (FrameBodBase *)v18;
        (*p_first)->bod.list_prev->bod.list_next = *p_first;
        list_prev = (*p_first)->bod.list_prev;
        *p_first = list_prev;
        list_prev->bod.list_prev = nullptr;
      }
      else
      {
        *p_first = (FrameBodBase *)v18;
        v18->body.bod.bod.list_prev = nullptr;
        (*p_first)->bod.list_next = nullptr;
      }
      v18->body.bod.bod.list_flags |= 0x200u;
    }
    initialize_ring_or_special_effect_particles(v18, player->lives);
    (*(void (__thiscall **)(SubRing *))v18->body.bod.bod.vtable)(v18);
  }
}
