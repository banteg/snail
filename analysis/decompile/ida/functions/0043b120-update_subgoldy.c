/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_subgoldy @ 0x43b120 */
/* selector: update_subgoldy */

// Main per-frame player or Goldy actor step. Updates attachment-follow state, samples current track cells, drives row events, dispatches pickups and completion handoff, emits movement flags and sounds, and advances the runtime track index. It contains four direct calls to `begin_post_follow_carryover`, plus the post-exit progress loop that advances `attachment_exit_progress` by `attachment_exit_progress_step` and trips the `gate_a` and `gate_b` thresholds. Windows `cdb` confirmed those carryover-arm lanes are real, but at least one clean level-complete path bypasses all four of them. Newer field-xref narrowing also shows later retirement of `attachment_exit_pending` happens only through five clear sites inside this function, not through the swept-entry helper or a standalone progress-expiry store; one of those clear sites, `0x43bcb3`, now resolves to the non-follow floor-cache/slide motion branch for runtime tiles `0x0f`/`0x10`/`0x12`/`0x13` plus the `damage_gauge.state == 2` slide override. Cross-port Android 
int32_t __thiscall update_subgoldy(Player *player)
{
  int32_t result; // eax
  PathTemplate *template_record; // esi
  signed int v4; // eax
  signed int segment_count; // ecx
  Game *game; // eax
  Game *v7; // eax
  int v8; // ecx
  int v9; // eax
  Vec3 *p_position; // ebx
  Game *v11; // eax
  double v12; // st7
  double steering_x; // st7
  double v14; // st7
  char v16; // c0
  double v17; // st7
  __int16 v18; // ax
  Game *v19; // esi
  Game *v20; // esi
  double v21; // st7
  Game *v22; // eax
  PlayerControlSource *control_source; // eax
  Game *v24; // eax
  TrackRowCell *track_grid_cell_at_world_position; // eax
  Game *v26; // edi
  int v27; // eax
  char *v28; // esi
  int32_t v29; // eax
  int v30; // esi
  Game *v31; // edx
  uint8_t tile_id; // al
  double track_center_x; // st7
  Game *v34; // ecx
  Vec3 *p_velocity; // esi
  double v36; // st7
  TrackRowCell *v37; // eax
  double v38; // st6
  double v39; // st7
  double v40; // st7
  TrackRowCell *v41; // esi
  Game *v42; // edi
  int track_cell_row_index; // eax
  int v44; // eax
  uint8_t v45; // al
  uint8_t v46; // al
  double v47; // st7
  double v48; // st6
  Game *v49; // ecx
  double v50; // st7
  double v51; // st7
  double v52; // st7
  TrackRowCell *v53; // eax
  TrackRowCell *v54; // esi
  float v55; // eax
  Game *v56; // ecx
  double v57; // st7
  double v58; // st7
  Game *v59; // ecx
  Game *v60; // ecx
  double v61; // st7
  Game *v62; // ecx
  double v63; // st7
  double v64; // st7
  Game *v65; // ecx
  Game *v66; // eax
  Game *v67; // ecx
  int v68; // eax
  Game *v69; // eax
  Game *v70; // ecx
  Game *v71; // ebp
  bool v72; // zf
  double v73; // st7
  double wobble_y; // st7
  float v75; // edx
  double v76; // st7
  double wobble_x; // st6
  double v78; // st6
  double v79; // st5
  double v80; // st5
  int32_t skin_hold_ticks; // eax
  double v82; // st7
  double v83; // st7
  double v84; // st7
  double v85; // st7
  double v86; // st7
  Game *v87; // ecx
  char *v88; // eax
  int v89; // ecx
  int v90; // edx
  int v91; // ecx
  double v92; // st7
  double v93; // st7
  double v94; // st7
  float cycle_phase_step; // eax
  double v96; // st7
  double v97; // st6
  double v98; // st7
  uint8_t control_override_active; // al
  double v100; // st7
  Game *v101; // eax
  double v102; // st7
  double v103; // st7
  Game *v104; // ecx
  int32_t movement_state; // eax
  double v106; // st7
  Game *v107; // eax
  float x; // [esp-14h] [ebp-6Ch]
  float v109; // [esp-14h] [ebp-6Ch]
  float y; // [esp-10h] [ebp-68h]
  float v111; // [esp-10h] [ebp-68h]
  float z; // [esp-Ch] [ebp-64h]
  float v113; // [esp-Ch] [ebp-64h]
  float v114; // [esp+0h] [ebp-58h]
  int v115; // [esp+4h] [ebp-54h]
  int v116; // [esp+4h] [ebp-54h]
  float v117; // [esp+4h] [ebp-54h]
  float v118; // [esp+4h] [ebp-54h]
  int v119; // [esp+4h] [ebp-54h]
  float v120; // [esp+18h] [ebp-40h]
  TrackRowCell *v121; // [esp+18h] [ebp-40h]
  float v122; // [esp+18h] [ebp-40h]
  float completion_row_start; // [esp+18h] [ebp-40h]
  int v124; // [esp+18h] [ebp-40h]
  float v125; // [esp+18h] [ebp-40h]
  float v126; // [esp+1Ch] [ebp-3Ch]
  float v127; // [esp+1Ch] [ebp-3Ch]
  float v128; // [esp+1Ch] [ebp-3Ch]
  float v129; // [esp+20h] [ebp-38h]
  float v130; // [esp+20h] [ebp-38h]
  float v131; // [esp+20h] [ebp-38h]
  float v132; // [esp+24h] [ebp-34h]
  float v133; // [esp+24h] [ebp-34h]
  float v134; // [esp+24h] [ebp-34h]
  Vec3 v135; // [esp+28h] [ebp-30h] BYREF
  float v136; // [esp+34h] [ebp-24h]
  float v137; // [esp+38h] [ebp-20h]
  float v138; // [esp+40h] [ebp-18h]
  float v139; // [esp+44h] [ebp-14h]
  float v140; // [esp+4Ch] [ebp-Ch]
  float v141; // [esp+50h] [ebp-8h]
  float v142; // [esp+54h] [ebp-4h]

  result = (int32_t)player->game;
  if ( *(_BYTE *)(result + 9) )
  {
    if ( *((_DWORD *)MEMORY[0x4DF904] + 110) != 9 )
    {
      update_damage_gauge((int)&player->damage_gauge);
      update_progress_bar();
      update_warning((float *)&player->_pad_3f0[4]);
      update_row_event_display((RowEventDisplayController *)&player->game[1]._pad_5c[340]);
    }
    return result;
  }
  if ( player->follow_state.active == 1 )
  {
    template_record = player->follow_state.template_record;
    v4 = player->follow_state.sample_index + 3;
    segment_count = template_record->segment_count;
    if ( v4 >= segment_count )
      v4 = segment_count - 1;
    *(float *)(*(_DWORD *)&player->presentation._pad_08[24] + 128) = (*(float *)template_record->primary_samples[v4]._pad_a4
                                                                    * -3.0
                                                                    - *(float *)(*(_DWORD *)&player->presentation._pad_08[24]
                                                                               + 128))
                                                                   * 0.1
                                                                   + *(float *)(*(_DWORD *)&player->presentation._pad_08[24]
                                                                              + 128);
  }
  else
  {
    *(float *)(*(_DWORD *)&player->presentation._pad_08[24] + 128) = -*(float *)(*(_DWORD *)&player->presentation._pad_08[24]
                                                                               + 128)
                                                                   * 0.1
                                                                   + *(float *)(*(_DWORD *)&player->presentation._pad_08[24]
                                                                              + 128);
  }
  update_squidge((SquidgeState *)&player->visible_life_stock);
  *(_DWORD *)(*(_DWORD *)&player->presentation._pad_08[24] + 132) = player->visible_life_stock;
  *(float *)(*(_DWORD *)&player->presentation._pad_08[24] + 136) = player->squidge.y_phase;
  if ( !player->game->level_mode )
    show_subgoldy_lives(player);
  result = player->movement_mode_selector;
  if ( result )
  {
    result -= 2;
    if ( result )
    {
      game = player->game;
      if ( *(int *)&game->_pad_ff25e0[508] > 20 && !game->track_state_latch )
        game->track_state_latch = 1;
      v7 = player->game;
      if ( v7->_pad_ff25e0[496] )
      {
        v8 = *(_DWORD *)&v7->_pad_ff25e0[500];
        v9 = *(_DWORD *)&v7->_pad_ff25e0[508];
        if ( v9 < *(_DWORD *)(v8 + 108) && player->movement_state != 2 )
        {
          p_position = (Vec3 *)&player->live_matrix.position;
          player->live_matrix.position.x = convert_math_type16_to_32(*(_WORD *)(v8 + 6 * v9 + 112), 16.0);
          v11 = player->game;
          v11->track_state_latch = (*(_BYTE *)(*(_DWORD *)&v11->_pad_ff25e0[500]
                                             + 6 * *(_DWORD *)&v11->_pad_ff25e0[508]
                                             + 116)
                                  & 4) != 0;
          if ( (*(_BYTE *)(*(_DWORD *)&player->game->_pad_ff25e0[500]
                         + 6 * *(_DWORD *)&player->game->_pad_ff25e0[508]
                         + 116)
              & 8) != 0 )
          {
            *((_DWORD *)MEMORY[0x4DF904] + 110) = 26;
            *((_DWORD *)MEMORY[0x4DF904] + 111) = 10;
            *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
            begin_frontend_fade_in((_DWORD *)MEMORY[0x4DF904] + 9);
            return result;
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
          if ( player->_pad_78[12] )
            update_subgoldy_resurrect((int)player);
          track_grid_cell_at_world_position = get_track_grid_cell_at_world_position(player->game, p_position);
          v26 = player->game;
          v121 = track_grid_cell_at_world_position;
          v27 = 61 * get_track_cell_row_index(track_grid_cell_at_world_position);
          v28 = &byte_5CCAC8[(_DWORD)v26 + 4 * v27];
          v29 = *(int *)((char *)unk_5CCBB8 + (_DWORD)v26 + 4 * v27);
          if ( v29 > 0 && v29 != player->row_event.id && v29 < v26->level_segment_count + 1 )
          {
            player->row_event.id = v29;
            if ( player->game->_pad_5c[16928 * *((_DWORD *)v28 + 60) + 42516] )
            {
              player->row_event.tip_definition.flags = 2;
              player->row_event.tip_definition.text = (char *)&player->game->_pad_5c[16928 * *((_DWORD *)v28 + 60)
                                                                                   + 42516];
              player->row_event.tip_definition.layout_y = 0.0;
              player->row_event.tip_definition.text_scale = 30.0;
              player->row_event.tip_definition.dismiss_seconds = *(float *)&player->game->_pad_a855[16928 * *((_DWORD *)v28 + 60) + 27];
              if ( !player->row_event_cutscene_started )
              {
                player->row_event_cutscene_started = 1;
                if ( p_position->x <= 0.0 )
                  dispatch_cutscene_animation((PlayerPresentationController *)&player->interaction_max_z, 3, 1u, -1);
                else
                  dispatch_cutscene_animation((PlayerPresentationController *)&player->interaction_max_z, 4, 1u, -1);
                dispatch_cutscene_animation((PlayerPresentationController *)&player->interaction_max_z, 1, 0, -1);
              }
              v30 = *((_DWORD *)v28 + 60);
              v31 = player->game;
              if ( *(_DWORD *)&v31->_pad_a855[16928 * v30 + 31] != -1 )
                play_voice_manager((int)unk_751498, 13, 2u, *(_DWORD *)&v31->_pad_a855[16928 * v30 + 31]);
              enqueue_tip_message(
                (TipManager *)((char *)MEMORY[0x4DF904] + 19820376),
                &player->row_event.tip_definition,
                1);
            }
          }
          if ( !player->attachment_exit_pending )
          {
            tile_id = v121->tile_id;
            if ( (tile_id == 29 || tile_id == 30) && !player->follow_state.active )
            {
              begin_track_attachment_follow_state(&player->follow_state, v121, p_position, player);
              if ( player->follow_state.template_record->kind == PATH_TEMPLATE_KIND_WORM )
                play_voice_manager((int)unk_751498, 12, 0, -1);
            }
          }
          if ( player->control_override_active )
          {
            if ( player->velocity.z < 0.0 )
            {
              track_center_x = player->game->track_center_x;
              player->velocity.z = track_center_x * track_center_x * 0.0040000002 * 0.25 + player->velocity.z;
            }
            if ( player->velocity.z > 0.0 )
LABEL_94:
              player->velocity.z = 0.0;
          }
          else
          {
            v34 = player->game;
            if ( (double)v34->first_block_row_count > player->live_matrix.position.z )
              player->velocity.z = v34->track_center_x * v34->track_center_x * 0.0040000002 + player->velocity.z;
            if ( player->velocity.z > 1.0 )
              player->velocity.z = 1.0;
            if ( player->movement_state == 2 )
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
                  v36 = player->game->track_center_x;
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
                player->velocity.z = (1.0 - player->game->track_center_x * 0.003) * player->velocity.z;
                player->velocity.y = (1.0 - player->game->track_center_x * 0.003) * player->velocity.y;
                p_velocity->x = (1.0 - player->game->track_center_x * 0.1) * p_velocity->x;
                player->velocity.y = player->game->track_center_x * player->game->track_center_x * -0.0099999998
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
            if ( !LOBYTE(player->completion_handoff_active) )
            {
              if ( get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 15
                || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 16
                || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 18
                || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 19
                || player->damage_gauge.state == 2
                && (v37 = get_track_grid_cell_at_world_position(player->game, p_position),
                    is_slide_cache_tile_family(v37)) )
              {
                v38 = player->game->track_center_x * player->game->track_center_x * 0.0040000002;
                player->velocity.z = v38 + v38 + player->velocity.z;
                if ( (double)player->game->first_block_row_count <= player->live_matrix.position.z
                  && player->live_matrix.position.z > (double)player->movement_rate_scalar )
                {
                  player->movement_rate_scalar = player->live_matrix.position.z + 1.0;
                }
              }
            }
            if ( LODWORD(player->jetpack_gauge.cycle_phase_step) == 1 )
            {
              v39 = player->game->track_center_x;
              player->velocity.z = v39 * v39 * 0.0040000002 + v39 * v39 * 0.0040000002 + player->velocity.z;
            }
            if ( !player->_pad_1e4[0] )
              player->velocity.z = (1.0 - player->game->track_center_x * 0.003) * player->velocity.z;
            player->velocity.y = (1.0 - player->game->track_center_x * 0.003) * player->velocity.y;
            player->velocity.x = (1.0 - player->game->track_center_x * 0.1) * player->velocity.x;
            if ( player->_pad_41c[0] )
            {
              v40 = player->game->track_center_x;
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
                  && !LODWORD(player->jetpack_gauge.cycle_phase_step)
                  && !player->control_override_active )
                {
                  player->velocity.z = (1.0 - v42->track_center_x * 0.2) * player->velocity.z;
                }
                if ( (byte_5CCAC8[(unsigned int)&player->game->_pad_00[244 * get_track_cell_row_index(v41)]] & 0x40) != 0 )
                {
                  v126 = player->velocity.x * 1.05;
                  v129 = player->velocity.y * 1.05;
                  v132 = player->velocity.z * 1.05;
                  v115 = *(int *)((char *)unk_5CCB6C
                                + (unsigned int)&player->game->_pad_00[244 * get_track_cell_row_index(v41)]);
                  x = p_position->x;
                  y = p_position->y;
                  z = p_position->z;
                  track_cell_row_index = get_track_cell_row_index(v41);
                  try_enter_track_attachment_from_swept_motion(
                    *(_DWORD **)(*(int *)((char *)unk_5CCB6C
                                        + (unsigned int)&player->game->_pad_00[244 * track_cell_row_index])
                               + 56),
                    x,
                    y,
                    z,
                    v126,
                    v129,
                    v132,
                    v115);
                }
                if ( player->attachment_exit_pending
                  && byte_5CCAC8[(unsigned int)&player->game->_pad_00[244 * get_track_cell_row_index(v41)]] < 0 )
                {
                  v127 = player->velocity.x * 1.05;
                  v130 = player->velocity.y * 1.05;
                  v133 = player->velocity.z * 1.05;
                  v116 = *(int *)((char *)unk_5CCB70
                                + (unsigned int)&player->game->_pad_00[244 * get_track_cell_row_index(v41)]);
                  v109 = p_position->x;
                  v111 = p_position->y;
                  v113 = p_position->z;
                  v44 = get_track_cell_row_index(v41);
                  try_enter_track_attachment_from_swept_motion(
                    *(_DWORD **)(*(int *)((char *)unk_5CCB70 + (unsigned int)&player->game->_pad_00[244 * v44]) + 56),
                    v109,
                    v111,
                    v113,
                    v127,
                    v130,
                    v133,
                    v116);
                }
              }
              if ( !player->follow_state.active )
              {
                if ( player->live_matrix.position.y < 0.49000001
                  && player->live_matrix.position.y > -0.16333334
                  && !is_open_neighbor_tile_family(v41)
                  && v41->tile_id != 22 )
                {
                  set_matrix_rotation_identity(&player->live_matrix);
                  player->_pad_1e4[0] = 0;
                  if ( player->velocity.y < -0.029999999 )
                  {
                    v117 = player->velocity.y - 0.029999999;
                    start_squidge_y((SquidgeState *)&player->visible_life_stock, v117);
                  }
                  if ( player->velocity.y <= 0.0 )
                  {
                    player->live_matrix.position.y = 0.49000001;
                    player->velocity.y = 0.0;
                  }
                  player->attachment_exit_pending = 0;
                }
                v45 = v41->tile_id;
                if ( (!v45 || v45 == 35) && player->live_matrix.position.y < 0.49000001 && player->velocity.y <= 0.0 )
                {
                  v46 = v41->_pad_3d[0];
                  v47 = player->live_matrix.position.z - (double)(int)(__int64)player->live_matrix.position.z;
                  if ( (v46 & 2) != 0 )
                    v48 = 0.80000001;
                  else
                    v48 = 1.0;
                  v122 = 0.0;
                  if ( (v46 & 1) != 0 )
                    v122 = 0.2;
                  if ( v47 < v48 && v47 > v122 && !player->attachment_exit_pending )
                    begin_post_follow_carryover((int)player);
                }
                v49 = player->game;
                if ( v49->level_mode == 3 )
                  get_track_grid_cell_at_world_position(v49, p_position);
                if ( ((player->game->runtime_flags & 0x400) == 0 || (byte_4B2F40 & 2) != 0)
                  && player->live_matrix.position.y < 0.49000001 )
                {
                  start_squidge_y((SquidgeState *)&player->visible_life_stock, player->velocity.y);
                  player->_pad_1e4[0] = 0;
                  player->velocity.y = 0.0;
                  player->attachment_exit_pending = 0;
                  player->live_matrix.position.y = 0.49000001;
                }
                if ( player->live_matrix.position.y < -7.0 && !player->_pad_78[12] )
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
              player->velocity.y = player->game->track_center_x * player->game->track_center_x * -0.0099999998
                                 + player->velocity.y;
              v53 = get_track_grid_cell_at_world_position(player->game, p_position);
              v54 = v53;
              if ( v53->tile_id == 22
                && v53->anchor_position.y + 0.49000001 > player->live_matrix.position.y
                && v53->anchor_position.y - 0.49000001 < player->live_matrix.position.y )
              {
                start_squidge_y((SquidgeState *)&player->visible_life_stock, player->velocity.y);
                player->velocity.y = player->game->track_center_x * 0.30000001;
                player->live_matrix.position.y = v54->anchor_position.y + 0.49000001;
                player->attachment_exit_pending = 0;
                player->_pad_1e4[0] = 1;
                play_sound_effect(41);
              }
            }
            else
            {
              v51 = sample_track_floor_height_at_position(player->game, p_position) + 0.49000001;
              if ( v51 <= player->live_matrix.position.y )
              {
                v52 = player->game->track_center_x;
                player->velocity.y = v52 * v52 * -0.0099999998 + player->velocity.y;
              }
              else
              {
                if ( player->velocity.y <= 0.0 )
                  player->live_matrix.position.y = v51;
                if ( get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 8
                  || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 9
                  || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 10
                  || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 11
                  || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 12
                  || get_track_grid_cell_at_world_position(player->game, p_position)->tile_id == 13 )
                {
                  player->velocity.y = player->game->track_center_x * 0.30000001;
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
                  player->velocity.y = player->game->track_center_x * 0.2;
                  if ( !player->control_override_active )
                  {
                    if ( p_position->x <= 0.0 )
                      dispatch_cutscene_animation((PlayerPresentationController *)&player->interaction_max_z, 3, 1u, -1);
                    else
                      dispatch_cutscene_animation((PlayerPresentationController *)&player->interaction_max_z, 4, 1u, -1);
                    dispatch_cutscene_animation((PlayerPresentationController *)&player->interaction_max_z, 1, 0, -1);
                  }
                }
                else if ( get_track_grid_cell_at_world_position(player->game, p_position)->tile_id
                       && get_track_grid_cell_at_world_position(player->game, p_position)->tile_id != 35
                       && get_track_grid_cell_at_world_position(player->game, p_position)->tile_id != 22 )
                {
                  player->_pad_1e4[0] = 0;
                  player->velocity.y = 0.0;
                }
              }
              if ( player->live_matrix.position.y < 0.0 && player->velocity.y <= 0.0 )
LABEL_98:
                begin_post_follow_carryover((int)player);
            }
          }
          update_warning((float *)&player->_pad_3f0[4]);
          if ( player->_pad_41c[0]
            || player->follow_state.active
            || (v55 = p_position->y,
                v134 = p_position->z + 0.49000001,
                v135.x = p_position->x,
                v135.z = v134,
                v56 = player->game,
                v135.y = v55,
                get_track_grid_cell_at_world_position(v56, &v135)->tile_id != 14)
            || player->live_matrix.position.y >= 6.5 )
          {
            *(_DWORD *)&player->_pad_30c[28] = 0;
          }
          else
          {
            player->velocity.z = 0.0;
            player->live_matrix.position.z = (double)(int)(__int64)(player->live_matrix.position.z + 0.49000001) - 0.5;
            if ( player->squidge.y_phase == 0.0 )
              play_sound_effect(47);
            start_squidge_z((SquidgeState *)&player->visible_life_stock, -0.33000001);
            v57 = *(float *)&player->_pad_30c[32] + *(float *)&player->_pad_30c[28];
            *(float *)&player->_pad_30c[28] = v57;
            if ( v57 > 1.0 )
            {
              *(_DWORD *)&player->_pad_30c[28] = 0;
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
            && player->live_matrix.position.y <= 0.98000002 )
          {
            player->lane_lean_progress_step = player->game->track_center_x * 0.037037037;
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
          completion_row_start = (float)v59->completion_row_start;
          if ( player->live_matrix.position.z < (double)completion_row_start || player->attachment_exit_pending )
          {
            if ( !player->_pad_41c[0] && !player->control_override_active )
            {
              v73 = v59->track_center_x * 0.17;
              if ( player->velocity.z >= v73 )
              {
                v73 = v59->track_center_x * 0.5;
                if ( player->velocity.z <= v73 )
                  v73 = player->velocity.z;
              }
              player->velocity.z = v73;
            }
          }
          else
          {
            if ( !LOBYTE(player->completion_handoff_active) )
            {
              if ( v59->level_mode == 4 )
              {
                v118 = (1.0 - (player->live_matrix.position.z - completion_row_start) / player->velocity.z)
                     * 0.016666668;
                advance_timer_counters((float *)&player->_pad_2e4[4], v118);
              }
              v60 = player->game;
              player->completion_handoff_timer = 0.0;
              player->completion_handoff_timer_step = 0.016666668;
              player->completion_handoff_voice_gate = 0;
              v61 = v60->track_center_x * 0.17;
              if ( player->velocity.z >= v61 )
              {
                v61 = v60->track_center_x * 0.5;
                if ( player->velocity.z <= v61 )
                  v61 = player->velocity.z;
              }
              player->velocity.z = v61;
              reset_voice_manager(unk_751498);
              end_jetpack_hover((float *)&player->_pad_2744[8]);
              player->presentation.cutscene_ai.unresolved_08 = 5;
              play_sound_effect(0);
              player->_pad_41c[0] = 0;
            }
            LOBYTE(player->completion_handoff_active) = 1;
            v62 = player->game;
            if ( (double)v62->completion_row_start + 2.5 < player->live_matrix.position.z )
            {
              v63 = player->velocity.z
                  - (v62->track_center_x * v62->track_center_x * 0.0040000002
                   + v62->track_center_x * v62->track_center_x * 0.0040000002);
              player->velocity.z = v63;
              if ( v63 < 0.0 )
                player->velocity.z = 0.0;
            }
            v64 = *(float *)player->_pad_2744 + player->track_z_anchor;
            player->track_z_anchor = v64;
            if ( v64 > 1.0 )
              player->track_z_anchor = 0.0;
            v65 = player->game;
            player->completion_handoff_timer = player->completion_handoff_timer + player->completion_handoff_timer_step;
            *(_DWORD *)&v65->_pad_ff25e0[2616296] = 2;
            if ( player->completion_handoff_timer > 2.0 && !player->completion_handoff_voice_gate )
            {
              player->completion_handoff_voice_gate = 1;
              play_voice_manager((int)unk_751498, 8, 2u, -1);
            }
            if ( player->completion_handoff_timer > 2.0 )
            {
              v66 = player->game;
              if ( v66->level_mode <= 1u )
              {
                if ( v66[1]._pad_5c[364] == 1 && (player->control_source->control_flags_a & 0x4000) != 0 )
                  player->completion_handoff_timer = 5.0999999;
                if ( *(_DWORD *)&v66[1]._pad_5c[360] == 5 )
                  player->completion_handoff_timer = 5.0999999;
              }
            }
            if ( player->completion_handoff_timer > 5.0 )
            {
              v67 = player->game;
              if ( v67->level_mode <= 1u && *(_DWORD *)&v67[1]._pad_5c[360] != 5 )
                player->completion_handoff_timer = player->completion_handoff_timer
                                                 - player->completion_handoff_timer_step;
            }
            if ( player->completion_handoff_timer > 5.0 )
            {
              v68 = *((_DWORD *)MEMORY[0x4DF904] + 9);
              if ( !v68 )
              {
                begin_frontend_fade_out((_DWORD *)MEMORY[0x4DF904] + 9, 0);
                goto LABEL_287;
              }
              if ( v68 == 4 )
              {
                v69 = player->game;
                if ( *(_DWORD *)&v69[1]._pad_5c[360] )
                  flush_row_event_display((RowEventDisplayController *)&v69[1]._pad_5c[340]);
                v70 = player->game;
                if ( v70->level_mode )
                {
                  complete_subgame((int)v70, 1);
                }
                else
                {
                  if ( v70->level_mode_arg == *((_DWORD *)MEMORY[0x4DF904] + 4936081) - 1 )
                  {
                    complete_subgame((int)v70, 1);
                    *((_DWORD *)MEMORY[0x4DF904] + 111) = 29;
                    *((_DWORD *)MEMORY[0x4DF904] + 110) = 26;
                    return result;
                  }
                  complete_subgame((int)v70, 0);
                  result = (int32_t)player->game;
                  *(_DWORD *)(result + 19337160) = 1;
                }
                v71 = player->game;
                if ( v71->level_mode == 7 )
                {
                  *((_DWORD *)MEMORY[0x4DF904] + 110) = 26;
                  *((_DWORD *)MEMORY[0x4DF904] + 111) = 2;
                }
                else
                {
                  v72 = v71->_pad_ff25e0[497] == 0;
                  result = (int32_t)MEMORY[0x4DF904];
                  *((_DWORD *)MEMORY[0x4DF904] + 111) = *((_DWORD *)MEMORY[0x4DF904] + 110);
                  if ( v72 )
                    *((_DWORD *)MEMORY[0x4DF904] + 110) = 27;
                  else
                    *((_DWORD *)MEMORY[0x4DF904] + 110) = 26;
                }
                return result;
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
          update_jetpack_gauge((int)&player->_pad_2744[8]);
          if ( LOBYTE(player->completion_handoff_active) )
          {
            qmemcpy((char *)MEMORY[0x4DF904] + 716, (char *)MEMORY[0x4DF904] + 348, 0x40u);
            *((float *)MEMORY[0x4DF904] + 192) = *((float *)MEMORY[0x4DF904] + 192) - 1.0;
          }
          update_damage_gauge((int)&player->damage_gauge);
          update_progress_bar();
          wobble_y = player->jetpack_gauge.wobble_y;
          player->jetpack_gauge.warning_intensity = p_position->x;
          v75 = p_position->z;
          player->cached_camera_target_world.x = p_position->y;
          player->cached_camera_target_world.y = v75;
          v138 = wobble_y * player->live_matrix.basis_forward.x;
          v139 = wobble_y * player->live_matrix.basis_forward.y;
          v76 = wobble_y * player->live_matrix.basis_forward.z;
          wobble_x = player->jetpack_gauge.wobble_x;
          v128 = wobble_x * player->live_matrix.basis_up.x;
          v131 = wobble_x * player->live_matrix.basis_up.y;
          v78 = wobble_x * player->live_matrix.basis_up.z;
          v79 = *(float *)&player->jetpack_gauge.warning_anchor;
          v135.x = v79 * player->live_matrix.basis_right.x;
          v135.y = v79 * player->live_matrix.basis_right.y;
          v80 = v79 * player->live_matrix.basis_right.z;
          v136 = v135.x + v128;
          v137 = v135.y + v131;
          v135.x = v136 + v138;
          v135.y = v137 + v139;
          player->jetpack_gauge.warning_intensity = v135.x + player->jetpack_gauge.warning_intensity;
          player->cached_camera_target_world.x = v135.y + player->cached_camera_target_world.x;
          player->cached_camera_target_world.y = v76 + v78 + v80 + player->cached_camera_target_world.y;
          skin_hold_ticks = player->damage_gauge.skin_hold_ticks;
          if ( skin_hold_ticks > 0 )
            player->damage_gauge.skin_hold_ticks = skin_hold_ticks - 1;
          if ( player->follow_state.active == 1 )
            p_position->x = v140;
          v82 = player->game->track_center_x * 0.037037037;
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
          if ( *(_DWORD *)player->_pad_360 )
          {
            v84 = *(float *)&player->_pad_360[12] + *(float *)&player->_pad_360[8];
            *(float *)&player->_pad_360[8] = v84;
            if ( v84 > 1.0 )
            {
              *(_DWORD *)&player->_pad_360[8] = 0;
              *(_DWORD *)player->_pad_360 = 0;
            }
          }
          v85 = player->game->track_center_x * 0.022222223;
          *(float *)&player->_pad_374[4] = v85;
          if ( *(float *)player->_pad_374 > 0.0 )
          {
            v86 = v85 + *(float *)player->_pad_374;
            *(float *)player->_pad_374 = v86;
            if ( v86 <= 1.0 )
            {
              update_nuke(&player->nuke);
            }
            else
            {
              *(_DWORD *)player->_pad_374 = 0;
              uninit_nuke(&player->nuke);
            }
          }
          v87 = player->game;
          if ( v87->level_mode == 4 )
          {
            v88 = (char *)v87 + 129728 * v87->level_mode_arg;
            if ( *((_DWORD *)v88 + 2429012) == 1 && !v87->_pad_ff25e0[496] )
            {
              v89 = *(_DWORD *)&v87->_pad_ff25e0[508];
              if ( v89 >= *((_DWORD *)v88 + 2429039) )
                v89 = *((_DWORD *)v88 + 2429039);
              v90 = *(_DWORD *)&player->_pad_2e4[32];
              if ( v90 && (v91 = *((_DWORD *)v88 + 2429021) - v90 + v89) != 0 )
                v92 = convert_math_type16_to_32(*(_WORD *)&v88[6 * v91 + 9716162], 32.0) + flt_643190;
              else
                v92 = convert_math_type16_to_32(*((_WORD *)v88 + 4858081), 32.0);
              flt_643190 = v92;
              if ( player->game->_pad_ff25e0[496] )
                flt_643190 = player->live_matrix.position.z;
              v93 = player->live_matrix.position.z + 20.0;
              if ( flt_643190 >= v93 )
              {
                *(float *)&v124 = v93;
                mark_current_track_pair_with_payload(player, v124);
              }
              else
              {
                mark_current_track_pair_with_payload(player, SLODWORD(flt_643190));
              }
            }
          }
          *(float *)&v119 = player->live_matrix.position.z / (double)player->game->runtime_row_count;
          set_backdrop_progress_fraction((_DWORD *)MEMORY[0x4DF904] + 80644, v119);
          v94 = (double)player->game->completion_row_start - 30.0;
          v125 = player->live_matrix.position.z - 8.0;
          if ( v94 >= v125 )
            v94 = v125;
          cycle_phase_step = player->jetpack_gauge.cycle_phase_step;
          *(float *)&player->_pad_2974[8] = v94;
          if ( LODWORD(cycle_phase_step) == 1 )
          {
            if ( player->live_matrix.position.y < 1.0 )
            {
              v96 = player->velocity.y * 0.89999998;
              player->velocity.y = v96;
              v97 = player->game->track_center_x;
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
              play_voice_manager((int)unk_751498, 3, 0, -1);
              control_override_active = player->control_override_active;
              player->attachment_exit_gate_a = 1;
              if ( !control_override_active && player->live_matrix.position.y < -6.0 )
                dispatch_cutscene_animation((PlayerPresentationController *)&player->interaction_max_z, 5, 1u, -1);
            }
            if ( player->live_matrix.position.y < -7.0 && !player->attachment_exit_gate_b )
            {
              play_voice_manager((int)unk_751498, 1, 2u, -1);
              player->attachment_exit_gate_b = 1;
              player->attachment_exit_gate_a = 1;
            }
          }
          if ( *(float *)&player->_pad_30c[36] > 0.0 )
          {
            v100 = *(float *)&player->_pad_30c[40] + *(float *)&player->_pad_30c[36];
            *(float *)&player->_pad_30c[36] = v100;
            if ( v100 > 1.0 )
            {
              play_voice_manager((int)unk_751498, 7, 2u, -1);
              *(_DWORD *)&player->_pad_30c[36] = 0;
            }
          }
          v101 = player->game;
          v102 = v101->track_center_x * 0.17;
          if ( (v101->track_center_x * 0.5 - v102) * 0.1 + v102 <= player->velocity.z
            || v102 >= player->velocity.z
            || player->attachment_exit_pending
            || player->movement_state == 2 )
          {
            player->squidge.z_phase = 0.0;
          }
          else
          {
            v103 = *((float *)player + 4312) + player->squidge.z_phase;
            player->squidge.z_phase = v103;
            if ( v103 > 1.0 )
            {
              player->squidge.z_phase = 0.0;
              play_voice_manager((int)unk_751498, 6, 1u, -1);
            }
          }
          handle_subgoldy_collisions(player);
          update_anim_manager((AnimationDispatchState *)&player->presentation.owner_player);
          update_anim_manager((AnimationDispatchState *)&player->presentation.jetpack_channel.selected_state);
          update_anim_manager((AnimationDispatchState *)&player->presentation.weapon_channels[0].selected_state);
          update_anim_manager((AnimationDispatchState *)&player->presentation.weapon_channels[1].selected_state);
          update_anim_manager((AnimationDispatchState *)&player->presentation.weapon_channels[2].selected_state);
          update_track_parcels(&player->game->_pad_ff25e0[2539680]);
          initialize_cutscene((PlayerPresentationController *)&player->interaction_max_z);
          update_player_movement_flags((int *)player);
          if ( *((int *)MEMORY[0x4DF904] + 4299517) < 10 )
            player->slow_commentary_step = player->movement_progress;
          v104 = player->game;
          if ( (v104->runtime_flags & 0x400000) == 0 )
            goto LABEL_365;
          if ( LOBYTE(player->completion_handoff_active) )
            goto LABEL_365;
          if ( player->control_override_active )
            goto LABEL_365;
          movement_state = player->movement_state;
          if ( movement_state )
          {
            if ( movement_state != 4 )
              goto LABEL_365;
          }
          if ( player->slow_commentary_step > 0.0 )
          {
            v106 = player->movement_progress + player->slow_commentary_step;
            player->slow_commentary_step = v106;
            if ( v106 > 1.0 )
              player->slow_commentary_step = 0.0;
            goto LABEL_365;
          }
          if ( v104->track_state_latch )
          {
            if ( v104->_pad_ff25e0[496] )
            {
              if ( (*(_BYTE *)(*(_DWORD *)&v104->_pad_ff25e0[500] + 6 * *(_DWORD *)&v104->_pad_ff25e0[508] + 116) & 1) == 0 )
              {
                if ( (*(_BYTE *)(*(_DWORD *)&v104->_pad_ff25e0[500] + 6 * *(_DWORD *)&v104->_pad_ff25e0[508] + 116) & 2) == 0 )
                  goto LABEL_365;
                goto LABEL_364;
              }
              goto LABEL_359;
            }
            if ( (player->control_source->control_flags_a & 0x4000) != 0 )
            {
LABEL_359:
              play_movement_state_sound((int)player);
              update_movement_flag_emitters((char *)player, (int)player);
              player->slow_commentary_step = player->movement_progress + 0.30000001;
              goto LABEL_365;
            }
            if ( (player->control_source->control_flags_b & 0x4000) != 0 )
            {
LABEL_364:
              player->slow_commentary_step = player->movement_progress;
              play_movement_state_sound((int)player);
              update_movement_flag_emitters((char *)player, (int)player);
            }
          }
LABEL_365:
          update_row_event_display((RowEventDisplayController *)&player->game[1]._pad_5c[340]);
          ++*(_DWORD *)&player->game->_pad_a878[16548612];
          ++*(_DWORD *)&player->game->_pad_ff25e0[508];
          v107 = player->game;
          if ( *(_DWORD *)&v107->_pad_ff25e0[508] == 21000 )
            show_times_up_message((int *)&v107[1]._pad_5c[420]);
          update_times_up((int)&player->game[1]._pad_5c[420]);
          return result;
        }
      }
      if ( player->follow_state._pad_3c[0] && LOBYTE(player->completion_handoff_active) )
      {
        *(_DWORD *)player->_pad_2738 = 1134559232;
        player->track_z_offset = 320.0;
      }
      else
      {
        if ( player->control_override_active )
        {
          v12 = *(float *)player->_pad_2738
              - (player->presentation.live_matrix.basis_right.w
               + player->presentation.live_matrix.basis_right.w);
          *(float *)player->_pad_2738 = v12;
          player->track_z_offset = v12;
          if ( *(float *)player->_pad_2738 >= 0.0 )
          {
            if ( *(float *)player->_pad_2738 <= 639.0 )
              steering_x = *(float *)player->_pad_2738;
            else
              steering_x = 639.0;
          }
          else
          {
            steering_x = 0.0;
          }
        }
        else
        {
          resolve_uncaptured_cursor_sensitivity_scale(flt_4DF950[LODWORD(player->cached_camera_target_world.z)]);
          v14 = player->control_source->steering_x - player->track_z_offset + *(float *)player->_pad_2738;
          *(float *)player->_pad_2738 = v14;
          if ( v16 )
          {
            v14 = 0.0;
          }
          else if ( v14 > 639.0 )
          {
            v14 = 639.0;
          }
          *(float *)player->_pad_2738 = v14;
          player->track_z_offset = player->control_source->steering_x;
          if ( LODWORD(player->cached_camera_target_world.z) != 1 )
            goto LABEL_40;
          steering_x = player->control_source->steering_x;
        }
        *(float *)player->_pad_2738 = steering_x;
      }
LABEL_40:
      if ( !LOBYTE(player->completion_handoff_active) )
      {
        v17 = (320.0 - *(float *)player->_pad_2738) * 0.0125;
        if ( v17 >= -3.7 )
        {
          if ( v17 > 3.7 )
            v17 = 3.7;
        }
        else
        {
          v17 = -3.7;
        }
        if ( player->movement_state != 2 )
          player->live_matrix.position.x = player->game->track_center_x * 0.2 * (v17 - player->live_matrix.position.x)
                                         + player->live_matrix.position.x;
      }
      p_position = (Vec3 *)&player->live_matrix.position;
      v18 = convert_math_type32_to_16(player->live_matrix.position.x, 16.0);
      v120 = convert_math_type16_to_32(v18, 16.0);
      player->live_matrix.position.x = v120;
      v19 = player->game;
      *(_WORD *)&v19->_pad_a878[6 * *(_DWORD *)&v19->_pad_ff25e0[508] + 16548616] = convert_math_type32_to_16(
                                                                                      v120,
                                                                                      16.0);
      v20 = player->game;
      if ( *(_DWORD *)&v20->_pad_ff25e0[508] )
      {
        v114 = player->live_matrix.position.z - unk_643194;
        *(_WORD *)&v20->_pad_a878[6 * *(_DWORD *)&v20->_pad_ff25e0[508] + 16548618] = convert_math_type32_to_16(
                                                                                        v114,
                                                                                        32.0);
        v21 = convert_math_type16_to_32(
                *(_WORD *)&player->game->_pad_a878[6 * *(_DWORD *)&player->game->_pad_ff25e0[508] + 16548618],
                32.0)
            + unk_643194;
      }
      else
      {
        *(_WORD *)&v20->_pad_a878[6 * *(_DWORD *)&v20->_pad_ff25e0[508] + 16548618] = convert_math_type32_to_16(
                                                                                        player->live_matrix.position.z,
                                                                                        32.0);
        v21 = convert_math_type16_to_32(
                *(_WORD *)&player->game->_pad_a878[6 * *(_DWORD *)&player->game->_pad_ff25e0[508] + 16548618],
                32.0);
      }
      unk_643194 = v21;
      v22 = player->game;
      if ( v22->track_state_latch )
      {
        if ( (player->control_source->control_flags_a & 0x4000) != 0 )
          v22->_pad_a878[6 * *(_DWORD *)&v22->_pad_ff25e0[508] + 16548620] |= 1u;
        if ( (player->control_source->control_flags_b & 0x4000) != 0 )
          player->game->_pad_a878[6 * *(_DWORD *)&player->game->_pad_ff25e0[508] + 16548620] |= 2u;
      }
      control_source = player->control_source;
      if ( (control_source->control_flags_b & 0x4000) == 0 && (control_source->control_flags_a & 0x4000) == 0 )
        player->game->track_state_latch = 1;
      v24 = player->game;
      if ( v24->track_state_latch )
        v24->_pad_a878[6 * *(_DWORD *)&v24->_pad_ff25e0[508] + 16548620] |= 4u;
      goto LABEL_60;
    }
  }
  return result;
}
