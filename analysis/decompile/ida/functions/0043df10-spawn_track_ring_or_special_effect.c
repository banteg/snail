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
  double v17; // st7
  double v18; // st7
  double v19; // st7
  double v20; // st7
  double v21; // st7
  double v22; // st7
  double v23; // st7
  double v24; // st7
  uint32_t list_flags; // eax
  SubRing *selected_ring; // esi
  BodNode **active_head; // eax
  BodNode *active_first; // ecx
  BodNode *promoted_head; // ecx
  float default_phase_step; // [esp+10h] [ebp-10h]
  float v31; // [esp+18h] [ebp-8h]
  float v32; // [esp+18h] [ebp-8h]
  float v33; // [esp+18h] [ebp-8h]
  float v34; // [esp+18h] [ebp-8h]
  float v35; // [esp+18h] [ebp-8h]
  float v36; // [esp+18h] [ebp-8h]
  float v37; // [esp+18h] [ebp-8h]
  float v38; // [esp+18h] [ebp-8h]
  float v39; // [esp+18h] [ebp-8h]
  float v40; // [esp+1Ch] [ebp-4h]
  float v41; // [esp+1Ch] [ebp-4h]
  float v42; // [esp+1Ch] [ebp-4h]
  float v43; // [esp+1Ch] [ebp-4h]
  float v44; // [esp+1Ch] [ebp-4h]
  float z; // [esp+1Ch] [ebp-4h]
  float v46; // [esp+1Ch] [ebp-4h]
  float v47; // [esp+1Ch] [ebp-4h]
  float v48; // [esp+1Ch] [ebp-4h]

  slot_index = 0;
  for ( state_cursor = &game->ring_effects.slots[0].state; *state_cursor != SUB_RING_STATE_INACTIVE; state_cursor += 126 )
  {
    if ( ++slot_index >= 2 )
      return;
  }
  slot_cursor = (SubRingSlotCursor *)((char *)game + 504 * slot_index);
  default_phase_step = 1.0
                     / ((2.0 - game->base_subgame_rate * 0.30000001)
                      * 60.0)
                     * ((double)player->shooting_tier
                      * 0.125)
                     * game->subgame_rate
                     * 6.2831855;
  set_matrix_identity(&slot_cursor->ring.body.transform);
  effective_kind = requested_kind;
  slot_cursor->ring.owner_player = player;
  if ( requested_kind == 4
    && (random_float_below(1.0, aRt) > 0.93000001 || random_float_below(1.0, aRt2) > 0.5 && game->level_mode == 4) )
  {
    effective_kind = 3;
  }
  switch ( effective_kind )
  {
    case 0:
      v31 = cell->anchor_position.y + 2.5;
      v10 = cell->anchor_position.z + 6.0;
      slot_cursor->ring.body.transform.position.x = cell->anchor_position.x;
      v40 = v10;
      slot_cursor->ring.body.transform.position.y = v31;
      slot_cursor->ring.body.transform.position.z = v40;
      v11 = random_float_below(1.0, aRr);
      slot_cursor->ring.body.transform.position.x = (v11 - 0.5 + v11 - 0.5) * 3.0;
      v12 = random_float_below(1.0, aRr1);
      goto LABEL_17;
    case 1:
      v32 = cell->anchor_position.y + 2.5;
      v13 = cell->anchor_position.z + 6.0;
      slot_cursor->ring.body.transform.position.x = cell->anchor_position.x;
      v41 = v13;
      slot_cursor->ring.body.transform.position.y = v32;
      slot_cursor->ring.body.transform.position.z = v41;
      v14 = random_float_below(1.0, aRr2);
      slot_cursor->ring.body.transform.position.x = (v14 - 0.5 + v14 - 0.5) * 3.0;
      v15 = random_float_below(1.0, aRr3);
      goto LABEL_15;
    case 2:
      v33 = cell->anchor_position.y + 3.5;
      v16 = cell->anchor_position.z + 17.0;
      slot_cursor->ring.body.transform.position.x = cell->anchor_position.x;
      v42 = v16;
      slot_cursor->ring.body.transform.position.y = v33;
      slot_cursor->ring.body.transform.position.z = v42;
      v17 = random_float_below(1.0, aRr4);
      slot_cursor->ring.body.transform.position.x = (v17 - 0.5 + v17 - 0.5) * 3.0;
      v12 = random_float_below(1.0, aRr5);
      goto LABEL_17;
    case 3:
      v34 = cell->anchor_position.y + 2.5;
      v18 = cell->anchor_position.z + 6.0;
      slot_cursor->ring.body.transform.position.x = cell->anchor_position.x;
      v43 = v18;
      slot_cursor->ring.body.transform.position.y = v34;
      slot_cursor->ring.body.transform.position.z = v43;
      v19 = random_float_below(1.0, aRr6);
      slot_cursor->ring.body.transform.position.x = (v19 - 0.5 + v19 - 0.5) * 3.0;
      v15 = random_float_below(1.0, aRr7);
LABEL_15:
      slot_cursor->ring.active_phase = v15 * 6.2831855;
      slot_cursor->ring.active_phase_step = default_phase_step;
      break;
    case 4:
      v35 = cell->anchor_position.y + 2.5;
      v20 = cell->anchor_position.z + 6.0;
      slot_cursor->ring.body.transform.position.x = cell->anchor_position.x;
      v44 = v20;
      slot_cursor->ring.body.transform.position.y = v35;
      slot_cursor->ring.body.transform.position.z = v44;
      v21 = random_float_below(1.0, aRr8);
      slot_cursor->ring.body.transform.position.x = (v21 - 0.5 + v21 - 0.5) * 3.0;
      v12 = random_float_below(1.0, aRr9);
LABEL_17:
      slot_cursor->ring.active_phase = v12 * 6.2831855;
      slot_cursor->ring.active_phase_step = default_phase_step;
      break;
    case 5:
      z = cell->anchor_position.z;
      v36 = cell->anchor_position.y + 2.5;
      slot_cursor->ring.body.transform.position.x = cell->anchor_position.x;
      slot_cursor->ring.body.transform.position.y = v36;
      slot_cursor->ring.body.transform.position.z = z;
      v22 = random_float_below(1.0, aRr10);
      goto LABEL_22;
    case 6:
      v47 = cell->anchor_position.z;
      v38 = cell->anchor_position.y + 2.5;
      slot_cursor->ring.body.transform.position.x = cell->anchor_position.x;
      slot_cursor->ring.body.transform.position.y = v38;
      slot_cursor->ring.body.transform.position.z = v47;
      v22 = random_float_below(1.0, aRr12);
      goto LABEL_22;
    case 7:
      v24 = cell->anchor_position.y + 2.5;
      v48 = cell->anchor_position.z;
      slot_cursor->ring.body.transform.position.x = cell->anchor_position.x;
      v39 = v24;
      slot_cursor->ring.body.transform.position.y = v39;
      slot_cursor->ring.body.transform.position.z = v48;
      v22 = random_float_below(1.0, aRr13);
      goto LABEL_22;
    case 8:
      v23 = cell->anchor_position.y + 2.5;
      v46 = cell->anchor_position.z;
      slot_cursor->ring.body.transform.position.x = cell->anchor_position.x;
      v37 = v23;
      slot_cursor->ring.body.transform.position.y = v37;
      slot_cursor->ring.body.transform.position.z = v46;
      v22 = random_float_below(1.0, aRr11);
LABEL_22:
      slot_cursor->ring.active_phase = v22 * 6.2831855;
      slot_cursor->ring.active_phase_step = 1.0 / (ring_speed * 60.0) * game->subgame_rate * 6.2831855;
      break;
    default:
      break;
  }
  if ( get_track_grid_cell_at_world_position(game, &slot_cursor->ring.body.transform.position)->tile_id != SUBLOC_TILE_WALL2 )
  {
    slot_cursor->ring.kind = effective_kind;
    slot_cursor->ring.owner_lives_snapshot = player->lives;
    slot_cursor->ring.state = SUB_RING_STATE_ACTIVE;
    if ( random_float_below(1.0, aRt1) > 0.5 )
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
      if ( active_first != nullptr )
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
