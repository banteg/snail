/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_subgame @ 0x438b90 */
/* selector: update_subgame */

// Runs the main gameplay subgame state machine, including the continuation-controlled galaxy or challenge-setup handoff, replay-backed level start or restart, pause and quit flow, HUD timing, camera updates, active gameplay tick, and forward runtime-row scan for pickups plus authored or ambient garbage/salt hazards. Generated garbage/salt spawns are suppressed while the live `Player::click_start.state` lane at +0x120 equals 2. Cross-port Android and iOS symbols match this helper to `cRSubGame::AI()`.
void __thiscall update_subgame(SubgameRuntime *game)
{
  int32_t subgame_rebuild_selector; // eax
  SubSolution *selected_level_record; // eax
  int32_t level_mode; // eax
  int32_t updated; // eax
  int32_t level_mode_arg; // eax
  int32_t v7; // edx
  int32_t v8; // edx
  int v9; // eax
  double v10; // st7
  int32_t v11; // eax
  int32_t v12; // eax
  int32_t v13; // eax
  int32_t runtime_row_scan_end; // edi
  int32_t v15; // eax
  int32_t runtime_row_scan_begin; // ebp
  RuntimeRowStrideAnchor *runtime_row_anchor; // edi
  RowModel *p_row_model; // ecx
  BodNode **p_first; // eax
  BodNode *first; // edx
  struct BodNode *list_prev; // edx
  uint32_t list_flags; // eax
  RuntimeCellStrideAnchor *runtime_cell_anchor; // edi
  uint8_t tile_id; // al
  TrackRowCell *v25; // eax
  struct BodNode *v26; // ecx
  TrackRowCell *p_cell; // eax
  struct BodNode *list_next; // ecx
  BodBase *p_attachment_body; // eax
  struct BodNode *v30; // ecx
  uint32_t v31; // ecx
  Fringe **p_fringe_front; // ebx
  struct BodNode *v33; // eax
  struct BodNode *v34; // ecx
  uint32_t v35; // ecx
  uint8_t v36; // al
  uint8_t v37; // al
  uint8_t v38; // al
  uint8_t v39; // al
  uint32_t flags; // edx
  uint8_t v41; // cl
  float z; // edx
  uint8_t v43; // al
  int32_t v44; // eax
  char *v45; // eax
  TimeTrialRouteRecordCursor *time_trial_route_cursor; // eax
  char *v47; // eax
  int32_t total_score; // eax
  FrontendWidget *bottom_score_widget; // ecx
  tColour *v50; // [esp-1Ch] [ebp-68h]
  tColour *v51; // [esp-1Ch] [ebp-68h]
  int v52; // [esp+10h] [ebp-3Ch]
  int v53; // [esp+14h] [ebp-38h]
  RuntimeRowStrideAnchor *runtime_row_anchor_saved; // [esp+18h] [ebp-34h]
  Color4f color; // [esp+1Ch] [ebp-30h] BYREF
  Color4f v56; // [esp+2Ch] [ebp-20h] BYREF
  tColour out; // [esp+3Ch] [ebp-10h] BYREF

  calc_subgame_rate(game);
  switch ( game->subgame_state )
  {
    case 0:
      subgame_rebuild_selector = game->subgame_rebuild_selector;
      game->subgame_state = 1;
      if ( subgame_rebuild_selector == 1 )
        goto LABEL_214;
      if ( !subgame_rebuild_selector || subgame_rebuild_selector == 3 )
      {
LABEL_21:
        build_subgame_level(game, game->level_mode_arg);
      }
      else
      {
        if ( game->selected_level_record_persistent != 1 )
        {
          game->selected_level_record_active = 0;
          hide_star_field(&g_game_base->star_manager);
          goto LABEL_14;
        }
        selected_level_record = game->selected_level_record;
        game->selected_level_record_active = 1;
        build_subgame_level(game, selected_level_record->replay_level_index);
      }
      return;
    case 1:
LABEL_14:
      random_float_below(1.0);
      level_mode = game->level_mode;
      game->completion_bonus_x_source = g_runtime_config.completion_bonus_x_source;
      game->completion_bonus_y_source = g_runtime_config.completion_bonus_y_source;
      switch ( level_mode )
      {
        case 0:
          updated = update_galaxy(&game->galaxy);
          if ( updated == 1 )
          {
            level_mode_arg = game->level_mode_arg;
            game->subgame_rebuild_selector = 3;
            g_runtime_config.landscape_backdrop_variant_selector = level_mode_arg;
            build_subgame_level(game, game->level_mode_arg);
            return;
          }
          if ( updated == 2 )
          {
            v7 = game->level_mode_arg;
            game->subgame_rebuild_selector = 1;
            g_runtime_config.landscape_backdrop_variant_selector = v7;
            build_subgame_level(game, game->level_mode_arg);
            return;
          }
LABEL_22:
          if ( updated != 3 )
            goto LABEL_214;
LABEL_23:
          destroy_subgame(game);
          g_game_base->players[0].frontend_state = 2;
          break;
        case 1:
          v9 = update_challenge_setup_screen(&game->gui);
          if ( v9 == 1 )
            goto LABEL_25;
          if ( v9 == 3 )
            goto LABEL_23;
          goto LABEL_214;
        case 4:
          updated = update_galaxy(&game->galaxy);
          if ( updated != 1 )
            goto LABEL_22;
          v8 = game->level_mode_arg;
          game->subgame_rebuild_selector = 2;
          g_runtime_config.landscape_backdrop_variant_selector = v8;
          goto LABEL_21;
        case 7:
LABEL_25:
          game->subgame_rebuild_selector = 2;
          build_subgame_level(game, 0);
          return;
        default:
          goto LABEL_214;
      }
      return;
    case 2:
      if ( game->selected_level_record_active == 1 && !g_game_base->intro.hide_for_replay_latch )
      {
        if ( game->level_mode == 3 )
        {
          v50 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 0.40000001);
          queue_axis_aligned_textured_quad_uv(27, 580.0, 6.0, 64.0, 64.0, 0x1000000u, v50, 0.0, 0.0, 1.0, 1.0, 1, 0.0);
        }
        else
        {
          v51 = set_color_rgba((tColour *)&v56, 1.0, 1.0, 1.0, 0.40000001);
          queue_axis_aligned_textured_quad_uv(27, 288.0, 10.0, 64.0, 64.0, 0x1000000u, v51, 0.0, 0.0, 1.0, 1.0, 1, 0.0);
        }
      }
      if ( !game->player.completion_handoff_active
        && game->player.click_start.state != CLICK_START_STATE_WAITING_FOR_START )
      {
        advance_timer_counters(&game->player.stopwatch, 1.0);
      }
      if ( game->level_mode == 7 )
        update_tutorial(&game->tutorial);
      update_slug_voice_manager(&game->slug_voice_manager);
      if ( game->resume_requested == 1 )
      {
        game->subgame_pause_gate = 0;
        game->resume_requested = 0;
        set_sprite_manager_paused(&g_sprite_manager, 0);
      }
      if ( game->selected_level_record_active
        && game->pause_fade == 0.0
        && (game->player.control_source->control_flags_a & 0x4000) != 0
        || g_game_base->intro.hide_for_replay_latch )
      {
        if ( game->selected_level_record_persistent )
        {
          g_game_base->players[0].saved_frontend_state = g_game_base->players[0].frontend_state;
          g_game_base->players[0].frontend_state = 26;
        }
        else
        {
          g_game_base->players[0].saved_frontend_state = g_game_base->players[0].frontend_state;
          g_game_base->players[0].frontend_state = 27;
        }
        if ( g_game_base->intro.attract_reset_progress <= 1.0 )
          g_game_base->intro.hide_for_replay_latch = 0;
        return;
      }
      if ( (read_pressed_text_input_key_code() == 11 || g_window_deactivated == 1) && !g_game_base->fade.state )
      {
        game->subgame_pause_gate = 1;
        game->subgame_state = 3;
        set_sprite_manager_paused(&g_sprite_manager, 1u);
        if ( game->player.click_start.state == CLICK_START_STATE_WAITING_FOR_START )
          hide_border_init(game->player.click_start.prompt);
        return;
      }
      if ( game->pause_fade > 0.0 )
      {
        v10 = game->pause_fade_step + game->pause_fade;
        game->pause_fade = v10;
        if ( v10 > 1.0 )
          game->pause_fade = 0.0;
        if ( game->player.click_start.state == CLICK_START_STATE_WAITING_FOR_START )
          unhide_border_init(game->player.click_start.prompt);
      }
      if ( game->scan_reset )
      {
        v11 = game->level_mode;
        game->runtime_row_scan_begin = 0;
        if ( v11 == 2 )
        {
          game->runtime_row_scan_end = game->runtime_row_count;
          goto LABEL_62;
        }
        v12 = (__int64)game->player.interaction_max_z + 46;
LABEL_61:
        game->runtime_row_scan_end = v12;
        goto LABEL_62;
      }
      v13 = game->level_mode;
      runtime_row_scan_end = game->runtime_row_scan_end;
      game->runtime_row_scan_begin = runtime_row_scan_end;
      if ( v13 == 2 )
      {
        game->runtime_row_scan_end = game->runtime_row_count;
        goto LABEL_62;
      }
      v12 = (__int64)game->player.interaction_max_z + 46;
      if ( v12 > runtime_row_scan_end )
        goto LABEL_61;
LABEL_62:
      v15 = game->completion_row_start + 20;
      if ( game->runtime_row_scan_end > v15 )
        game->runtime_row_scan_end = v15;
      runtime_row_scan_begin = game->runtime_row_scan_begin;
      if ( runtime_row_scan_begin < game->runtime_row_scan_end )
      {
LABEL_65:
        runtime_row_anchor = (RuntimeRowStrideAnchor *)((char *)game + 244 * runtime_row_scan_begin);
        runtime_row_anchor_saved = runtime_row_anchor;
        if ( (runtime_row_anchor->row.flags & 2) != 0 )
        {
          p_row_model = &runtime_row_anchor->row.row_model;
          if ( (runtime_row_anchor->row.row_model.body.bod.bod.list_flags & 0x200) != 0 )
          {
            report_errorf(aListAdd);
          }
          else
          {
            p_first = &g_game_base->active_bod_list.first;
            first = g_game_base->active_bod_list.first;
            if ( first )
            {
              first->list_prev = &p_row_model->body.bod.bod;
              (*p_first)->list_prev->list_next = *p_first;
              list_prev = (*p_first)->list_prev;
              *p_first = list_prev;
              list_prev->list_prev = nullptr;
            }
            else
            {
              *p_first = &p_row_model->body.bod.bod;
              runtime_row_anchor->row.row_model.body.bod.bod.list_prev = nullptr;
              (*p_first)->list_next = nullptr;
            }
            list_flags = runtime_row_anchor->row.row_model.body.bod.bod.list_flags;
            BYTE1(list_flags) |= 2u;
            runtime_row_anchor->row.row_model.body.bod.bod.list_flags = list_flags;
          }
        }
        if ( (runtime_row_anchor->row.flags & 0x10) != 0 && (game->runtime_flags & 0x800000) != 0 )
          spawn_track_parcel(game, &runtime_row_anchor->row.projection_payload, &game->player);
        v52 = 0;
        while ( 1 )
        {
          if ( runtime_row_scan_begin < 0 )
            goto LABEL_209;
          if ( runtime_row_scan_begin >= game->runtime_row_count )
            goto LABEL_209;
          runtime_cell_anchor = (RuntimeCellStrideAnchor *)((char *)game + 672 * runtime_row_scan_begin + 84 * v52);
          if ( (runtime_cell_anchor->cell.bod.list_flags & 0x200) != 0 )
            goto LABEL_209;
          if ( (runtime_cell_anchor->cell.lane_and_flags & 0x4000) != 0 )
          {
            tile_id = runtime_cell_anchor->cell.tile_id;
            if ( tile_id == 29 || tile_id == 30 )
            {
              if ( runtime_cell_anchor->cell.object )
              {
                p_cell = &runtime_cell_anchor->cell;
                if ( (runtime_cell_anchor->cell.bod.list_flags & 0x200) != 0 )
                {
                  report_errorf(aListAddafter);
                }
                else
                {
                  runtime_cell_anchor->cell.bod.list_prev = &game->special_track_cell_list_head.bod;
                  runtime_cell_anchor->cell.bod.list_next = game->special_track_cell_list_head.bod.list_next;
                  game->special_track_cell_list_head.bod.list_next = &p_cell->bod;
                  list_next = runtime_cell_anchor->cell.bod.list_next;
                  if ( list_next )
                    list_next->list_prev = &p_cell->bod;
                  runtime_cell_anchor->cell.bod.list_flags |= 0x200u;
                }
                p_attachment_body = &runtime_row_anchor_saved->row.attachment_body;
                runtime_cell_anchor->cell.render_arg_20 = (double)(runtime_row_scan_begin & 7) * 0.125;
                if ( (runtime_row_anchor_saved->row.attachment_body.bod.list_flags & 0x200) != 0 )
                {
                  report_errorf(aListAddafter);
                }
                else
                {
                  runtime_row_anchor_saved->row.attachment_body.bod.list_prev = &game->fringe_attachment_list_head.bod;
                  runtime_row_anchor_saved->row.attachment_body.bod.list_next = game->fringe_attachment_list_head.bod.list_next;
                  game->fringe_attachment_list_head.bod.list_next = &p_attachment_body->bod;
                  v30 = runtime_row_anchor_saved->row.attachment_body.bod.list_next;
                  if ( v30 )
                    v30->list_prev = &p_attachment_body->bod;
                  v31 = runtime_row_anchor_saved->row.attachment_body.bod.list_flags;
                  BYTE1(v31) |= 2u;
                  runtime_row_anchor_saved->row.attachment_body.bod.list_flags = v31;
                }
                runtime_row_anchor_saved->row.attachment_body.position = runtime_cell_anchor->cell.anchor_position;
              }
            }
            else
            {
              v25 = &runtime_cell_anchor->cell;
              if ( (runtime_cell_anchor->cell.bod.list_flags & 0x200) != 0 )
              {
                report_errorf(aListAddafter);
              }
              else
              {
                runtime_cell_anchor->cell.bod.list_prev = &game->track_body_list_head.bod;
                runtime_cell_anchor->cell.bod.list_next = game->track_body_list_head.bod.list_next;
                game->track_body_list_head.bod.list_next = &v25->bod;
                v26 = runtime_cell_anchor->cell.bod.list_next;
                if ( v26 )
                  v26->list_prev = &v25->bod;
                runtime_cell_anchor->cell.bod.list_flags |= 0x200u;
              }
            }
            (*(void (__thiscall **)(TrackRowCell *))runtime_cell_anchor->cell.bod.vtable)(&runtime_cell_anchor->cell);
          }
          p_fringe_front = &runtime_cell_anchor->cell.fringe_front;
          v53 = 4;
          do
          {
            v33 = (struct BodNode *)*p_fringe_front;
            if ( *p_fringe_front )
            {
              if ( (v33->list_flags & 0x200) != 0 )
              {
                report_errorf(aListAddafter);
              }
              else
              {
                v33->list_prev = &game->fringe_attachment_list_head.bod;
                v33->list_next = game->fringe_attachment_list_head.bod.list_next;
                game->fringe_attachment_list_head.bod.list_next = v33;
                v34 = v33->list_next;
                if ( v34 )
                  v34->list_prev = v33;
                v35 = v33->list_flags;
                BYTE1(v35) |= 2u;
                v33->list_flags = v35;
              }
              (*p_fringe_front)->bod.color = *get_track_skirt_color(&g_game_base->subgame, &out);
            }
            ++p_fringe_front;
            --v53;
          }
          while ( v53 );
          if ( runtime_cell_anchor->cell.tile_id == 23
            && (game->runtime_flags & 0x800) != 0
            && runtime_row_scan_begin >= game->first_block_row_count
            && runtime_row_scan_begin < game->completion_row_start )
          {
            spawn_track_health_pickup(game, &runtime_cell_anchor->cell, &game->player);
          }
          if ( runtime_cell_anchor->cell.tile_id == 24
            && runtime_row_scan_begin >= game->first_block_row_count
            && runtime_row_scan_begin < game->completion_row_start )
          {
            spawn_track_speedup((int)&runtime_cell_anchor->cell, (int)&game->player);
          }
          if ( runtime_cell_anchor->cell.tile_id == 25
            && runtime_row_scan_begin >= game->first_block_row_count
            && runtime_row_scan_begin < game->completion_row_start )
          {
            spawn_track_jetpack_pickup(game, &runtime_cell_anchor->cell, &game->player);
          }
          v36 = runtime_cell_anchor->cell.tile_id;
          if ( v36 == 33
            || (runtime_cell_anchor->cell.lane_and_flags & 0x10) == 0
            && (v36 == 1 || v36 == 21)
            && (game->runtime_flags & 2) != 0
            && (1.0 - game->garbage_frequency) * 0.2 + 0.80000001 < random_float_below(1.0)
            && (!v52
             || (v37 = runtime_cell_anchor->previous_lane_same_row.tile_id, v37 == 1)
             || v37 == 20
             || v37 == 21
             || v37 == 32)
            && (v52 == 7
             || (v38 = runtime_cell_anchor->next_lane_same_row.tile_id, v38 == 1)
             || v38 == 20
             || v38 == 21
             || v38 == 32)
            && runtime_row_scan_begin >= game->first_block_row_count
            && runtime_row_scan_begin < game->completion_row_start
            && game->player.click_start.state != CLICK_START_STATE_WAITING_FOR_START
            && (game->level_mode != 4 || game->base_subgame_rate * 0.30000001 + 0.69999999 >= random_float_below(1.0))
            && (game->level_mode || game->base_subgame_rate * 0.60000002 + 0.40000001 >= random_float_below(1.0)) )
          {
            spawn_track_garbage_hazard(game, &runtime_cell_anchor->cell, &game->player);
          }
          v39 = runtime_cell_anchor->cell.tile_id;
          if ( v39 == 34 )
          {
            if ( runtime_row_scan_begin >= game->first_block_row_count
              && runtime_row_scan_begin < game->completion_row_start )
            {
              goto LABEL_158;
            }
          }
          else if ( (runtime_cell_anchor->cell.lane_and_flags & 8) == 0
                 && (v39 == 1 || v39 == 15)
                 && game->player.click_start.state != CLICK_START_STATE_WAITING_FOR_START
                 && (game->runtime_flags & 0x10000) != 0
                 && (1.0 - game->salt_frequency) * 0.02 + 0.98000002 < random_float_below(1.0)
                 && runtime_row_scan_begin >= game->first_block_row_count
                 && runtime_row_scan_begin < game->completion_row_start )
          {
LABEL_158:
            spawn_salt_hazard(&game->salt_hazards, &runtime_cell_anchor->cell.anchor_position);
          }
          if ( SLOBYTE(game->runtime_flags) < 0
            && runtime_cell_anchor->cell.tile_id == 18
            && runtime_row_scan_begin >= game->first_block_row_count
            && runtime_row_scan_begin < game->completion_row_start )
          {
            spawn_slug_hazard(game, &runtime_cell_anchor->cell, &game->player);
          }
          flags = runtime_row_anchor_saved->row.flags;
          if ( (flags & 0x200) != 0 )
            goto LABEL_209;
          v41 = runtime_cell_anchor->cell.tile_id;
          if ( v41 == 35 )
          {
            if ( (flags & 0x400) != 0 )
            {
              spawn_track_ring_or_special_effect(
                game,
                &runtime_cell_anchor->cell,
                5,
                &game->player,
                *(&game->runtime_rows[0].ring_speed + 60 * runtime_row_scan_begin + runtime_row_scan_begin));
              goto LABEL_207;
            }
            if ( (flags & 0x2000) != 0 )
            {
              spawn_track_ring_or_special_effect(
                game,
                &runtime_cell_anchor->cell,
                8,
                &game->player,
                *(&game->runtime_rows[0].ring_speed + 60 * runtime_row_scan_begin + runtime_row_scan_begin));
              goto LABEL_207;
            }
            if ( (flags & 0x800) != 0 )
            {
              spawn_track_ring_or_special_effect(
                game,
                &runtime_cell_anchor->cell,
                6,
                &game->player,
                *(&game->runtime_rows[0].ring_speed + 60 * runtime_row_scan_begin + runtime_row_scan_begin));
              goto LABEL_207;
            }
            if ( (flags & 0x1000) != 0 )
            {
              spawn_track_ring_or_special_effect(
                game,
                &runtime_cell_anchor->cell,
                7,
                &game->player,
                *(&game->runtime_rows[0].ring_speed + 60 * runtime_row_scan_begin + runtime_row_scan_begin));
              goto LABEL_207;
            }
          }
          else
          {
            if ( v41 != 2 && v41 != 3 && v41 != 4 && v41 != 5 && v41 != 6 && v41 != 7
              || game->player.last_ring_spawn_z + 10.0 >= runtime_cell_anchor->cell.anchor_position.z
              || runtime_row_scan_begin >= game->completion_row_start )
            {
              if ( v41 != 8 && v41 != 9 && v41 != 10
                || game->player.last_ring_spawn_z + 10.0 >= runtime_cell_anchor->cell.anchor_position.z
                || runtime_row_scan_begin >= game->completion_row_start )
              {
                goto LABEL_209;
              }
              if ( (flags & 0x800) != 0 )
              {
                spawn_track_ring_or_special_effect(
                  game,
                  &runtime_cell_anchor->cell,
                  2,
                  &game->player,
                  *(&game->runtime_rows[0].ring_speed + 60 * runtime_row_scan_begin + runtime_row_scan_begin));
              }
              else
              {
                if ( random_float_below(1.0) <= 0.69999999
                  && game->level_mode != 7
                  && (runtime_row_anchor_saved->row.flags & 0x800) == 0 )
                {
                  goto LABEL_209;
                }
                spawn_track_ring_or_special_effect(game, &runtime_cell_anchor->cell, 2, &game->player, 0.0);
              }
LABEL_207:
              z = runtime_cell_anchor->cell.anchor_position.z;
LABEL_208:
              game->player.last_ring_spawn_z = z;
              goto LABEL_209;
            }
            if ( (flags & 0x2000) != 0 )
            {
              spawn_track_ring_or_special_effect(
                game,
                &runtime_cell_anchor->projected_row_six_ahead_same_lane,
                8,
                &game->player,
                *(&game->runtime_rows[0].ring_speed + 60 * runtime_row_scan_begin + runtime_row_scan_begin));
              z = runtime_cell_anchor->projected_row_six_ahead_same_lane.anchor_position.z;
              goto LABEL_208;
            }
            if ( (flags & 0x800) != 0 )
            {
              spawn_track_ring_or_special_effect(
                game,
                &runtime_cell_anchor->projected_row_six_ahead_same_lane,
                6,
                &game->player,
                *(&game->runtime_rows[0].ring_speed + 60 * runtime_row_scan_begin + runtime_row_scan_begin));
              z = runtime_cell_anchor->projected_row_six_ahead_same_lane.anchor_position.z;
              goto LABEL_208;
            }
            if ( (flags & 0x1000) != 0 )
            {
              spawn_track_ring_or_special_effect(
                game,
                &runtime_cell_anchor->projected_row_six_ahead_same_lane,
                7,
                &game->player,
                *(&game->runtime_rows[0].ring_speed + 60 * runtime_row_scan_begin + runtime_row_scan_begin));
              z = runtime_cell_anchor->projected_row_six_ahead_same_lane.anchor_position.z;
              goto LABEL_208;
            }
            if ( (game->runtime_flags & 8) == 0 || random_float_below(1.0) <= 0.69999999 && game->level_mode != 7 )
              goto LABEL_209;
            v43 = runtime_cell_anchor->cell.tile_id;
            if ( v43 == 5 || v43 == 6 || v43 == 7 )
              goto LABEL_209;
            spawn_track_ring_or_special_effect(game, &runtime_cell_anchor->cell, 4, &game->player, 0.0);
            if ( game->player.lives < 10 )
              goto LABEL_207;
            game->player.last_ring_spawn_z = runtime_cell_anchor->cell.anchor_position.z + 35.0;
          }
LABEL_209:
          if ( ++v52 >= 8 )
          {
            v44 = game->runtime_row_scan_end;
            ++runtime_row_scan_begin;
            game->scan_reset = 0;
            if ( runtime_row_scan_begin >= v44 )
              break;
            goto LABEL_65;
          }
        }
      }
      update_track_render_cache_rows(&game->segment_cache);
      if ( game->level_mode == 4 )
      {
        v45 = format_time_trial_string(&game->time_trial, &game->player.stopwatch);
        rstrcpy_checked_ascii((char *)&game->top_score_widget->text_buffer, v45);
        time_trial_route_cursor = (TimeTrialRouteRecordCursor *)((char *)game + 129728 * game->level_mode_arg);
        if ( time_trial_route_cursor->record.active == 1 )
        {
          v47 = format_time_trial_string(&game->time_trial, (Time *)&time_trial_route_cursor->record.score_or_time);
          rstrcpy_checked_ascii((char *)&game->bottom_score_widget->text_buffer, v47);
          goto LABEL_214;
        }
        hide_border_init(game->bottom_score_widget);
        update_subgame_camera(game);
      }
      else
      {
        game->top_score_widget->text_buffer.raw[0] = 0;
        border_add_text_number(game->top_score_widget, game->player.total_score);
        total_score = game->player.total_score;
        if ( total_score <= game->active_level_score )
          goto LABEL_214;
        bottom_score_widget = game->bottom_score_widget;
        game->active_level_score = total_score;
        bottom_score_widget->text_buffer.raw[0] = 0;
        border_add_text_number(game->bottom_score_widget, game->active_level_score);
        update_subgame_camera(game);
      }
      return;
    case 3:
      game->subgame_state = 4;
      game->subgame_pause_gate = 1;
      game->pause_fade = game->pause_fade_step;
      initialize_pause_menu(&game->sub_pause);
      goto LABEL_3;
    case 4:
LABEL_3:
      update_pause_menu(&game->sub_pause);
      return;
    case 7:
      game->selected_level_record_active = game->selected_level_record_persistent == 1;
      build_subgame_level(game, 0);
      game->subgame_state = 2;
      g_game_base->render_skip_count = 1;
      return;
    default:
LABEL_214:
      update_subgame_camera(game);
      return;
  }
}
