/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_track_ring_or_special_effect @ 0x43df10 */
/* selector: spawn_track_ring_or_special_effect */

// Void Windows `cRSubGame::AddRing(cRSubLoc*, int, cRSubGoldy*, float)`: scans the two SubgameRuntime-owned SubRing slots, mutates the ordinary integer kind parameter when the default ring randomizes to slow, and stores the resulting typed `SubRingKind`. Its nine distinct authored paths preserve `RR` through `RR13`, dispatch Ring=* rows into ring, explode, slow, or power-up effects, link the inherited BOD, initialize ten inline SubRingStar children, and invoke slot-zero AI. All five Windows callers discard EAX; the independent iOS body likewise returns from failure paths without establishing a result.
void __thiscall spawn_track_ring_or_special_effect(
        SubgameRuntime *game,
        TrackRowCell *cell,
        int32_t requested_kind,
        Player *player,
        float ring_speed)
{
  int32_t slot_index; // eax
  SubRingState *state_cursor; // ecx
  SubRingSlotCursor *slot_cursor; // esi
  int32_t effective_kind; // ebp
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  double v14; // st7
  double v15; // st7
  double v16; // st7
  uint32_t list_flags; // eax
  SubRing *selected_ring; // esi
  BodNode **active_head; // eax
  BodNode *active_first; // ecx
  BodNode *promoted_head; // ecx
  float default_phase_step; // [esp+10h] [ebp-10h]
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

  slot_index = 0;
  for ( state_cursor = &game->ring_effects.slots[0].state; *state_cursor; state_cursor += 126 )
  {
    if ( ++slot_index >= 2 )
      return;
  }
  slot_cursor = (SubRingSlotCursor *)((char *)game + 504 * slot_index);
  default_phase_step = 1.0
                     / ((2.0 - game->base_subgame_rate * 0.30000001)
                      * 60.0)
                     * ((double)player->movement_flag_selector
                      * 0.125)
                     * game->subgame_rate
                     * 6.2831855;
  set_matrix_identity(&slot_cursor->ring.body.transform);
  effective_kind = requested_kind;
  slot_cursor->ring.owner_player = player;
  if ( requested_kind == 4
    && (random_float_below(1.0) > 0.93000001 || random_float_below(1.0) > 0.5 && game->level_mode == 4) )
  {
    effective_kind = 3;
  }
  switch ( effective_kind )
  {
    case 0:
    case 4:
      v25 = cell->anchor_position.y + 2.5;
      v14 = cell->anchor_position.z + 6.0;
      slot_cursor->ring.body.transform.position.x = cell->anchor_position.x;
      v31 = v14;
      slot_cursor->ring.body.transform.position.y = v25;
      slot_cursor->ring.body.transform.position.z = v31;
      v15 = random_float_below(1.0);
      slot_cursor->ring.body.transform.position.x = (v15 - 0.5 + v15 - 0.5) * 3.0;
      goto LABEL_13;
    case 1:
    case 3:
      v24 = cell->anchor_position.y + 2.5;
      v12 = cell->anchor_position.z + 6.0;
      slot_cursor->ring.body.transform.position.x = cell->anchor_position.x;
      v30 = v12;
      slot_cursor->ring.body.transform.position.y = v24;
      slot_cursor->ring.body.transform.position.z = v30;
      v13 = random_float_below(1.0);
      slot_cursor->ring.body.transform.position.x = (v13 - 0.5 + v13 - 0.5) * 3.0;
      goto LABEL_13;
    case 2:
      v23 = cell->anchor_position.y + 3.5;
      v10 = cell->anchor_position.z + 17.0;
      slot_cursor->ring.body.transform.position.x = cell->anchor_position.x;
      v29 = v10;
      slot_cursor->ring.body.transform.position.y = v23;
      slot_cursor->ring.body.transform.position.z = v29;
      v11 = random_float_below(1.0);
      slot_cursor->ring.body.transform.position.x = (v11 - 0.5 + v11 - 0.5) * 3.0;
LABEL_13:
      slot_cursor->ring.active_phase = random_float_below(1.0) * 6.2831855;
      slot_cursor->ring.active_phase_step = default_phase_step;
      break;
    case 5:
      z = cell->anchor_position.z;
      v26 = cell->anchor_position.y + 2.5;
      slot_cursor->ring.body.transform.position.x = cell->anchor_position.x;
      slot_cursor->ring.body.transform.position.y = v26;
      slot_cursor->ring.body.transform.position.z = z;
      goto LABEL_19;
    case 6:
      v33 = cell->anchor_position.z;
      v27 = cell->anchor_position.y + 2.5;
      slot_cursor->ring.body.transform.position.x = cell->anchor_position.x;
      slot_cursor->ring.body.transform.position.y = v27;
      slot_cursor->ring.body.transform.position.z = v33;
      goto LABEL_19;
    case 7:
    case 8:
      v16 = cell->anchor_position.y + 2.5;
      v34 = cell->anchor_position.z;
      slot_cursor->ring.body.transform.position.x = cell->anchor_position.x;
      v28 = v16;
      slot_cursor->ring.body.transform.position.y = v28;
      slot_cursor->ring.body.transform.position.z = v34;
LABEL_19:
      slot_cursor->ring.active_phase = random_float_below(1.0) * 6.2831855;
      slot_cursor->ring.active_phase_step = 1.0 / (ring_speed * 60.0) * game->subgame_rate * 6.2831855;
      break;
    default:
      break;
  }
  if ( get_track_grid_cell_at_world_position(game, (Vec3 *)&slot_cursor->ring.body.transform.position)->tile_id != SUBLOC_TILE_WALL2 )
  {
    slot_cursor->ring.kind = effective_kind;
    slot_cursor->ring.owner_lives_snapshot = player->lives;
    slot_cursor->ring.state = SUB_RING_STATE_ACTIVE;
    if ( random_float_below(1.0) > 0.5 )
      slot_cursor->ring.active_phase_step = slot_cursor->ring.active_phase_step * -1.0;
    list_flags = slot_cursor->ring.body.bod.bod.list_flags;
    selected_ring = &slot_cursor->ring;
    if ( (list_flags & 0x200) != 0 )
    {
      report_errorf(aListAdd);
    }
    else
    {
      active_head = &g_game_base->active_bod_list.first;
      active_first = g_game_base->active_bod_list.first;
      if ( active_first )
      {
        active_first->list_prev = &selected_ring->body.bod.bod;
        (*active_head)->list_prev->list_next = *active_head;
        promoted_head = (*active_head)->list_prev;
        *active_head = promoted_head;
        promoted_head->list_prev = nullptr;
      }
      else
      {
        *active_head = &selected_ring->body.bod.bod;
        selected_ring->body.bod.bod.list_prev = nullptr;
        (*active_head)->list_next = nullptr;
      }
      selected_ring->body.bod.bod.list_flags |= 0x200u;
    }
    initialize_ring_or_special_effect_particles(selected_ring, player->lives);
    (*(void (__thiscall **)(SubRing *))selected_ring->body.bod.bod.vtable)(selected_ring);
  }
}
