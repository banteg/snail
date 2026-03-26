/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_subgoldy @ 0x43a9c0 */
/* selector: initialize_subgoldy */

// Initializes the live Goldy actor for a new run: resets movement and follow state, seeds the animation managers and cutscene block, initializes the jetpack gauge, cameraman, and click-start prompt, and wires the actor back to the active Game. Cross-port Android and iOS symbols match this helper to `cRSubGoldy::Init(int)`.
int32_t __thiscall initialize_subgoldy(Player *player, int32_t player_slot)
{
  int v3; // eax
  unsigned int v4; // ecx
  unsigned int v5; // edx
  int v6; // eax
  unsigned int v7; // ecx
  float z; // ecx
  PlayerControlSource *v9; // eax
  uint8_t *v10; // edi
  int v11; // ebp
  int32_t result; // eax
  int32_t v13; // [esp-4h] [ebp-14h]

  player->player_slot = player_slot;
  player->game = (Game *)((char *)MEMORY[0x4DF904] + 476696);
  player->heading_roll = 0.0;
  player->row_event.id = 0;
  player->control_override_active = 0;
  player->nuke.owner_player = player;
  player->nuke.state = 0;
  player->row_event_cutscene_started = 0;
  *(_DWORD *)&player->_pad_78[20] = 0;
  player->completion_handoff_timer = 0.0;
  player->movement_flags = 0;
  player->previous_movement_flags = -1;
  player->_pad_1e4[0] = 0;
  player->presentation.invincible_shell._pad_90[8] = 0;
  *(_DWORD *)&player->game[1]._pad_5c[360] = 0;
  *(_DWORD *)&player->presentation.jetpack_channel._pad_7c[132] = 0;
  *(_DWORD *)&player->presentation.weapon_channels[0]._pad_7c[132] = 0;
  *(_DWORD *)&player->presentation.weapon_channels[1]._pad_7c[132] = 0;
  *(_DWORD *)&player->presentation.weapon_channels[2]._pad_7c[132] = 0;
  player->cutscene_pitch_cycle = 0.0;
  player->cutscene_pitch_cycle_step = 0.0;
  sub_41AA30((_DWORD *)(*(_DWORD *)&player->presentation._pad_08[24] + 128));
  *(_DWORD *)&player->_pad_2974[8] = -1047003136;
  player->movement_sound_variant_sample = 0;
  *(_DWORD *)player->presentation.invincible_shell._pad_90 = 0;
  *(_DWORD *)&player->presentation.invincible_shell._pad_90[4] = 1015580809;
  player->squidge.z_velocity = 0.0;
  player->squidge.z_phase = 0.016666668;
  initialize_score_stats(&player->presentation.cutscene_ai._pad_59[7]);
  initialize_invincible_shell((InvincibleShellController *)&player->presentation.snail_hotspots_world[18].z);
  *(_DWORD *)&player->_pad_30c[40] = 1029934648;
  *(_DWORD *)&player->_pad_30c[36] = 1029934648;
  player->attachment_exit_progress = 0.0;
  player->attachment_exit_progress_step = 0.016666668;
  if ( (*(_DWORD *)(*(_DWORD *)&player->presentation._pad_08[24] + 16) & 0x200000) != 0 )
  {
    v3 = *(_DWORD *)player->presentation._pad_00;
    BYTE1(v3) |= 8u;
    *(_DWORD *)player->presentation._pad_00 = v3;
    LODWORD(player->presentation.live_matrix.position.w) = &player->presentation.owner_player;
    initialize_anim_manager((AnimationDispatchState *)&player->presentation.owner_player);
    player->presentation.owner_player = (Player *)1;
    player->presentation.anim_manager.queued_animation_count = (int32_t)&player->interaction_max_z;
    player->presentation.anim_manager.self_ref = &player->presentation.anim_manager.queue_sentinel;
    player->presentation.anim_manager.queued_animation_ids[9] = 0;
  }
  else
  {
    initialize_anim_manager((AnimationDispatchState *)&player->presentation.owner_player);
    player->presentation.owner_player = nullptr;
  }
  if ( (*(_DWORD *)(*(_DWORD *)&player->presentation.jetpack_channel._pad_08[24] + 16) & 0x200000) != 0 )
  {
    v4 = *(_DWORD *)player->presentation.jetpack_channel._pad_00 & 0xFFFFFFDF;
    BYTE1(v4) |= 8u;
    *(_DWORD *)player->presentation.jetpack_channel._pad_00 = v4;
    *(_DWORD *)&player->presentation.jetpack_channel._pad_7c[132] = 0;
    LODWORD(player->presentation.jetpack_channel.live_matrix.position.w) = &player->presentation.jetpack_channel.selected_state;
    initialize_anim_manager((AnimationDispatchState *)&player->presentation.jetpack_channel.selected_state);
    player->presentation.jetpack_channel.selected_state = 1;
    player->presentation.jetpack_channel.anim_manager.queued_animation_count = (int32_t)&player->presentation.weapon_channels[2].release_step.z;
    player->presentation.jetpack_channel.anim_manager.self_ref = &player->presentation.jetpack_channel.anim_manager.queue_sentinel;
    player->presentation.jetpack_channel.anim_manager.queued_animation_ids[9] = 0;
  }
  else
  {
    initialize_anim_manager((AnimationDispatchState *)&player->presentation.jetpack_channel.selected_state);
    player->presentation.jetpack_channel.selected_state = 0;
  }
  if ( (*(_DWORD *)(*(_DWORD *)&player->presentation.weapon_channels[0]._pad_08[24] + 16) & 0x200000) != 0 )
  {
    v5 = *(_DWORD *)player->presentation.weapon_channels[0]._pad_00 & 0xFFFFFFDF;
    BYTE1(v5) |= 8u;
    *(_DWORD *)player->presentation.weapon_channels[0]._pad_00 = v5;
    *(_DWORD *)&player->presentation.weapon_channels[0]._pad_7c[132] = 0;
    LODWORD(player->presentation.weapon_channels[0].live_matrix.position.w) = &player->presentation.weapon_channels[0].selected_state;
    initialize_anim_manager((AnimationDispatchState *)&player->presentation.weapon_channels[0].selected_state);
    player->presentation.weapon_channels[0].selected_state = 1;
    player->presentation.weapon_channels[0].anim_manager.queued_animation_count = (int32_t)&player->presentation._pad_14c[1276];
    player->presentation.weapon_channels[0].anim_manager.self_ref = &player->presentation.weapon_channels[0].anim_manager.queue_sentinel;
    player->presentation.weapon_channels[0].anim_manager.queued_animation_ids[9] = 0;
  }
  else
  {
    initialize_anim_manager((AnimationDispatchState *)&player->presentation.weapon_channels[0].selected_state);
    player->presentation.weapon_channels[0].selected_state = 0;
  }
  if ( (*(_DWORD *)(*(_DWORD *)&player->presentation.weapon_channels[1]._pad_08[24] + 16) & 0x200000) != 0 )
  {
    v6 = *(_DWORD *)player->presentation.weapon_channels[1]._pad_00;
    LOBYTE(v6) = v6 & 0xDF;
    BYTE1(v6) |= 8u;
    *(_DWORD *)player->presentation.weapon_channels[1]._pad_00 = v6;
    *(_DWORD *)&player->presentation.weapon_channels[1]._pad_7c[132] = 0;
    LODWORD(player->presentation.weapon_channels[1].live_matrix.position.w) = &player->presentation.weapon_channels[1].selected_state;
    initialize_anim_manager((AnimationDispatchState *)&player->presentation.weapon_channels[1].selected_state);
    player->presentation.weapon_channels[1].selected_state = 1;
    player->presentation.weapon_channels[1].anim_manager.queued_animation_count = (int32_t)&player->presentation.weapon_channels[0].release_step.z;
    player->presentation.weapon_channels[1].anim_manager.self_ref = &player->presentation.weapon_channels[1].anim_manager.queue_sentinel;
    player->presentation.weapon_channels[1].anim_manager.queued_animation_ids[9] = 0;
  }
  else
  {
    initialize_anim_manager((AnimationDispatchState *)&player->presentation.weapon_channels[1].selected_state);
    player->presentation.weapon_channels[1].selected_state = 0;
  }
  if ( (*(_DWORD *)(*(_DWORD *)&player->presentation.weapon_channels[2]._pad_08[24] + 16) & 0x200000) != 0 )
  {
    v7 = *(_DWORD *)player->presentation.weapon_channels[2]._pad_00 & 0xFFFFFFDF;
    BYTE1(v7) |= 8u;
    *(_DWORD *)player->presentation.weapon_channels[2]._pad_00 = v7;
    *(_DWORD *)&player->presentation.weapon_channels[2]._pad_7c[132] = 0;
    LODWORD(player->presentation.weapon_channels[2].live_matrix.position.w) = &player->presentation.weapon_channels[2].selected_state;
    initialize_anim_manager((AnimationDispatchState *)&player->presentation.weapon_channels[2].selected_state);
    player->presentation.weapon_channels[2].selected_state = 1;
    player->presentation.weapon_channels[2].anim_manager.queued_animation_count = (int32_t)&player->presentation.weapon_channels[1].release_step.z;
    player->presentation.weapon_channels[2].anim_manager.self_ref = &player->presentation.weapon_channels[2].anim_manager.queue_sentinel;
    player->presentation.weapon_channels[2].anim_manager.queued_animation_ids[9] = 0;
  }
  else
  {
    initialize_anim_manager((AnimationDispatchState *)&player->presentation.weapon_channels[2].selected_state);
    player->presentation.weapon_channels[2].selected_state = 0;
  }
  initialize_snail_skin((SnailSkinTransitionState *)&player->presentation.invincible_shell._pad_90[12]);
  initialize_cutscene_ai((CutsceneAI *)&player->presentation.snail_skin_transition.progress);
  if ( !player->game->_pad_ff25e0[496] )
    player->presentation.cutscene_ai.player = (Player *)1;
  *(_DWORD *)&player->presentation._pad_c0[60] = player;
  set_matrix_identity((TransformMatrix *)&player->presentation._pad_28[12]);
  set_matrix_identity((TransformMatrix *)&player->presentation.previous_live_matrix.position.w);
  set_matrix_identity((TransformMatrix *)&player->presentation._pad_78[4]);
  player->presentation.cutscene_ai.progress_step = 0.0;
  initialize_click_start((int)player->_pad_a0, (int)player);
  initialize_cameraman((CameramanState *)player->_pad_200);
  initialize_subgoldy_ghost(player, player->player_slot);
  player->damage_retrigger_step = 0.05050505;
  player->surface_reaction_step = 0.05050505;
  player->live_matrix.position.x = 0.0;
  player->live_matrix.position.y = 0.0;
  player->jetpack_gauge.warning_intensity = 0.0;
  player->live_matrix.position.z = 4.0;
  z = player->live_matrix.position.z;
  *(_DWORD *)&player->_pad_374[8] = 0;
  player->cached_camera_target_world.x = 0.0;
  *(_DWORD *)&player->_pad_30c[28] = 0;
  *(_DWORD *)&player->_pad_30c[32] = 1015580809;
  player->damage_retrigger_timer = 0.0;
  player->surface_reaction_timer = 0.0;
  player->presentation.jetpack_channel.release_step.z = 0.0;
  player->presentation.wobble.roll_phase = 0.0057471264;
  player->presentation.wobble.roll_phase_step = 0.0;
  player->presentation.wobble.lift_phase = 0.0067750677;
  player->_pad_78[12] = 0;
  player->cached_camera_target_world.y = z;
  player->velocity.z = 0.0;
  player->velocity.y = 0.0;
  player->velocity.x = 0.0;
  if ( player->player_slot != 1 )
  {
    if ( MEMORY[0x4DF904] != (void *)-180 )
    {
      v9 = (PlayerControlSource *)((char *)MEMORY[0x4DF904] + 236);
      goto LABEL_24;
    }
LABEL_23:
    v9 = nullptr;
    goto LABEL_24;
  }
  if ( MEMORY[0x4DF904] == (void *)-68 )
    goto LABEL_23;
  v9 = (PlayerControlSource *)((char *)MEMORY[0x4DF904] + 124);
LABEL_24:
  player->control_source = v9;
  player->slow_commentary_step = 0.0;
  LOBYTE(player->completion_handoff_active) = 0;
  player->movement_rate_scalar = 0.0;
  initialize_damage_gauge(&player->damage_gauge.state);
  noop_runtime_ai();
  player->follow_state.active = 0;
  v10 = &player->_pad_44f[453];
  v11 = 12;
  do
  {
    *((_DWORD *)v10 + 32) = 0;
    set_matrix_identity((TransformMatrix *)v10);
    *((_DWORD *)v10 + 43) = player->game;
    v10 += 744;
    --v11;
  }
  while ( v11 );
  v13 = player->player_slot;
  *(_DWORD *)&player->_pad_00[4] |= 0x20u;
  player->track_z_anchor = 0.0;
  *(_DWORD *)player->_pad_2744 = 1045779798;
  *(_DWORD *)&player->_pad_2744[4] = 0;
  result = initialize_jetpack_gauge(&player->_pad_2744[8], v13);
  player->lane_lean_state = 0;
  player->lane_lean_amplitude = 0.0;
  player->lane_lean_progress = 0.0;
  player->lane_lean_progress_step = 0.0;
  *(_DWORD *)player->_pad_360 = 0;
  *(_DWORD *)&player->_pad_360[4] = 0;
  *(_DWORD *)&player->_pad_360[8] = 0;
  *(_DWORD *)&player->_pad_360[12] = 0;
  *(_DWORD *)player->_pad_374 = 0;
  *(_DWORD *)&player->_pad_374[4] = 0;
  player->attachment_exit_pending = 0;
  player->_pad_41c[0] = 0;
  *(_DWORD *)&player->_pad_3f0[20] = 0;
  player->game->_pad_00[1] = 1;
  return result;
}

