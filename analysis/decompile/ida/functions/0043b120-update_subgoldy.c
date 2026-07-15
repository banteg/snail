/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_subgoldy @ 0x43b120 */
/* selector: update_subgoldy */

// Main void per-frame player or Goldy actor step, installed as slot zero of `g_subgoldy_callback_table` and invoked through the shared void `BodAiDispatch` ABI. It updates attachment-follow state, samples current track cells, drives row events, dispatches pickups and completion handoff, emits movement flags and sounds, and advances the runtime track index. It contains four direct calls to `begin_post_follow_carryover`, plus the post-exit progress loop that advances `attachment_exit_progress` by `attachment_exit_progress_step` and trips the `gate_a` and `gate_b` thresholds. Windows `cdb` confirmed those carryover-arm lanes are real, but at least one clean level-complete path bypasses all four of them. Newer field-xref narrowing also shows later retirement of `attachment_exit_pending` happens only through five clear sites inside this function, not through the swept-entry helper or a standalone progress-expiry store; one of those clear sites, `0x43bcb3`, now resolves to the non-follow floor-cache/slide motion bran
void __thiscall update_subgoldy(Player *player)
{
  Path *template_record; // esi
  signed int v3; // eax
  signed int segment_count; // ecx
  int32_t movement_mode_selector; // eax
  SubgameRuntime *game; // eax
  SubgameRuntime *v7; // eax
  SubSolution *selected_level_record; // ecx
  int32_t replay_update_cursor; // eax
  Vec3 *p_position; // ebx
  SubgameRuntime *v11; // eax
  double v12; // st7
  double track_z_offset; // st7
  double v14; // st7
  char v16; // c0
  double v17; // st7
  __int16 v18; // ax
  SubgameRuntime *v19; // esi
  SubgameRuntime *v20; // esi
  double v21; // st7
  SubgameRuntime *v22; // eax
  PlayerControlSource *control_source; // eax
  SubgameRuntime *v24; // eax
  TrackRowCell *track_grid_cell_at_world_position; // eax
  SubgameRuntime *v26; // edi
  int v27; // eax
  char *v28; // esi
  int32_t v29; // eax
  int v30; // esi
  SubgameRuntime *v31; // edx
  uint8_t tile_id; // al
  double subgame_rate; // st7
  SubgameRuntime *v34; // ecx
  Vec3 *p_velocity; // esi
  double v36; // st7
  TrackRowCell *v37; // eax
  double v38; // st6
  double v39; // st7
  double v40; // st7
  TrackRowCell *v41; // esi
  SubgameRuntime *v42; // edi
  int32_t track_cell_row_index; // eax
  int32_t v44; // eax
  uint8_t v45; // al
  uint8_t open_edge_mask; // al
  double v47; // st7
  double v48; // st6
  SubgameRuntime *v49; // ecx
  double v50; // st7
  double v51; // st7
  double v52; // st7
  TrackRowCell *v53; // eax
  TrackRowCell *v54; // esi
  float v55; // eax
  SubgameRuntime *v56; // ecx
  double v57; // st7
  double v58; // st7
  SubgameRuntime *v59; // ecx
  SubgameRuntime *v60; // ecx
  double v61; // st7
  SubgameRuntime *v62; // ecx
  double v63; // st7
  double v64; // st7
  SubgameRuntime *v65; // ecx
  SubgameRuntime *v66; // eax
  SubgameRuntime *v67; // ecx
  int32_t state; // eax
  SubgameRuntime *v69; // eax
  SubgameRuntime *v70; // ecx
  SubgameRuntime *v71; // ebp
  bool v72; // zf
  double v73; // st7
  double wobble_alpha; // st7
  float v75; // edx
  double v76; // st7
  double wobble_y; // st6
  double v78; // st6
  double wobble_x; // st5
  double v80; // st5
  int32_t skin_hold_ticks; // eax
  double v82; // st7
  double v83; // st7
  double v84; // st7
  double v85; // st7
  double v86; // st7
  SubgameRuntime *v87; // ecx
  char *v88; // eax
  int32_t v89; // ecx
  int32_t startup_track_index; // edx
  int v91; // ecx
  double v92; // st7
  double v93; // st7
  double v94; // st7
  SubHoverState v95; // eax
  double v96; // st7
  double v97; // st6
  double v98; // st7
  uint8_t control_override_active; // al
  double v100; // st7
  SubgameRuntime *v101; // eax
  double v102; // st7
  double v103; // st7
  SubgameRuntime *v104; // ecx
  ClickStartState v105; // eax
  double v106; // st7
  SubgameRuntime *v107; // eax
  float x; // [esp-14h] [ebp-6Ch]
  float v109; // [esp-14h] [ebp-6Ch]
  float y; // [esp-10h] [ebp-68h]
  float v111; // [esp-10h] [ebp-68h]
  float z; // [esp-Ch] [ebp-64h]
  float v113; // [esp-Ch] [ebp-64h]
  float v114; // [esp+0h] [ebp-58h]
  SubLoc *value; // [esp+4h] [ebp-54h]
  SubLoc *valuea; // [esp+4h] [ebp-54h]
  float valueb; // [esp+4h] [ebp-54h]
  float valuec; // [esp+4h] [ebp-54h]
  float valued; // [esp+4h] [ebp-54h]
  float source_celld; // [esp+18h] [ebp-40h]
  TrackRowCell *source_cell; // [esp+18h] [ebp-40h]
  float source_cella; // [esp+18h] [ebp-40h]
  float source_cellb; // [esp+18h] [ebp-40h]
  float source_celle; // [esp+18h] [ebp-40h]
  float source_cellc; // [esp+18h] [ebp-40h]
  float v126; // [esp+1Ch] [ebp-3Ch]
  float v127; // [esp+1Ch] [ebp-3Ch]
  float v128; // [esp+1Ch] [ebp-3Ch]
  float v129; // [esp+20h] [ebp-38h]
  float v130; // [esp+20h] [ebp-38h]
  float v131; // [esp+20h] [ebp-38h]
  float v132; // [esp+24h] [ebp-34h]
  float v133; // [esp+24h] [ebp-34h]
  float v134; // [esp+24h] [ebp-34h]
  Vec3 position; // [esp+28h] [ebp-30h] BYREF
  float v136; // [esp+34h] [ebp-24h]
  float v137; // [esp+38h] [ebp-20h]
  float v138; // [esp+40h] [ebp-18h]
  float v139; // [esp+44h] [ebp-14h]
  float v140; // [esp+4Ch] [ebp-Ch]
  float v141; // [esp+50h] [ebp-8h]
  float v142; // [esp+54h] [ebp-4h]

  if ( player->game->subgame_pause_gate )
  {
    if ( g_game_base->players[0].frontend_state != 9 )
    {
      update_damage_gauge((int)&player->damage_gauge);
      update_progress_bar(&player->progress_bar);
      update_warning((float *)&player->warning);
      update_row_event_display(&player->game->completion);
    }
    return;
  }
  if ( player->follow_state.active == 1 )
  {
    template_record = player->follow_state.template_record;
    v3 = player->follow_state.sample_index + 3;
    segment_count = template_record->segment_count;
    if ( v3 >= segment_count )
      v3 = segment_count - 1;
    player->presentation.body.bod.object->distort.z_wave = (*(float *)template_record->primary_samples[v3]._pad_a4
                                                          * -3.0
                                                          - player->presentation.body.bod.object->distort.z_wave)
                                                         * 0.1
                                                         + player->presentation.body.bod.object->distort.z_wave;
  }
  else
  {
    player->presentation.body.bod.object->distort.z_wave = -player->presentation.body.bod.object->distort.z_wave * 0.1
                                                         + player->presentation.body.bod.object->distort.z_wave;
  }
  update_squidge(&player->squidge);
  player->presentation.body.bod.object->distort.y_squash = player->squidge.y_output;
  player->presentation.body.bod.object->distort.xyz_scale = player->squidge.z_output;
  if ( !player->game->level_mode )
    show_subgoldy_lives(player);
  movement_mode_selector = player->movement_mode_selector;
  if ( movement_mode_selector && movement_mode_selector != 2 )
  {
    game = player->game;
    if ( game->replay_update_cursor > 20 && !game->track_state_latch )
      game->track_state_latch = 1;
    v7 = player->game;
    if ( v7->selected_level_record_active )
    {
      selected_level_record = v7->selected_level_record;
      replay_update_cursor = v7->replay_update_cursor;
      if ( replay_update_cursor < selected_level_record->replay_sample_count
        && player->click_start.state != CLICK_START_STATE_WAITING_FOR_START )
      {
        p_position = (Vec3 *)&player->body.transform.position;
        player->body.transform.position.x = convert_math_type16_to_32(
                                              selected_level_record->run_records[replay_update_cursor].lateral_x,
                                              16.0);
        v11 = player->game;
        v11->track_state_latch = (v11->selected_level_record->run_records[v11->replay_update_cursor].flags & 4) != 0;
        if ( (player->game->selected_level_record->run_records[player->game->replay_update_cursor].flags & 8) != 0 )
        {
          g_game_base->players[0].frontend_state = 26;
          g_game_base->players[0].saved_frontend_state = 10;
          g_game_base->players[0].redispatch_requested = 1;
          begin_frontend_fade_in(&g_game_base->fade.state);
          return;
        }
LABEL_60:
        if ( p_position->x < -4.0 )
        {
          p_position->x = -4.0;
          player->velocity.x = 0.0;
        }
        if ( p_position->x > 4.0 )
        {
          p_position->x = 4.0;
          player->velocity.x = 0.0;
        }
        if ( LOBYTE(player->resurrect_active) )
          update_subgoldy_resurrect((int)player);
        track_grid_cell_at_world_position = get_track_grid_cell_at_world_position(player->game, p_position);
        v26 = player->game;
        source_cell = track_grid_cell_at_world_position;
        v27 = 61 * get_track_cell_row_index(track_grid_cell_at_world_position);
        v28 = &byte_5CCAC8[(_DWORD)v26 + 4 * v27];
        v29 = *(int *)((char *)unk_5CCBB8 + (_DWORD)v26 + 4 * v27);
        if ( v29 > 0 && v29 != player->row_event.id && v29 < v26->level_definition.segment_count + 1 )
        {
          player->row_event.id = v29;
          if ( *((_BYTE *)&player->game->segment_cache.slots[141][2].bod.bod.list_prev + 16928 * *((_DWORD *)v28 + 60)) )
          {
            player->row_event.tip_definition.flags = 2;
            player->row_event.tip_definition.text = (char *)(&player->game->segment_cache.slots[141][2].bod.bod.list_prev
                                                           + 4232 * *((_DWORD *)v28 + 60));
            player->row_event.tip_definition.layout_y = 0.0;
            player->row_event.tip_definition.text_scale = 30.0;
            player->row_event.tip_definition.dismiss_seconds = *(float *)&player->game->tutorial._pad_10[16928 * *((_DWORD *)v28 + 60) + 8];
            if ( !player->row_event_cutscene_started )
            {
              player->row_event_cutscene_started = 1;
              if ( p_position->x <= 0.0 )
                dispatch_cutscene_animation(&player->presentation, 3, 1u, -1);
              else
                dispatch_cutscene_animation(&player->presentation, 4, 1u, -1);
              dispatch_cutscene_animation(&player->presentation, 1, 0, -1);
            }
            v30 = *((_DWORD *)v28 + 60);
            v31 = player->game;
            if ( *(&v31->level_definition.segment_count + 4232 * v30) != -1 )
              play_voice_manager((int)g_voice_manager, 13, 2u, *(&v31->level_definition.segment_count + 4232 * v30));
            enqueue_tip_message(&g_game_base->tip_manager, &player->row_event.tip_definition, 1);
          }
        }
        if ( !player->attachment_exit_pending )
        {
          tile_id = source_cell->tile_id;
          if ( (tile_id == 29 || tile_id == 30) && !player->follow_state.active )
          {
            begin_track_attachment_follow_state(&player->follow_state, source_cell, p_position, player);
            if ( player->follow_state.template_record->kind == PATH_TEMPLATE_KIND_WORM )
              play_voice_manager((int)g_voice_manager, 12, 0, -1);
          }
        }
        if ( player->control_override_active )
        {
          if ( player->velocity.z < 0.0 )
          {
            subgame_rate = player->game->subgame_rate;
            player->velocity.z = subgame_rate * subgame_rate * 0.0040000002 * 0.25 + player->velocity.z;
          }
          if ( player->velocity.z > 0.0 )
LABEL_94:
            player->velocity.z = 0.0;
        }
        else
        {
          v34 = player->game;
          if ( (double)v34->first_block_row_count > player->body.transform.position.z )
            player->velocity.z = v34->subgame_rate * v34->subgame_rate * 0.0040000002 + player->velocity.z;
          if ( player->velocity.z > 1.0 )
            player->velocity.z = 1.0;
          if ( player->click_start.state == CLICK_START_STATE_WAITING_FOR_START )
            goto LABEL_94;
        }
        if ( player->follow_state.active == 1 )
        {
          p_velocity = &player->velocity;
          switch ( update_track_attachment_follow_state(
                     &player->follow_state,
                     player->velocity.z,
                     p_position,
                     &player->velocity) )
          {
            case 0:
              if ( player->follow_state.template_record->kind != PATH_TEMPLATE_KIND_DETOUR )
              {
                v36 = player->game->subgame_rate;
                player->velocity.z = v36 * v36 * 0.0040000002 + v36 * v36 * 0.0040000002 + player->velocity.z;
              }
              goto LABEL_101;
            case 1:
            case 3:
              if ( player->follow_state.active == 1 )
                goto LABEL_98;
              break;
            case 2:
LABEL_101:
              p_position->x = p_position->x + p_velocity->x;
              p_position->y = player->velocity.y + p_position->y;
              p_position->z = player->velocity.z + p_position->z;
              player->velocity.z = (1.0 - player->game->subgame_rate * 0.003) * player->velocity.z;
              player->velocity.y = (1.0 - player->game->subgame_rate * 0.003) * player->velocity.y;
              p_velocity->x = (1.0 - player->game->subgame_rate * 0.1) * p_velocity->x;
              player->velocity.y = player->game->subgame_rate * player->game->subgame_rate * -0.0099999998
                                 + player->velocity.y;
              if ( p_position->x < -4.0 )
              {
                p_position->x = -4.0;
                p_velocity->x = 0.0;
              }
              if ( p_position->x > 4.0 )
              {
                p_position->x = 4.0;
                p_velocity->x = 0.0;
              }
              break;
            default:
              break;
          }
        }
        else
        {
          p_position->x = player->velocity.x + p_position->x;
          p_position->y = player->velocity.y + p_position->y;
          p_position->z = player->velocity.z + p_position->z;
          if ( p_position->x < -4.0 )
          {
            p_position->x = -4.0;
            player->velocity.x = 0.0;
          }
          if ( p_position->x > 4.0 )
          {
            p_position->x = 4.0;
            player->velocity.x = 0.0;
          }
          if ( !player->completion_handoff_active )
          {
            if ( get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 15
              || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 16
              || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 18
              || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 19
              || player->damage_gauge.state == DAMAGE_GUAGE_STATE_DRAINING
              && (v37 = get_track_grid_cell_at_world_position(player->game, p_position),
                  (unsigned __int8)is_sub_loc_floor(v37)) )
            {
              v38 = player->game->subgame_rate * player->game->subgame_rate * 0.0040000002;
              player->velocity.z = v38 + v38 + player->velocity.z;
              if ( (double)player->game->first_block_row_count <= player->body.transform.position.z
                && player->body.transform.position.z > (double)player->slide_extension_threshold_z )
              {
                player->slide_extension_threshold_z = player->body.transform.position.z + 1.0;
              }
            }
          }
          if ( player->sub_hover.state == SUB_HOVER_STATE_ACTIVE )
          {
            v39 = player->game->subgame_rate;
            player->velocity.z = v39 * v39 * 0.0040000002 + v39 * v39 * 0.0040000002 + player->velocity.z;
          }
          if ( !player->trampoline_bounce_active )
            player->velocity.z = (1.0 - player->game->subgame_rate * 0.003) * player->velocity.z;
          player->velocity.y = (1.0 - player->game->subgame_rate * 0.003) * player->velocity.y;
          player->velocity.x = (1.0 - player->game->subgame_rate * 0.1) * player->velocity.x;
          if ( player->boost_one_tick )
          {
            v40 = player->game->subgame_rate;
            player->velocity.z = v40 * v40 * 0.0040000002 + v40 * v40 * 0.0040000002 + player->velocity.z;
            player->attachment_exit_pending = 0;
          }
          else
          {
            v41 = get_track_grid_cell_at_world_position(player->game, p_position);
            if ( player->attachment_exit_pending )
            {
              v42 = player->game;
              if ( (*(_DWORD *)&byte_5CCAC8[(_DWORD)v42 + 244 * get_track_cell_row_index(v41)] & 0x100) == 0
                && player->sub_hover.state == SUB_HOVER_STATE_INACTIVE
                && !player->control_override_active )
              {
                player->velocity.z = (1.0 - v42->subgame_rate * 0.2) * player->velocity.z;
              }
              if ( (byte_5CCAC8[(unsigned int)player->game + 244 * get_track_cell_row_index(v41)] & 0x40) != 0 )
              {
                v126 = player->velocity.x * 1.05;
                v129 = player->velocity.y * 1.05;
                v132 = player->velocity.z * 1.05;
                value = *(SubLoc **)((char *)unk_5CCB6C
                                   + (unsigned int)player->game
                                   + 244 * get_track_cell_row_index(v41));
                x = p_position->x;
                y = p_position->y;
                z = p_position->z;
                track_cell_row_index = get_track_cell_row_index(v41);
                try_enter_track_attachment_from_swept_motion(
                  *(Path **)(*(int *)((char *)unk_5CCB6C + (unsigned int)player->game + 244 * track_cell_row_index) + 56),
                  x,
                  y,
                  z,
                  v126,
                  v129,
                  v132,
                  value);
              }
              if ( player->attachment_exit_pending
                && byte_5CCAC8[(unsigned int)player->game + 244 * get_track_cell_row_index(v41)] < 0 )
              {
                v127 = player->velocity.x * 1.05;
                v130 = player->velocity.y * 1.05;
                v133 = player->velocity.z * 1.05;
                valuea = *(SubLoc **)((char *)unk_5CCB70
                                    + (unsigned int)player->game
                                    + 244 * get_track_cell_row_index(v41));
                v109 = p_position->x;
                v111 = p_position->y;
                v113 = p_position->z;
                v44 = get_track_cell_row_index(v41);
                try_enter_track_attachment_from_swept_motion(
                  *(Path **)(*(int *)((char *)unk_5CCB70 + (unsigned int)player->game + 244 * v44) + 56),
                  v109,
                  v111,
                  v113,
                  v127,
                  v130,
                  v133,
                  valuea);
              }
            }
            if ( !player->follow_state.active )
            {
              if ( player->body.transform.position.y < 0.49000001
                && player->body.transform.position.y > -0.16333334
                && !(unsigned __int8)is_sub_loc_empty(v41)
                && v41->tile_id != 22 )
              {
                set_matrix_rotation_identity(&player->body.transform);
                player->trampoline_bounce_active = 0;
                if ( player->velocity.y < -0.029999999 )
                {
                  valueb = player->velocity.y - 0.029999999;
                  start_squidge_y(&player->squidge, valueb);
                }
                if ( player->velocity.y <= 0.0 )
                {
                  player->body.transform.position.y = 0.49000001;
                  player->velocity.y = 0.0;
                }
                player->attachment_exit_pending = 0;
              }
              v45 = v41->tile_id;
              if ( (!v45 || v45 == 35) && player->body.transform.position.y < 0.49000001 && player->velocity.y <= 0.0 )
              {
                open_edge_mask = v41->open_edge_mask;
                v47 = player->body.transform.position.z - (double)(int)(__int64)player->body.transform.position.z;
                if ( (open_edge_mask & 2) != 0 )
                  v48 = 0.80000001;
                else
                  v48 = 1.0;
                source_cella = 0.0;
                if ( (open_edge_mask & 1) != 0 )
                  source_cella = 0.2;
                if ( v47 < v48 && v47 > source_cella && !player->attachment_exit_pending )
                  begin_post_follow_carryover((int)player);
              }
              v49 = player->game;
              if ( v49->level_mode == 3 )
                get_track_grid_cell_at_world_position(v49, p_position);
              if ( ((player->game->runtime_flags & 0x400) == 0 || (g_cheat_state & 2) != 0)
                && player->body.transform.position.y < 0.49000001 )
              {
                start_squidge_y(&player->squidge, player->velocity.y);
                player->trampoline_bounce_active = 0;
                player->velocity.y = 0.0;
                player->attachment_exit_pending = 0;
                player->body.transform.position.y = 0.49000001;
              }
              if ( player->body.transform.position.y < -7.0 && !LOBYTE(player->resurrect_active) )
                initialize_subgoldy_death(player);
            }
          }
          if ( player->surface_reaction_timer != 0.0 )
          {
            v50 = player->surface_reaction_step + player->surface_reaction_timer;
            player->surface_reaction_timer = v50;
            if ( v50 > 1.0 )
              player->surface_reaction_timer = 0.0;
          }
          if ( player->attachment_exit_pending )
          {
            player->velocity.y = player->game->subgame_rate * player->game->subgame_rate * -0.0099999998
                               + player->velocity.y;
            v53 = get_track_grid_cell_at_world_position(player->game, p_position);
            v54 = v53;
            if ( v53->tile_id == 22
              && v53->anchor_position.y + 0.49000001 > player->body.transform.position.y
              && v53->anchor_position.y - 0.49000001 < player->body.transform.position.y )
            {
              start_squidge_y(&player->squidge, player->velocity.y);
              player->velocity.y = player->game->subgame_rate * 0.30000001;
              player->body.transform.position.y = v54->anchor_position.y + 0.49000001;
              player->attachment_exit_pending = 0;
              player->trampoline_bounce_active = 1;
              play_sound_effect(41);
            }
          }
          else
          {
            v51 = sample_track_floor_height_at_position(player->game, p_position) + 0.49000001;
            if ( v51 <= player->body.transform.position.y )
            {
              v52 = player->game->subgame_rate;
              player->velocity.y = v52 * v52 * -0.0099999998 + player->velocity.y;
            }
            else
            {
              if ( player->velocity.y <= 0.0 )
                player->body.transform.position.y = v51;
              if ( get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 8
                || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 9
                || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 10
                || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 11
                || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 12
                || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 13 )
              {
                player->velocity.y = player->game->subgame_rate * 0.30000001;
              }
              else if ( get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 2
                     || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 3
                     || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 4
                     || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 5
                     || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 6
                     || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 7 )
              {
                if ( player->surface_reaction_timer == 0.0 )
                  player->surface_reaction_timer = player->surface_reaction_step;
                player->velocity.y = player->game->subgame_rate * 0.2;
                if ( !player->control_override_active )
                {
                  if ( p_position->x <= 0.0 )
                    dispatch_cutscene_animation(&player->presentation, 3, 1u, -1);
                  else
                    dispatch_cutscene_animation(&player->presentation, 4, 1u, -1);
                  dispatch_cutscene_animation(&player->presentation, 1, 0, -1);
                }
              }
              else if ( get_track_grid_cell_at_world_position(player->game, p_position)->tile_id
                     && get_track_grid_cell_at_world_position(player->game, p_position)->tile_id != 35
                     && get_track_grid_cell_at_world_position(player->game, p_position)->tile_id != 22 )
              {
                player->trampoline_bounce_active = 0;
                player->velocity.y = 0.0;
              }
            }
            if ( player->body.transform.position.y < 0.0 && player->velocity.y <= 0.0 )
LABEL_98:
              begin_post_follow_carryover((int)player);
          }
        }
        update_warning((float *)&player->warning);
        if ( player->boost_one_tick
          || player->follow_state.active
          || (v55 = p_position->y,
              v134 = p_position->z + 0.49000001,
              position.x = p_position->x,
              position.z = v134,
              v56 = player->game,
              position.y = v55,
              get_track_grid_cell_at_world_position(v56, &position)->tile_id != 14)
          || player->body.transform.position.y >= 6.5 )
        {
          player->barrier_hold_progress = 0.0;
        }
        else
        {
          player->velocity.z = 0.0;
          player->body.transform.position.z = (double)(int)(__int64)(player->body.transform.position.z + 0.49000001)
                                            - 0.5;
          if ( player->squidge.z_output == 0.0 )
            play_sound_effect(47);
          start_squidge_z(&player->squidge, -0.33000001);
          v57 = player->barrier_hold_step + player->barrier_hold_progress;
          player->barrier_hold_progress = v57;
          if ( v57 > 1.0 )
          {
            player->barrier_hold_progress = 0.0;
            if ( !player->attachment_exit_pending )
              begin_post_follow_carryover((int)player);
          }
        }
        if ( !player->lane_lean_state
          && (get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 2
           || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 4
           || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 5
           || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 7
           || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 10
           || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 8
           || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 10
           || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 11
           || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 13)
          && !player->attachment_exit_pending
          && player->body.transform.position.y <= 0.98000002 )
        {
          player->lane_lean_progress_step = player->game->subgame_rate * 0.037037037;
          if ( get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 2
            || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 5
            || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 8
            || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 11 )
          {
            player->lane_lean_state = 1;
            player->lane_lean_amplitude = 1.0;
          }
          else
          {
            player->lane_lean_state = 2;
            player->lane_lean_amplitude = -1.0;
          }
        }
        if ( player->damage_retrigger_timer != 0.0 )
        {
          v58 = player->damage_retrigger_step + player->damage_retrigger_timer;
          player->damage_retrigger_timer = v58;
          if ( v58 > 1.0 )
            player->damage_retrigger_timer = 0.0;
        }
        v59 = player->game;
        source_cellb = (float)v59->completion_row_start;
        if ( player->body.transform.position.z < (double)source_cellb || player->attachment_exit_pending )
        {
          if ( !player->boost_one_tick && !player->control_override_active )
          {
            v73 = v59->subgame_rate * 0.17;
            if ( player->velocity.z >= v73 )
            {
              v73 = v59->subgame_rate * 0.5;
              if ( player->velocity.z <= v73 )
                v73 = player->velocity.z;
            }
            player->velocity.z = v73;
          }
        }
        else
        {
          if ( !player->completion_handoff_active )
          {
            if ( v59->level_mode == 4 )
            {
              valuec = (1.0 - (player->body.transform.position.z - source_cellb) / player->velocity.z) * 0.016666668;
              advance_timer_counters(&player->stopwatch, valuec);
            }
            v60 = player->game;
            player->completion_handoff_timer = 0.0;
            player->completion_handoff_timer_step = 0.016666668;
            player->completion_handoff_voice_gate = 0;
            v61 = v60->subgame_rate * 0.17;
            if ( player->velocity.z >= v61 )
            {
              v61 = v60->subgame_rate * 0.5;
              if ( player->velocity.z <= v61 )
                v61 = player->velocity.z;
            }
            player->velocity.z = v61;
            reset_voice_manager(g_voice_manager);
            end_jetpack_hover(&player->sub_hover);
            player->presentation.cutscene.state = CUT_SCENE_STATE_COMPLETION_PENDING;
            play_sound_effect(0);
            player->boost_one_tick = 0;
          }
          player->completion_handoff_active = 1;
          v62 = player->game;
          if ( (double)v62->completion_row_start + 2.5 < player->body.transform.position.z )
          {
            v63 = player->velocity.z
                - (v62->subgame_rate * v62->subgame_rate * 0.0040000002
                 + v62->subgame_rate * v62->subgame_rate * 0.0040000002);
            player->velocity.z = v63;
            if ( v63 < 0.0 )
              player->velocity.z = 0.0;
          }
          v64 = player->completion_handoff_cycle_step + player->completion_handoff_cycle_progress;
          player->completion_handoff_cycle_progress = v64;
          if ( v64 > 1.0 )
            player->completion_handoff_cycle_progress = 0.0;
          v65 = player->game;
          player->completion_handoff_timer = player->completion_handoff_timer + player->completion_handoff_timer_step;
          v65->subgame_rebuild_selector = 2;
          if ( player->completion_handoff_timer > 2.0 && !player->completion_handoff_voice_gate )
          {
            player->completion_handoff_voice_gate = 1;
            play_voice_manager((int)g_voice_manager, 8, 2u, -1);
          }
          if ( player->completion_handoff_timer > 2.0 )
          {
            v66 = player->game;
            if ( v66->level_mode <= 1u )
            {
              if ( v66->completion.gate_18 == 1 && (player->control_source->control_flags_a & 0x4000) != 0 )
                player->completion_handoff_timer = 5.0999999;
              if ( v66->completion.state == COMPLETION_STATE_CONTINUE_ACCEPTED )
                player->completion_handoff_timer = 5.0999999;
            }
          }
          if ( player->completion_handoff_timer > 5.0 )
          {
            v67 = player->game;
            if ( v67->level_mode <= 1u && v67->completion.state != COMPLETION_STATE_CONTINUE_ACCEPTED )
              player->completion_handoff_timer = player->completion_handoff_timer
                                               - player->completion_handoff_timer_step;
          }
          if ( player->completion_handoff_timer > 5.0 )
          {
            state = g_game_base->fade.state;
            if ( !state )
            {
              begin_frontend_fade_out(&g_game_base->fade.state, 0);
              goto LABEL_287;
            }
            if ( state == 4 )
            {
              v69 = player->game;
              if ( v69->completion.state )
                flush_row_event_display(&v69->completion);
              v70 = player->game;
              if ( v70->level_mode )
              {
                complete_subgame(v70, 1u);
              }
              else
              {
                if ( v70->level_mode_arg == g_game_base->subgame.galaxy.record_count - 1 )
                {
                  complete_subgame(v70, 1u);
                  g_game_base->players[0].saved_frontend_state = 29;
                  g_game_base->players[0].frontend_state = 26;
                  return;
                }
                complete_subgame(v70, 0);
                player->game->subgame_rebuild_selector = 1;
              }
              v71 = player->game;
              if ( v71->level_mode == 7 )
              {
                g_game_base->players[0].frontend_state = 26;
                g_game_base->players[0].saved_frontend_state = 2;
              }
              else
              {
                v72 = v71->selected_level_record_persistent == 0;
                g_game_base->players[0].saved_frontend_state = g_game_base->players[0].frontend_state;
                if ( v72 )
                  g_game_base->players[0].frontend_state = 27;
                else
                  g_game_base->players[0].frontend_state = 26;
              }
              return;
            }
          }
        }
LABEL_287:
        v140 = p_position->x;
        v141 = p_position->y;
        v142 = p_position->z;
        if ( player->follow_state.active == 1 )
        {
          p_position->x = player->follow_state.output_position.x;
          p_position->y = player->follow_state.output_position.y;
          p_position->z = player->follow_state.output_position.z;
        }
        update_jetpack_gauge(&player->sub_hover);
        if ( player->completion_handoff_active )
        {
          qmemcpy(
            &g_game_base->players[0].completion_handoff_transform,
            &g_game_base->players[0].transform,
            sizeof(g_game_base->players[0].completion_handoff_transform));
          g_game_base->players[0].completion_handoff_transform.position.y = g_game_base->players[0].completion_handoff_transform.position.y
                                                                          - 1.0;
        }
        update_damage_gauge((int)&player->damage_gauge);
        update_progress_bar(&player->progress_bar);
        wobble_alpha = player->sub_hover.wobble_alpha;
        player->cached_camera_target_world.x = p_position->x;
        v75 = p_position->z;
        player->cached_camera_target_world.y = p_position->y;
        player->cached_camera_target_world.z = v75;
        v138 = wobble_alpha * player->body.transform.basis_forward.x;
        v139 = wobble_alpha * player->body.transform.basis_forward.y;
        v76 = wobble_alpha * player->body.transform.basis_forward.z;
        wobble_y = player->sub_hover.wobble_y;
        v128 = wobble_y * player->body.transform.basis_up.x;
        v131 = wobble_y * player->body.transform.basis_up.y;
        v78 = wobble_y * player->body.transform.basis_up.z;
        wobble_x = player->sub_hover.wobble_x;
        position.x = wobble_x * player->body.transform.basis_right.x;
        position.y = wobble_x * player->body.transform.basis_right.y;
        v80 = wobble_x * player->body.transform.basis_right.z;
        v136 = position.x + v128;
        v137 = position.y + v131;
        position.x = v136 + v138;
        position.y = v137 + v139;
        player->cached_camera_target_world.x = position.x + player->cached_camera_target_world.x;
        player->cached_camera_target_world.y = position.y + player->cached_camera_target_world.y;
        player->cached_camera_target_world.z = v76 + v78 + v80 + player->cached_camera_target_world.z;
        skin_hold_ticks = player->damage_gauge.skin_hold_ticks;
        if ( skin_hold_ticks > 0 )
          player->damage_gauge.skin_hold_ticks = skin_hold_ticks - 1;
        if ( player->follow_state.active == 1 )
          p_position->x = v140;
        v82 = player->game->subgame_rate * 0.037037037;
        player->lane_lean_progress_step = v82;
        if ( player->lane_lean_state )
        {
          v83 = v82 + player->lane_lean_progress;
          player->lane_lean_progress = v83;
          if ( v83 > 1.0 )
          {
            player->lane_lean_progress = 0.0;
            player->lane_lean_state = 0;
          }
        }
        if ( player->timer_360_state )
        {
          v84 = player->timer_360_step + player->timer_360_progress;
          player->timer_360_progress = v84;
          if ( v84 > 1.0 )
          {
            player->timer_360_progress = 0.0;
            player->timer_360_state = 0;
          }
        }
        v85 = player->game->subgame_rate * 0.022222223;
        player->nuke_effect_progress_step = v85;
        if ( player->nuke_effect_progress > 0.0 )
        {
          v86 = v85 + player->nuke_effect_progress;
          player->nuke_effect_progress = v86;
          if ( v86 <= 1.0 )
          {
            update_nuke(&player->nuke);
          }
          else
          {
            player->nuke_effect_progress = 0.0;
            uninit_nuke(&player->nuke);
          }
        }
        v87 = player->game;
        if ( v87->level_mode == 4 )
        {
          v88 = (char *)v87 + 129728 * v87->level_mode_arg;
          if ( *((_DWORD *)v88 + 2429012) == 1 && !v87->selected_level_record_active )
          {
            v89 = v87->replay_update_cursor;
            if ( v89 >= *((_DWORD *)v88 + 2429039) )
              v89 = *((_DWORD *)v88 + 2429039);
            startup_track_index = player->startup_track_index;
            if ( startup_track_index && (v91 = *((_DWORD *)v88 + 2429021) - startup_track_index + v89) != 0 )
              v92 = convert_math_type16_to_32(*(_WORD *)&v88[6 * v91 + 9716162], 32.0) + g_subgoldy_ghost_z;
            else
              v92 = convert_math_type16_to_32(*((_WORD *)v88 + 4858081), 32.0);
            g_subgoldy_ghost_z = v92;
            if ( player->game->selected_level_record_active )
              g_subgoldy_ghost_z = player->body.transform.position.z;
            v93 = player->body.transform.position.z + 20.0;
            if ( g_subgoldy_ghost_z >= v93 )
            {
              source_celle = v93;
              set_subgoldy_ghost_z(player, source_celle);
            }
            else
            {
              set_subgoldy_ghost_z(player, g_subgoldy_ghost_z);
            }
          }
        }
        valued = player->body.transform.position.z / (double)player->game->runtime_row_count;
        set_backdrop_progress_fraction(&g_game_base->backdrop, valued);
        v94 = (double)player->game->completion_row_start - 30.0;
        source_cellc = player->body.transform.position.z - 8.0;
        if ( v94 >= source_cellc )
          v94 = source_cellc;
        v95 = player->sub_hover.state;
        player->interaction_max_z = v94;
        if ( v95 == SUB_HOVER_STATE_ACTIVE )
        {
          if ( player->body.transform.position.y < 1.0 )
          {
            v96 = player->velocity.y * 0.89999998;
            player->velocity.y = v96;
            v97 = player->game->subgame_rate;
            player->velocity.y = v96 - v97 * v97 * -0.0099999998;
          }
          player->attachment_exit_pending = 0;
        }
        if ( player->attachment_exit_pending )
        {
          v98 = player->attachment_exit_progress_step + player->attachment_exit_progress;
          player->attachment_exit_progress = v98;
          if ( v98 > 0.69999999 && !player->attachment_exit_gate_a )
          {
            play_voice_manager((int)g_voice_manager, 3, 0, -1);
            control_override_active = player->control_override_active;
            player->attachment_exit_gate_a = 1;
            if ( !control_override_active && player->body.transform.position.y < -6.0 )
              dispatch_cutscene_animation(&player->presentation, 5, 1u, -1);
          }
          if ( player->body.transform.position.y < -7.0 && !player->attachment_exit_gate_b )
          {
            play_voice_manager((int)g_voice_manager, 1, 2u, -1);
            player->attachment_exit_gate_b = 1;
            player->attachment_exit_gate_a = 1;
          }
        }
        if ( player->startup_voice_timer > 0.0 )
        {
          v100 = player->startup_voice_step + player->startup_voice_timer;
          player->startup_voice_timer = v100;
          if ( v100 > 1.0 )
          {
            play_voice_manager((int)g_voice_manager, 7, 2u, -1);
            player->startup_voice_timer = 0.0;
          }
        }
        v101 = player->game;
        v102 = v101->subgame_rate * 0.17;
        if ( (v101->subgame_rate * 0.5 - v102) * 0.1 + v102 <= player->velocity.z
          || v102 >= player->velocity.z
          || player->attachment_exit_pending
          || player->click_start.state == CLICK_START_STATE_WAITING_FOR_START )
        {
          player->slow_commentary_timer = 0.0;
        }
        else
        {
          v103 = player->slow_commentary_step + player->slow_commentary_timer;
          player->slow_commentary_timer = v103;
          if ( v103 > 1.0 )
          {
            player->slow_commentary_timer = 0.0;
            play_voice_manager((int)g_voice_manager, 6, 1u, -1);
          }
        }
        handle_subgoldy_collisions(player);
        update_anim_manager(&player->presentation.anim_manager);
        update_anim_manager(&player->presentation.jetpack_channel.anim_manager);
        update_anim_manager(&player->presentation.weapon_channels[0].anim_manager);
        update_anim_manager(&player->presentation.weapon_channels[1].anim_manager);
        update_anim_manager(&player->presentation.weapon_channels[2].anim_manager);
        update_track_parcels(&player->game->parcel_manager);
        initialize_cutscene(&player->presentation);
        update_player_movement_flags((int *)player);
        if ( g_game_base->subgame.replay_update_cursor < 10 )
          player->movement_fire_progress = player->movement_fire_progress_step;
        v104 = player->game;
        if ( (v104->runtime_flags & 0x400000) == 0 )
          goto LABEL_365;
        if ( player->completion_handoff_active )
          goto LABEL_365;
        if ( player->control_override_active )
          goto LABEL_365;
        v105 = player->click_start.state;
        if ( v105 )
        {
          if ( v105 != CLICK_START_STATE_TEARDOWN )
            goto LABEL_365;
        }
        if ( player->movement_fire_progress > 0.0 )
        {
          v106 = player->movement_fire_progress_step + player->movement_fire_progress;
          player->movement_fire_progress = v106;
          if ( v106 > 1.0 )
            player->movement_fire_progress = 0.0;
          goto LABEL_365;
        }
        if ( v104->track_state_latch )
        {
          if ( v104->selected_level_record_active )
          {
            if ( (v104->selected_level_record->run_records[v104->replay_update_cursor].flags & 1) == 0 )
            {
              if ( (v104->selected_level_record->run_records[v104->replay_update_cursor].flags & 2) == 0 )
                goto LABEL_365;
              goto LABEL_364;
            }
            goto LABEL_359;
          }
          if ( (player->control_source->control_flags_a & 0x4000) != 0 )
          {
LABEL_359:
            play_movement_state_sound(player);
            update_movement_flag_emitters(player, player);
            player->movement_fire_progress = player->movement_fire_progress_step + 0.30000001;
            goto LABEL_365;
          }
          if ( (player->control_source->control_flags_b & 0x4000) != 0 )
          {
LABEL_364:
            player->movement_fire_progress = player->movement_fire_progress_step;
            play_movement_state_sound(player);
            update_movement_flag_emitters(player, player);
          }
        }
LABEL_365:
        update_row_event_display(&player->game->completion);
        ++player->game->current_high_score_record.replay_sample_count;
        ++player->game->replay_update_cursor;
        v107 = player->game;
        if ( v107->replay_update_cursor == 21000 )
          show_times_up_message((int *)&v107->times_up);
        update_times_up((int)&player->game->times_up);
        return;
      }
    }
    if ( player->follow_state._pad_3c[0] && player->completion_handoff_active )
    {
      player->track_z_offset = 320.0;
      player->track_z_anchor = 320.0;
    }
    else
    {
      if ( player->control_override_active )
      {
        v12 = player->track_z_offset
            - (player->presentation.body.transform.basis_up.x
             + player->presentation.body.transform.basis_up.x);
        player->track_z_offset = v12;
        player->track_z_anchor = v12;
        if ( player->track_z_offset >= 0.0 )
        {
          if ( player->track_z_offset <= 639.0 )
            track_z_offset = player->track_z_offset;
          else
            track_z_offset = 639.0;
        }
        else
        {
          track_z_offset = 0.0;
        }
      }
      else
      {
        resolve_uncaptured_cursor_sensitivity_scale(g_runtime_config.steering_sensitivity[player->steering_mode_selector]);
        v14 = player->control_source->steering_x - player->track_z_anchor + player->track_z_offset;
        player->track_z_offset = v14;
        if ( v16 )
        {
          v14 = 0.0;
        }
        else if ( v14 > 639.0 )
        {
          v14 = 639.0;
        }
        player->track_z_offset = v14;
        player->track_z_anchor = player->control_source->steering_x;
        if ( player->steering_mode_selector != 1 )
          goto LABEL_40;
        track_z_offset = player->control_source->steering_x;
      }
      player->track_z_offset = track_z_offset;
    }
LABEL_40:
    if ( !player->completion_handoff_active )
    {
      v17 = (320.0 - player->track_z_offset) * 0.0125;
      if ( v17 >= -3.7 )
      {
        if ( v17 > 3.7 )
          v17 = 3.7;
      }
      else
      {
        v17 = -3.7;
      }
      if ( player->click_start.state != CLICK_START_STATE_WAITING_FOR_START )
        player->body.transform.position.x = player->game->subgame_rate * 0.2 * (v17 - player->body.transform.position.x)
                                          + player->body.transform.position.x;
    }
    p_position = (Vec3 *)&player->body.transform.position;
    v18 = convert_math_type32_to_16(player->body.transform.position.x, 16.0);
    source_celld = convert_math_type16_to_32(v18, 16.0);
    player->body.transform.position.x = source_celld;
    v19 = player->game;
    v19->current_high_score_record.run_records[v19->replay_update_cursor].lateral_x = convert_math_type32_to_16(
                                                                                        source_celld,
                                                                                        16.0);
    v20 = player->game;
    if ( v20->replay_update_cursor )
    {
      v114 = player->body.transform.position.z - g_replay_accum_z;
      v20->current_high_score_record.run_records[v20->replay_update_cursor].delta_z = convert_math_type32_to_16(
                                                                                        v114,
                                                                                        32.0);
      v21 = convert_math_type16_to_32(
              player->game->current_high_score_record.run_records[player->game->replay_update_cursor].delta_z,
              32.0)
          + g_replay_accum_z;
    }
    else
    {
      v20->current_high_score_record.run_records[v20->replay_update_cursor].delta_z = convert_math_type32_to_16(
                                                                                        player->body.transform.position.z,
                                                                                        32.0);
      v21 = convert_math_type16_to_32(
              player->game->current_high_score_record.run_records[player->game->replay_update_cursor].delta_z,
              32.0);
    }
    g_replay_accum_z = v21;
    v22 = player->game;
    if ( v22->track_state_latch )
    {
      if ( (player->control_source->control_flags_a & 0x4000) != 0 )
        v22->current_high_score_record.run_records[v22->replay_update_cursor].flags |= 1u;
      if ( (player->control_source->control_flags_b & 0x4000) != 0 )
        player->game->current_high_score_record.run_records[player->game->replay_update_cursor].flags |= 2u;
    }
    control_source = player->control_source;
    if ( (control_source->control_flags_b & 0x4000) == 0 && (control_source->control_flags_a & 0x4000) == 0 )
      player->game->track_state_latch = 1;
    v24 = player->game;
    if ( v24->track_state_latch )
      v24->current_high_score_record.run_records[v24->replay_update_cursor].flags |= 4u;
    goto LABEL_60;
  }
}
