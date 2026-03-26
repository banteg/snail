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
  player->_pad_29ac[6412] = 0;
  *((_DWORD *)player->game + 4835835) = 0;
  *(_DWORD *)&player->_pad_29ac[4796] = 0;
  *(_DWORD *)&player->_pad_29ac[1832] = 0;
  *(_DWORD *)&player->_pad_29ac[2820] = 0;
  *(_DWORD *)&player->_pad_29ac[3808] = 0;
  player->cutscene_pitch_cycle = 0.0;
  player->cutscene_pitch_cycle_step = 0.0;
  sub_41AA30(&player->snail_visual->follow_lateral_response);
  player->interaction_max_z = -19.0;
  player->movement_sound_variant_sample = 0;
  *(_DWORD *)&player->_pad_29ac[6404] = 0;
  *(_DWORD *)&player->_pad_29ac[6408] = 1015580809;
  *((_DWORD *)player + 4311) = 0;
  *((_DWORD *)player + 4312) = 1015580809;
  initialize_score_stats(&player->squidge.y_output);
  initialize_invincible_shell(&player->_pad_29ac[6252]);
  *(_DWORD *)&player->_pad_30c[40] = 1029934648;
  *(_DWORD *)&player->_pad_30c[36] = 1029934648;
  player->attachment_exit_progress = 0.0;
  player->attachment_exit_progress_step = 0.016666668;
  if ( (*(_DWORD *)&player->snail_visual->_pad_00[16] & 0x200000) != 0 )
  {
    v3 = *(_DWORD *)&player->_pad_2984[4];
    BYTE1(v3) |= 8u;
    *(_DWORD *)&player->_pad_2984[4] = v3;
    *(_DWORD *)&player->_pad_29ac[80] = &player->_pad_29ac[220];
    initialize_anim_manager(&player->_pad_29ac[220]);
    *(_DWORD *)&player->_pad_29ac[220] = 1;
    *(_DWORD *)&player->_pad_29ac[284] = player->_pad_2984;
    *(_DWORD *)&player->_pad_29ac[288] = &player->_pad_29ac[292];
    *(_DWORD *)&player->_pad_29ac[280] = 0;
  }
  else
  {
    initialize_anim_manager(&player->_pad_29ac[220]);
    *(_DWORD *)&player->_pad_29ac[220] = 0;
  }
  if ( (*(_DWORD *)(*(_DWORD *)&player->_pad_29ac[4572] + 16) & 0x200000) != 0 )
  {
    v4 = *(_DWORD *)&player->_pad_29ac[4540] & 0xFFFFFFDF;
    BYTE1(v4) |= 8u;
    *(_DWORD *)&player->_pad_29ac[4540] = v4;
    *(_DWORD *)&player->_pad_29ac[4796] = 0;
    *(_DWORD *)&player->_pad_29ac[4656] = &player->_pad_29ac[4800];
    initialize_anim_manager(&player->_pad_29ac[4800]);
    *(_DWORD *)&player->_pad_29ac[4800] = 1;
    *(_DWORD *)&player->_pad_29ac[4864] = &player->_pad_29ac[4536];
    *(_DWORD *)&player->_pad_29ac[4868] = &player->_pad_29ac[4872];
    *(_DWORD *)&player->_pad_29ac[4860] = 0;
  }
  else
  {
    initialize_anim_manager(&player->_pad_29ac[4800]);
    *(_DWORD *)&player->_pad_29ac[4800] = 0;
  }
  if ( (*(_DWORD *)(*(_DWORD *)&player->_pad_29ac[1608] + 16) & 0x200000) != 0 )
  {
    v5 = *(_DWORD *)&player->_pad_29ac[1576] & 0xFFFFFFDF;
    BYTE1(v5) |= 8u;
    *(_DWORD *)&player->_pad_29ac[1576] = v5;
    *(_DWORD *)&player->_pad_29ac[1832] = 0;
    *(_DWORD *)&player->_pad_29ac[1692] = &player->_pad_29ac[1836];
    initialize_anim_manager(&player->_pad_29ac[1836]);
    *(_DWORD *)&player->_pad_29ac[1836] = 1;
    *(_DWORD *)&player->_pad_29ac[1900] = &player->_pad_29ac[1572];
    *(_DWORD *)&player->_pad_29ac[1904] = &player->_pad_29ac[1908];
    *(_DWORD *)&player->_pad_29ac[1896] = 0;
  }
  else
  {
    initialize_anim_manager(&player->_pad_29ac[1836]);
    *(_DWORD *)&player->_pad_29ac[1836] = 0;
  }
  if ( (*(_DWORD *)(*(_DWORD *)&player->_pad_29ac[2596] + 16) & 0x200000) != 0 )
  {
    v6 = *(_DWORD *)&player->_pad_29ac[2564];
    LOBYTE(v6) = v6 & 0xDF;
    BYTE1(v6) |= 8u;
    *(_DWORD *)&player->_pad_29ac[2564] = v6;
    *(_DWORD *)&player->_pad_29ac[2820] = 0;
    *(_DWORD *)&player->_pad_29ac[2680] = &player->_pad_29ac[2824];
    initialize_anim_manager(&player->_pad_29ac[2824]);
    *(_DWORD *)&player->_pad_29ac[2824] = 1;
    *(_DWORD *)&player->_pad_29ac[2888] = &player->_pad_29ac[2560];
    *(_DWORD *)&player->_pad_29ac[2892] = &player->_pad_29ac[2896];
    *(_DWORD *)&player->_pad_29ac[2884] = 0;
  }
  else
  {
    initialize_anim_manager(&player->_pad_29ac[2824]);
    *(_DWORD *)&player->_pad_29ac[2824] = 0;
  }
  if ( (*(_DWORD *)(*(_DWORD *)&player->_pad_29ac[3584] + 16) & 0x200000) != 0 )
  {
    v7 = *(_DWORD *)&player->_pad_29ac[3552] & 0xFFFFFFDF;
    BYTE1(v7) |= 8u;
    *(_DWORD *)&player->_pad_29ac[3552] = v7;
    *(_DWORD *)&player->_pad_29ac[3808] = 0;
    *(_DWORD *)&player->_pad_29ac[3668] = &player->_pad_29ac[3812];
    initialize_anim_manager(&player->_pad_29ac[3812]);
    *(_DWORD *)&player->_pad_29ac[3812] = 1;
    *(_DWORD *)&player->_pad_29ac[3876] = &player->_pad_29ac[3548];
    *(_DWORD *)&player->_pad_29ac[3880] = &player->_pad_29ac[3884];
    *(_DWORD *)&player->_pad_29ac[3872] = 0;
  }
  else
  {
    initialize_anim_manager(&player->_pad_29ac[3812]);
    *(_DWORD *)&player->_pad_29ac[3812] = 0;
  }
  initialize_snail_skin(&player->_pad_29ac[6416]);
  initialize_cutscene_ai(&player->_pad_29ac[6448]);
  if ( !*((_BYTE *)player->game + 16721360) )
    *(_DWORD *)&player->_pad_29ac[6460] = 1;
  *(_DWORD *)&player->_pad_29ac[216] = player;
  set_matrix_identity((TransformMatrix *)&player->_pad_29ac[16]);
  set_matrix_identity((TransformMatrix *)&player->_pad_29ac[152]);
  set_matrix_identity((TransformMatrix *)&player->_pad_29ac[88]);
  *(_DWORD *)&player->_pad_29ac[6540] = 0;
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
  *(_DWORD *)&player->_pad_29ac[5524] = 0;
  *(_DWORD *)&player->_pad_29ac[5528] = 1002197604;
  *(_DWORD *)&player->_pad_29ac[5532] = 0;
  *(_DWORD *)&player->_pad_29ac[5536] = 1004405091;
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

