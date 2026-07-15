/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_subgame @ 0x438b90 */
/* selector: update_subgame */

// Runs the main gameplay subgame state machine, including the continuation-controlled galaxy or challenge-setup handoff, replay-backed level start or restart, pause and quit flow, HUD timing, camera updates, active gameplay tick, and forward runtime-row scan for pickups plus authored or ambient garbage/salt hazards. Generated garbage/salt spawns are suppressed while the live `Player::click_start.state` lane at +0x120 equals 2. Cross-port Android and iOS symbols match this helper to `cRSubGame::AI()`.
void __thiscall update_subgame(SubgameRuntime *game)
{
  int32_t subgame_rebuild_selector; // eax
  SubSolution *selected_level_record; // eax
  int32_t level_mode; // eax
  int updated; // eax
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
  char *v17; // edi
  FrameBodBase *v18; // ecx
  FrameBodBase **p_first; // eax
  FrameBodBase *first; // edx
  FrameBodBase *list_prev; // edx
  uint32_t list_flags; // eax
  char *v23; // edi
  char v24; // al
  struct BodNode *v25; // eax
  int v26; // ecx
  struct BodNode *v27; // eax
  int v28; // ecx
  struct BodNode *v29; // eax
  struct BodNode *list_next; // ecx
  uint32_t v31; // ecx
  _DWORD *v32; // ebx
  struct BodNode **v33; // ebx
  struct BodNode *v34; // eax
  struct BodNode *v35; // ecx
  uint32_t v36; // ecx
  char v37; // al
  char v38; // al
  char v39; // al
  char v40; // al
  int v41; // edx
  char v42; // cl
  float v43; // edx
  char v44; // al
  int32_t v45; // eax
  char *v46; // eax
  char *v47; // eax
  char *v48; // eax
  int32_t total_score; // eax
  FrontendWidget *bottom_score_widget; // ecx
  tColour *v51; // [esp-1Ch] [ebp-68h]
  tColour *v52; // [esp-1Ch] [ebp-68h]
  int v53; // [esp+10h] [ebp-3Ch]
  int v54; // [esp+14h] [ebp-38h]
  char *v55; // [esp+18h] [ebp-34h]
  Color4f color; // [esp+1Ch] [ebp-30h] BYREF
  Color4f v57; // [esp+2Ch] [ebp-20h] BYREF
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
          updated = update_galaxy((FrontendWidget ***)&game->galaxy);
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
          updated = update_galaxy((FrontendWidget ***)&game->galaxy);
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
          v51 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 0.40000001);
          queue_axis_aligned_textured_quad_uv(27, 580.0, 6.0, 64.0, 64.0, 0x1000000u, v51, 0.0, 0.0, 1.0, 1.0, 1, 0.0);
        }
        else
        {
          v52 = set_color_rgba((tColour *)&v57, 1.0, 1.0, 1.0, 0.40000001);
          queue_axis_aligned_textured_quad_uv(27, 288.0, 10.0, 64.0, 64.0, 0x1000000u, v52, 0.0, 0.0, 1.0, 1.0, 1, 0.0);
        }
      }
      if ( !game->player.completion_handoff_active
        && game->player.click_start.state != CLICK_START_STATE_WAITING_FOR_START )
      {
        advance_timer_counters(&game->player.stopwatch, 1.0);
      }
      if ( game->level_mode == 7 )
        update_tutorial(&game->tutorial);
      update_slug_voice_manager((float *)&game->slug_voice_manager.active);
      if ( game->resume_requested == 1 )
      {
        game->subgame_pause_gate = 0;
        game->resume_requested = 0;
        set_sprite_manager_paused(g_sprite_manager, 0);
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
        set_sprite_manager_paused(g_sprite_manager, 1);
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
        v17 = (char *)game + 244 * runtime_row_scan_begin;
        v55 = v17;
        if ( (byte_5CCAC8[(_DWORD)v17] & 2) != 0 )
        {
          v18 = (FrameBodBase *)((char *)&unk_5CCACC + (_DWORD)v17);
          if ( (*(_DWORD *)((_BYTE *)&unk_5CCAD0 + (_DWORD)v17) & 0x200) != 0 )
          {
            report_errorf(aListAdd);
          }
          else
          {
            p_first = &g_game_base->active_bod_list.first;
            first = g_game_base->active_bod_list.first;
            if ( first )
            {
              first->bod.list_prev = v18;
              (*p_first)->bod.list_prev->bod.list_next = *p_first;
              list_prev = (*p_first)->bod.list_prev;
              *p_first = list_prev;
              list_prev->bod.list_prev = nullptr;
            }
            else
            {
              *p_first = v18;
              v18->bod.list_prev = nullptr;
              (*p_first)->bod.list_next = nullptr;
            }
            list_flags = v18->bod.list_flags;
            BYTE1(list_flags) |= 2u;
            v18->bod.list_flags = list_flags;
          }
        }
        if ( (byte_5CCAC8[(_DWORD)v17] & 0x10) != 0 && ((unsigned int)&unk_800000 & game->runtime_flags) != 0 )
          spawn_track_parcel(game, (Vec3 *)((char *)&unk_5CCB58 + (_DWORD)v17), &game->player);
        v53 = 0;
        while ( 1 )
        {
          if ( runtime_row_scan_begin < 0 )
            goto LABEL_209;
          if ( runtime_row_scan_begin >= game->runtime_row_count )
            goto LABEL_209;
          v23 = (char *)game + 672 * runtime_row_scan_begin + 84 * v53;
          if ( (*((_DWORD *)v23 + 982707) & 0x200) != 0 )
            goto LABEL_209;
          if ( (*((_DWORD *)v23 + 982722) & 0x4000) != 0 )
          {
            v24 = v23[3930884];
            if ( v24 == 29 || v24 == 30 )
            {
              if ( *((_DWORD *)v23 + 982715) )
              {
                v27 = (struct BodNode *)(v23 + 3930824);
                if ( (*((_DWORD *)v23 + 982707) & 0x200) != 0 )
                {
                  report_errorf(aListAddafter);
                }
                else
                {
                  *((_DWORD *)v23 + 982708) = &game->special_track_cell_list_head;
                  *((_DWORD *)v23 + 982709) = game->special_track_cell_list_head.bod.list_next;
                  game->special_track_cell_list_head.bod.list_next = v27;
                  v28 = *((_DWORD *)v23 + 982709);
                  if ( v28 )
                    *(_DWORD *)(v28 + 8) = v27;
                  *((_DWORD *)v23 + 982707) |= 0x200u;
                }
                v29 = (struct BodNode *)((char *)&unk_5CCB78 + (_DWORD)v55);
                *((float *)v23 + 982714) = (double)(runtime_row_scan_begin & 7) * 0.125;
                if ( (*(_DWORD *)((_BYTE *)&unk_5CCB78 + (_DWORD)v55 + 4) & 0x200) != 0 )
                {
                  report_errorf(aListAddafter);
                }
                else
                {
                  v29->list_prev = &game->fringe_attachment_list_head.bod;
                  v29->list_next = game->fringe_attachment_list_head.bod.list_next;
                  game->fringe_attachment_list_head.bod.list_next = v29;
                  list_next = v29->list_next;
                  if ( list_next )
                    list_next->list_prev = v29;
                  v31 = v29->list_flags;
                  BYTE1(v31) |= 2u;
                  v29->list_flags = v31;
                }
                v32 = (_DWORD *)((char *)&unk_5CCB88 + (_DWORD)v55);
                *v32 = *((_DWORD *)v23 + 982710);
                v32[1] = *((_DWORD *)v23 + 982711);
                v32[2] = *((_DWORD *)v23 + 982712);
              }
            }
            else
            {
              v25 = (struct BodNode *)(v23 + 3930824);
              if ( (*((_DWORD *)v23 + 982707) & 0x200) != 0 )
              {
                report_errorf(aListAddafter);
              }
              else
              {
                *((_DWORD *)v23 + 982708) = &game->track_body_list_head;
                *((_DWORD *)v23 + 982709) = game->track_body_list_head.bod.list_next;
                game->track_body_list_head.bod.list_next = v25;
                v26 = *((_DWORD *)v23 + 982709);
                if ( v26 )
                  *(_DWORD *)(v26 + 8) = v25;
                *((_DWORD *)v23 + 982707) |= 0x200u;
              }
            }
            (**((void (__thiscall ***)(int))v23 + 982706))((int)(v23 + 3930824));
          }
          v33 = (struct BodNode **)(v23 + 3930892);
          v54 = 4;
          do
          {
            v34 = *v33;
            if ( *v33 )
            {
              if ( (v34->list_flags & 0x200) != 0 )
              {
                report_errorf(aListAddafter);
              }
              else
              {
                v34->list_prev = &game->fringe_attachment_list_head.bod;
                v34->list_next = game->fringe_attachment_list_head.bod.list_next;
                game->fringe_attachment_list_head.bod.list_next = v34;
                v35 = v34->list_next;
                if ( v35 )
                  v35->list_prev = v34;
                v36 = v34->list_flags;
                BYTE1(v36) |= 2u;
                v34->list_flags = v36;
              }
              *(struct BodNode *)((char *)*v33 + 40) = *(struct BodNode *)get_track_skirt_color(
                                                                            &g_game_base->subgame,
                                                                            &out);
            }
            ++v33;
            --v54;
          }
          while ( v54 );
          if ( v23[3930884] == 23
            && (game->runtime_flags & 0x800) != 0
            && runtime_row_scan_begin >= game->first_block_row_count
            && runtime_row_scan_begin < game->completion_row_start )
          {
            spawn_track_health_pickup(game, (TrackRowCell *)(v23 + 3930824), &game->player);
          }
          if ( v23[3930884] == 24
            && runtime_row_scan_begin >= game->first_block_row_count
            && runtime_row_scan_begin < game->completion_row_start )
          {
            spawn_track_speedup((int)(v23 + 3930824), (int)&game->player);
          }
          if ( v23[3930884] == 25
            && runtime_row_scan_begin >= game->first_block_row_count
            && runtime_row_scan_begin < game->completion_row_start )
          {
            spawn_track_jetpack_pickup(game, (TrackRowCell *)(v23 + 3930824), &game->player);
          }
          v37 = v23[3930884];
          if ( v37 == 33
            || (v23[3930888] & 0x10) == 0
            && (v37 == 1 || v37 == 21)
            && (game->runtime_flags & 2) != 0
            && (1.0 - game->garbage_frequency) * 0.2 + 0.80000001 < random_float_below(1.0)
            && (!v53 || (v38 = v23[3930800], v38 == 1) || v38 == 20 || v38 == 21 || v38 == 32)
            && (v53 == 7 || (v39 = v23[3930968], v39 == 1) || v39 == 20 || v39 == 21 || v39 == 32)
            && runtime_row_scan_begin >= game->first_block_row_count
            && runtime_row_scan_begin < game->completion_row_start
            && game->player.click_start.state != CLICK_START_STATE_WAITING_FOR_START
            && (game->level_mode != 4 || game->base_subgame_rate * 0.30000001 + 0.69999999 >= random_float_below(1.0))
            && (game->level_mode || game->base_subgame_rate * 0.60000002 + 0.40000001 >= random_float_below(1.0)) )
          {
            spawn_track_garbage_hazard(game, (TrackRowCell *)(v23 + 3930824), &game->player);
          }
          v40 = v23[3930884];
          if ( v40 == 34 )
          {
            if ( runtime_row_scan_begin >= game->first_block_row_count
              && runtime_row_scan_begin < game->completion_row_start )
            {
              goto LABEL_158;
            }
          }
          else if ( (v23[3930888] & 8) == 0
                 && (v40 == 1 || v40 == 15)
                 && game->player.click_start.state != CLICK_START_STATE_WAITING_FOR_START
                 && (game->runtime_flags & 0x10000) != 0
                 && (1.0 - game->salt_frequency) * 0.02 + 0.98000002 < random_float_below(1.0)
                 && runtime_row_scan_begin >= game->first_block_row_count
                 && runtime_row_scan_begin < game->completion_row_start )
          {
LABEL_158:
            spawn_salt_hazard(&game->salt_hazards, (const Vec3 *)v23 + 327570);
          }
          if ( SLOBYTE(game->runtime_flags) < 0
            && v23[3930884] == 18
            && runtime_row_scan_begin >= game->first_block_row_count
            && runtime_row_scan_begin < game->completion_row_start )
          {
            spawn_slug_hazard((int)game, (int)(v23 + 3930824), (int)&game->player);
          }
          v41 = *(_DWORD *)&byte_5CCAC8[(_DWORD)v55];
          if ( (v41 & 0x200) != 0 )
            goto LABEL_209;
          v42 = v23[3930884];
          if ( v42 == 35 )
          {
            if ( (v41 & 0x400) != 0 )
            {
              spawn_track_ring_or_special_effect(
                game,
                (TrackRowCell *)(v23 + 3930824),
                5,
                &game->player,
                *(&game->runtime_rows[0].ring_speed + 60 * runtime_row_scan_begin + runtime_row_scan_begin));
              goto LABEL_207;
            }
            if ( (v41 & 0x2000) != 0 )
            {
              spawn_track_ring_or_special_effect(
                game,
                (TrackRowCell *)(v23 + 3930824),
                8,
                &game->player,
                *(&game->runtime_rows[0].ring_speed + 60 * runtime_row_scan_begin + runtime_row_scan_begin));
              goto LABEL_207;
            }
            if ( (v41 & 0x800) != 0 )
            {
              spawn_track_ring_or_special_effect(
                game,
                (TrackRowCell *)(v23 + 3930824),
                6,
                &game->player,
                *(&game->runtime_rows[0].ring_speed + 60 * runtime_row_scan_begin + runtime_row_scan_begin));
              goto LABEL_207;
            }
            if ( (v41 & 0x1000) != 0 )
            {
              spawn_track_ring_or_special_effect(
                game,
                (TrackRowCell *)(v23 + 3930824),
                7,
                &game->player,
                *(&game->runtime_rows[0].ring_speed + 60 * runtime_row_scan_begin + runtime_row_scan_begin));
              goto LABEL_207;
            }
          }
          else
          {
            if ( v42 != 2 && v42 != 3 && v42 != 4 && v42 != 5 && v42 != 6 && v42 != 7
              || game->player.last_ring_spawn_z + 10.0 >= *((float *)v23 + 982712)
              || runtime_row_scan_begin >= game->completion_row_start )
            {
              if ( v42 != 8 && v42 != 9 && v42 != 10
                || game->player.last_ring_spawn_z + 10.0 >= *((float *)v23 + 982712)
                || runtime_row_scan_begin >= game->completion_row_start )
              {
                goto LABEL_209;
              }
              if ( (v41 & 0x800) != 0 )
              {
                spawn_track_ring_or_special_effect(
                  game,
                  (TrackRowCell *)(v23 + 3930824),
                  2,
                  &game->player,
                  *(&game->runtime_rows[0].ring_speed + 60 * runtime_row_scan_begin + runtime_row_scan_begin));
              }
              else
              {
                if ( random_float_below(1.0) <= 0.69999999
                  && game->level_mode != 7
                  && (*(_DWORD *)&byte_5CCAC8[(_DWORD)v55] & 0x800) == 0 )
                {
                  goto LABEL_209;
                }
                spawn_track_ring_or_special_effect(game, (TrackRowCell *)(v23 + 3930824), 2, &game->player, 0.0);
              }
LABEL_207:
              v43 = *((float *)v23 + 982712);
LABEL_208:
              game->player.last_ring_spawn_z = v43;
              goto LABEL_209;
            }
            if ( (v41 & 0x2000) != 0 )
            {
              spawn_track_ring_or_special_effect(
                game,
                (TrackRowCell *)(v23 + 3934856),
                8,
                &game->player,
                *(&game->runtime_rows[0].ring_speed + 60 * runtime_row_scan_begin + runtime_row_scan_begin));
              v43 = *((float *)v23 + 983720);
              goto LABEL_208;
            }
            if ( (v41 & 0x800) != 0 )
            {
              spawn_track_ring_or_special_effect(
                game,
                (TrackRowCell *)(v23 + 3934856),
                6,
                &game->player,
                *(&game->runtime_rows[0].ring_speed + 60 * runtime_row_scan_begin + runtime_row_scan_begin));
              v43 = *((float *)v23 + 983720);
              goto LABEL_208;
            }
            if ( (v41 & 0x1000) != 0 )
            {
              spawn_track_ring_or_special_effect(
                game,
                (TrackRowCell *)(v23 + 3934856),
                7,
                &game->player,
                *(&game->runtime_rows[0].ring_speed + 60 * runtime_row_scan_begin + runtime_row_scan_begin));
              v43 = *((float *)v23 + 983720);
              goto LABEL_208;
            }
            if ( (game->runtime_flags & 8) == 0 || random_float_below(1.0) <= 0.69999999 && game->level_mode != 7 )
              goto LABEL_209;
            v44 = v23[3930884];
            if ( v44 == 5 || v44 == 6 || v44 == 7 )
              goto LABEL_209;
            spawn_track_ring_or_special_effect(game, (TrackRowCell *)(v23 + 3930824), 4, &game->player, 0.0);
            if ( game->player.lives < 10 )
              goto LABEL_207;
            game->player.last_ring_spawn_z = *((float *)v23 + 982712) + 35.0;
          }
LABEL_209:
          if ( ++v53 >= 8 )
          {
            v45 = game->runtime_row_scan_end;
            ++runtime_row_scan_begin;
            game->scan_reset = 0;
            if ( runtime_row_scan_begin >= v45 )
              break;
            goto LABEL_65;
          }
        }
      }
      update_track_render_cache_rows(&game->segment_cache);
      if ( game->level_mode == 4 )
      {
        v46 = format_time_trial_string(&game->time_trial, &game->player.stopwatch);
        rstrcpy_checked_ascii((char *)&game->top_score_widget->text_buffer, v46);
        v47 = (char *)game + 129728 * game->level_mode_arg;
        if ( *((_DWORD *)v47 + 2429012) == 1 )
        {
          v48 = format_time_trial_string(&game->time_trial, (Time *)(v47 + 9716056));
          rstrcpy_checked_ascii((char *)&game->bottom_score_widget->text_buffer, v48);
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
