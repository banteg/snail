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
  *(_DWORD *)&player->_pad_74[24] = 0;
  player->completion_handoff_timer = 0.0;
  player->movement_flags = 0;
  player->previous_movement_flags = -1;
  player->_pad_1e4[0] = 0;
  player->presentation._pad_144[6128] = 0;
  *((_DWORD *)player->game + 4835835) = 0;
  *(_DWORD *)&player->presentation._pad_144[4512] = 0;
  *(_DWORD *)&player->presentation._pad_144[1548] = 0;
  *(_DWORD *)&player->presentation._pad_144[2536] = 0;
  *(_DWORD *)&player->presentation._pad_144[3524] = 0;
  player->cutscene_pitch_cycle = 0.0;
  player->cutscene_pitch_cycle_step = 0.0;
  sub_41AA30(&player->presentation.visual_root->follow_lateral_response);
  player->interaction_max_z = -19.0;
  player->movement_sound_variant_sample = 0;
  *(_DWORD *)&player->presentation._pad_144[6120] = 0;
  *(_DWORD *)&player->presentation._pad_144[6124] = 1015580809;
  *((_DWORD *)player + 4311) = 0;
  *((_DWORD *)player + 4312) = 1015580809;
  initialize_score_stats(&player->squidge.y_output);
  initialize_invincible_shell(&player->presentation._pad_144[5968]);
  *(_DWORD *)&player->_pad_30c[40] = 1029934648;
  *(_DWORD *)&player->_pad_30c[36] = 1029934648;
  player->attachment_exit_progress = 0.0;
  player->attachment_exit_progress_step = 0.016666668;
  if ( (player->presentation.visual_root->flags & 0x200000) != 0 )
  {
    v3 = *(_DWORD *)&player->presentation._pad_00[4];
    BYTE1(v3) |= 8u;
    *(_DWORD *)&player->presentation._pad_00[4] = v3;
    *(_DWORD *)player->presentation._pad_78 = player->presentation._pad_104;
    initialize_anim_manager(player->presentation._pad_104);
    *(_DWORD *)player->presentation._pad_104 = 1;
    *(_DWORD *)player->presentation._pad_144 = &player->presentation;
    *(_DWORD *)&player->presentation._pad_144[4] = &player->presentation._pad_144[8];
    player->presentation.queued_animation_count = 0;
  }
  else
  {
    initialize_anim_manager(player->presentation._pad_104);
    *(_DWORD *)player->presentation._pad_104 = 0;
  }
  if ( (*(_DWORD *)(*(_DWORD *)&player->presentation._pad_144[4288] + 16) & 0x200000) != 0 )
  {
    v4 = *(_DWORD *)&player->presentation._pad_144[4256] & 0xFFFFFFDF;
    BYTE1(v4) |= 8u;
    *(_DWORD *)&player->presentation._pad_144[4256] = v4;
    *(_DWORD *)&player->presentation._pad_144[4512] = 0;
    *(_DWORD *)&player->presentation._pad_144[4372] = &player->presentation._pad_144[4516];
    initialize_anim_manager(&player->presentation._pad_144[4516]);
    *(_DWORD *)&player->presentation._pad_144[4516] = 1;
    *(_DWORD *)&player->presentation._pad_144[4580] = &player->presentation._pad_144[4252];
    *(_DWORD *)&player->presentation._pad_144[4584] = &player->presentation._pad_144[4588];
    *(_DWORD *)&player->presentation._pad_144[4576] = 0;
  }
  else
  {
    initialize_anim_manager(&player->presentation._pad_144[4516]);
    *(_DWORD *)&player->presentation._pad_144[4516] = 0;
  }
  if ( (*(_DWORD *)(*(_DWORD *)&player->presentation._pad_144[1324] + 16) & 0x200000) != 0 )
  {
    v5 = *(_DWORD *)&player->presentation._pad_144[1292] & 0xFFFFFFDF;
    BYTE1(v5) |= 8u;
    *(_DWORD *)&player->presentation._pad_144[1292] = v5;
    *(_DWORD *)&player->presentation._pad_144[1548] = 0;
    *(_DWORD *)&player->presentation._pad_144[1408] = &player->presentation._pad_144[1552];
    initialize_anim_manager(&player->presentation._pad_144[1552]);
    *(_DWORD *)&player->presentation._pad_144[1552] = 1;
    *(_DWORD *)&player->presentation._pad_144[1616] = &player->presentation._pad_144[1288];
    *(_DWORD *)&player->presentation._pad_144[1620] = &player->presentation._pad_144[1624];
    *(_DWORD *)&player->presentation._pad_144[1612] = 0;
  }
  else
  {
    initialize_anim_manager(&player->presentation._pad_144[1552]);
    *(_DWORD *)&player->presentation._pad_144[1552] = 0;
  }
  if ( (*(_DWORD *)(*(_DWORD *)&player->presentation._pad_144[2312] + 16) & 0x200000) != 0 )
  {
    v6 = *(_DWORD *)&player->presentation._pad_144[2280];
    LOBYTE(v6) = v6 & 0xDF;
    BYTE1(v6) |= 8u;
    *(_DWORD *)&player->presentation._pad_144[2280] = v6;
    *(_DWORD *)&player->presentation._pad_144[2536] = 0;
    *(_DWORD *)&player->presentation._pad_144[2396] = &player->presentation._pad_144[2540];
    initialize_anim_manager(&player->presentation._pad_144[2540]);
    *(_DWORD *)&player->presentation._pad_144[2540] = 1;
    *(_DWORD *)&player->presentation._pad_144[2604] = &player->presentation._pad_144[2276];
    *(_DWORD *)&player->presentation._pad_144[2608] = &player->presentation._pad_144[2612];
    *(_DWORD *)&player->presentation._pad_144[2600] = 0;
  }
  else
  {
    initialize_anim_manager(&player->presentation._pad_144[2540]);
    *(_DWORD *)&player->presentation._pad_144[2540] = 0;
  }
  if ( (*(_DWORD *)(*(_DWORD *)&player->presentation._pad_144[3300] + 16) & 0x200000) != 0 )
  {
    v7 = *(_DWORD *)&player->presentation._pad_144[3268] & 0xFFFFFFDF;
    BYTE1(v7) |= 8u;
    *(_DWORD *)&player->presentation._pad_144[3268] = v7;
    *(_DWORD *)&player->presentation._pad_144[3524] = 0;
    *(_DWORD *)&player->presentation._pad_144[3384] = &player->presentation._pad_144[3528];
    initialize_anim_manager(&player->presentation._pad_144[3528]);
    *(_DWORD *)&player->presentation._pad_144[3528] = 1;
    *(_DWORD *)&player->presentation._pad_144[3592] = &player->presentation._pad_144[3264];
    *(_DWORD *)&player->presentation._pad_144[3596] = &player->presentation._pad_144[3600];
    *(_DWORD *)&player->presentation._pad_144[3588] = 0;
  }
  else
  {
    initialize_anim_manager(&player->presentation._pad_144[3528]);
    *(_DWORD *)&player->presentation._pad_144[3528] = 0;
  }
  initialize_snail_skin(&player->presentation._pad_144[6132]);
  initialize_cutscene_ai(&player->presentation.cutscene_ai);
  if ( !*((_BYTE *)player->game + 16721360) )
    player->presentation.cutscene_ai.active = 1;
  player->presentation.owner_player = player;
  set_matrix_identity(&player->presentation.live_matrix);
  set_matrix_identity(&player->presentation.previous_live_matrix);
  set_matrix_identity((TransformMatrix *)&player->presentation._pad_78[8]);
  *(_DWORD *)&player->presentation.cutscene_ai._pad_10[76] = 0;
  initialize_click_start((int)player->_pad_a0, (int)player);
  initialize_cameraman((CameramanState *)player->_pad_200);
  initialize_subgoldy_ghost(player, player->player_slot);
  player->damage_retrigger_step = 0.05050505;
  player->surface_reaction_step = 0.05050505;
  player->position.x = 0.0;
  player->position.y = 0.0;
  player->cached_camera_target_world.x = 0.0;
  player->position.z = 4.0;
  z = player->position.z;
  *(_DWORD *)&player->_pad_374[8] = 0;
  player->cached_camera_target_world.y = 0.0;
  *(_DWORD *)&player->_pad_30c[28] = 0;
  *(_DWORD *)&player->_pad_30c[32] = 1015580809;
  player->damage_retrigger_timer = 0.0;
  player->surface_reaction_timer = 0.0;
  *(_DWORD *)&player->presentation._pad_144[5240] = 0;
  *(_DWORD *)&player->presentation._pad_144[5244] = 1002197604;
  *(_DWORD *)&player->presentation._pad_144[5248] = 0;
  *(_DWORD *)&player->presentation._pad_144[5252] = 1004405091;
  player->_pad_74[16] = 0;
  player->cached_camera_target_world.z = z;
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
  player->movement_progress = 0.0;
  LOBYTE(player->completion_handoff_active) = 0;
  *(_DWORD *)player->_pad_2738 = 0;
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
  *(_DWORD *)player->_pad_2744 = 0;
  *(_DWORD *)&player->_pad_2744[4] = 1045779798;
  *(_DWORD *)&player->_pad_2744[8] = 0;
  result = initialize_jetpack_gauge(&player->jetpack_gauge.progress, v13);
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
  *((_BYTE *)player->game + 1) = 1;
  return result;
}

