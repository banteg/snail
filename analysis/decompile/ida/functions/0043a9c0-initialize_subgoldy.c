/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_subgoldy @ 0x43a9c0 */
/* selector: initialize_subgoldy */

// Authored void `cRSubGoldy::Init(int)`: initializes the SubgameRuntime-owned Goldy actor, including movement/follow state, animation and cutscene owners, cached camera target, exact cRSubHover child, cameraman, and click-start prompt. It binds each animated Snail/weapon BOD to its own AnimManager and owned donor-slot bank for render-time ObjectAnimation progress synchronization; Android and iOS retain the method.
void __thiscall initialize_subgoldy(Player *player, int32_t player_slot)
{
  uint32_t list_flags; // eax
  uint32_t v4; // ecx
  uint32_t v5; // edx
  uint32_t v6; // eax
  uint32_t v7; // ecx
  float z; // ecx
  PlayerControlSource *p_input; // eax
  TransformMatrix *p_flight_transform; // edi
  int v11; // ebp
  int32_t v12; // [esp-4h] [ebp-14h]

  player->player_slot = player_slot;
  player->game = &g_game_base->subgame;
  player->heading_roll = 0.0;
  player->row_event.id = 0;
  player->control_override_active = 0;
  player->nuke.owner_player = player;
  player->nuke.state = NUKE_STATE_INACTIVE;
  player->row_event_cutscene_started = 0;
  player->resurrect_progress = 0.0;
  player->completion_handoff_timer = 0.0;
  player->movement_flags = 0;
  player->previous_movement_flags = -1;
  player->trampoline_bounce_active = 0;
  player->presentation.invincible_shell.channel_release_steps_active = 0;
  player->game->completion.state = COMPLETION_STATE_INACTIVE;
  player->presentation.jetpack_channel.selected_state = 0;
  player->presentation.weapon_channels[0].selected_state = 0;
  player->presentation.weapon_channels[1].selected_state = 0;
  player->presentation.weapon_channels[2].selected_state = 0;
  player->cutscene_pitch_cycle = 0.0;
  player->cutscene_pitch_cycle_step = 0.0;
  initialize_object_distort(&player->presentation.body.bod.object->distort.z_wave);
  player->interaction_max_z = -19.0;
  player->movement_sound_variant_sample = 0;
  player->presentation.invincible_shell.cutscene_roll_progress = 0.0;
  player->presentation.invincible_shell.cutscene_roll_step = 0.016666668;
  player->slow_commentary_timer = 0.0;
  player->slow_commentary_step = 0.016666668;
  initialize_score_stats(&player->squidge);
  initialize_invincible_shell(&player->presentation.invincible_shell);
  player->startup_voice_step = 0.055555552;
  player->startup_voice_timer = 0.055555552;
  player->attachment_exit_progress = 0.0;
  player->attachment_exit_progress_step = 0.016666668;
  if ( (player->presentation.body.bod.object->flags & 0x200000) != 0 )
  {
    list_flags = player->presentation.body.bod.bod.list_flags;
    BYTE1(list_flags) |= 8u;
    player->presentation.body.bod.bod.list_flags = list_flags;
    player->presentation.body.render_animation_manager = &player->presentation.anim_manager;
    initialize_anim_manager(&player->presentation.anim_manager);
    player->presentation.anim_manager.state = 1;
    player->presentation.anim_manager.target_model = &player->presentation.body;
    player->presentation.anim_manager.animation_slots = player->presentation.cutscene_animation_slots;
    player->presentation.anim_manager.queue_count = 0;
  }
  else
  {
    initialize_anim_manager(&player->presentation.anim_manager);
    player->presentation.anim_manager.state = 0;
  }
  if ( (player->presentation.jetpack_channel.body.bod.object->flags & 0x200000) != 0 )
  {
    v4 = player->presentation.jetpack_channel.body.bod.bod.list_flags & 0xFFFFFFDF;
    BYTE1(v4) |= 8u;
    player->presentation.jetpack_channel.body.bod.bod.list_flags = v4;
    player->presentation.jetpack_channel.selected_state = 0;
    player->presentation.jetpack_channel.body.render_animation_manager = &player->presentation.jetpack_channel.anim_manager;
    initialize_anim_manager(&player->presentation.jetpack_channel.anim_manager);
    player->presentation.jetpack_channel.anim_manager.state = 1;
    player->presentation.jetpack_channel.anim_manager.target_model = &player->presentation.jetpack_channel.body;
    player->presentation.jetpack_channel.anim_manager.animation_slots = player->presentation.jetpack_channel.animation_slots;
    player->presentation.jetpack_channel.anim_manager.queue_count = 0;
  }
  else
  {
    initialize_anim_manager(&player->presentation.jetpack_channel.anim_manager);
    player->presentation.jetpack_channel.anim_manager.state = 0;
  }
  if ( (player->presentation.weapon_channels[0].body.bod.object->flags & 0x200000) != 0 )
  {
    v5 = player->presentation.weapon_channels[0].body.bod.bod.list_flags & 0xFFFFFFDF;
    BYTE1(v5) |= 8u;
    player->presentation.weapon_channels[0].body.bod.bod.list_flags = v5;
    player->presentation.weapon_channels[0].selected_state = 0;
    player->presentation.weapon_channels[0].body.render_animation_manager = &player->presentation.weapon_channels[0].anim_manager;
    initialize_anim_manager(&player->presentation.weapon_channels[0].anim_manager);
    player->presentation.weapon_channels[0].anim_manager.state = 1;
    player->presentation.weapon_channels[0].anim_manager.target_model = &player->presentation.weapon_channels[0].body;
    player->presentation.weapon_channels[0].anim_manager.animation_slots = player->presentation.weapon_channels[0].animation_slots;
    player->presentation.weapon_channels[0].anim_manager.queue_count = 0;
  }
  else
  {
    initialize_anim_manager(&player->presentation.weapon_channels[0].anim_manager);
    player->presentation.weapon_channels[0].anim_manager.state = 0;
  }
  if ( (player->presentation.weapon_channels[1].body.bod.object->flags & 0x200000) != 0 )
  {
    v6 = player->presentation.weapon_channels[1].body.bod.bod.list_flags;
    LOBYTE(v6) = v6 & 0xDF;
    BYTE1(v6) |= 8u;
    player->presentation.weapon_channels[1].body.bod.bod.list_flags = v6;
    player->presentation.weapon_channels[1].selected_state = 0;
    player->presentation.weapon_channels[1].body.render_animation_manager = &player->presentation.weapon_channels[1].anim_manager;
    initialize_anim_manager(&player->presentation.weapon_channels[1].anim_manager);
    player->presentation.weapon_channels[1].anim_manager.state = 1;
    player->presentation.weapon_channels[1].anim_manager.target_model = &player->presentation.weapon_channels[1].body;
    player->presentation.weapon_channels[1].anim_manager.animation_slots = player->presentation.weapon_channels[1].animation_slots;
    player->presentation.weapon_channels[1].anim_manager.queue_count = 0;
  }
  else
  {
    initialize_anim_manager(&player->presentation.weapon_channels[1].anim_manager);
    player->presentation.weapon_channels[1].anim_manager.state = 0;
  }
  if ( (player->presentation.weapon_channels[2].body.bod.object->flags & 0x200000) != 0 )
  {
    v7 = player->presentation.weapon_channels[2].body.bod.bod.list_flags & 0xFFFFFFDF;
    BYTE1(v7) |= 8u;
    player->presentation.weapon_channels[2].body.bod.bod.list_flags = v7;
    player->presentation.weapon_channels[2].selected_state = 0;
    player->presentation.weapon_channels[2].body.render_animation_manager = &player->presentation.weapon_channels[2].anim_manager;
    initialize_anim_manager(&player->presentation.weapon_channels[2].anim_manager);
    player->presentation.weapon_channels[2].anim_manager.state = 1;
    player->presentation.weapon_channels[2].anim_manager.target_model = &player->presentation.weapon_channels[2].body;
    player->presentation.weapon_channels[2].anim_manager.animation_slots = player->presentation.weapon_channels[2].animation_slots;
    player->presentation.weapon_channels[2].anim_manager.queue_count = 0;
  }
  else
  {
    initialize_anim_manager(&player->presentation.weapon_channels[2].anim_manager);
    player->presentation.weapon_channels[2].anim_manager.state = 0;
  }
  initialize_snail_skin(&player->presentation.snail_skin);
  initialize_cutscene_ai(&player->presentation.cutscene);
  if ( !player->game->selected_level_record_active )
    player->presentation.cutscene.state = CUT_SCENE_STATE_INTRO_PENDING;
  player->presentation.owner_player = player;
  set_matrix_identity(&player->presentation.body.transform);
  set_matrix_identity(&player->presentation.cached_cutscene_matrix);
  set_matrix_identity(&player->presentation.previous_live_matrix);
  player->parcels_collected = 0;
  initialize_click_start((ClickStartController *)&player->click_start, (ClickStartPlayer *)player);
  initialize_cameraman(&player->cameraman);
  initialize_subgoldy_ghost(player, player->player_slot);
  player->damage_retrigger_step = 0.05050505;
  player->surface_reaction_step = 0.05050505;
  player->body.transform.position.x = 0.0;
  player->body.transform.position.y = 0.0;
  player->cached_camera_target_world.x = 0.0;
  player->body.transform.position.z = 4.0;
  z = player->body.transform.position.z;
  player->last_ring_spawn_z = 0.0;
  player->cached_camera_target_world.y = 0.0;
  player->barrier_hold_progress = 0.0;
  player->barrier_hold_step = 0.016666668;
  player->damage_retrigger_timer = 0.0;
  player->surface_reaction_timer = 0.0;
  player->presentation.wobble.roll_phase = 0.0;
  player->presentation.wobble.roll_phase_step = 0.0057471264;
  player->presentation.wobble.lift_phase = 0.0;
  player->presentation.wobble.lift_phase_step = 0.0067750677;
  LOBYTE(player->resurrect_active) = 0;
  player->cached_camera_target_world.z = z;
  player->velocity.z = 0.0;
  player->velocity.y = 0.0;
  player->velocity.x = 0.0;
  if ( player->player_slot != 1 )
  {
    if ( g_game_base != (GameRoot *)-180 )
    {
      p_input = (PlayerControlSource *)&g_game_base->game_inputs[1].input;
      goto LABEL_24;
    }
LABEL_23:
    p_input = nullptr;
    goto LABEL_24;
  }
  if ( g_game_base == (GameRoot *)-68 )
    goto LABEL_23;
  p_input = (PlayerControlSource *)&g_game_base->game_inputs[0].input;
LABEL_24:
  player->control_source = p_input;
  player->movement_fire_progress = 0.0;
  player->completion_handoff_active = 0;
  player->slide_extension_threshold_z = 0.0;
  initialize_damage_gauge(&player->damage_gauge);
  noop_runtime_ai();
  player->follow_state.active = 0;
  p_flight_transform = &player->golb_shots[0].flight_transform;
  v11 = 12;
  do
  {
    p_flight_transform[2].basis_right.x = 0.0;
    set_matrix_identity(p_flight_transform);
    LODWORD(p_flight_transform[2].basis_forward.w) = player->game;
    p_flight_transform = (TransformMatrix *)((char *)p_flight_transform + 744);
    --v11;
  }
  while ( v11 );
  v12 = player->player_slot;
  player->body.bod.bod.list_flags |= 0x20u;
  player->completion_handoff_cycle_progress = 0.0;
  player->completion_handoff_cycle_step = 0.20833334;
  player->unused_274c = 0;
  initialize_jetpack_gauge(&player->sub_hover, v12);
  player->lane_lean_state = 0;
  player->lane_lean_amplitude = 0.0;
  player->lane_lean_progress = 0.0;
  player->lane_lean_progress_step = 0.0;
  player->timer_360_state = 0;
  player->unknown_364 = 0;
  player->timer_360_progress = 0.0;
  player->timer_360_step = 0.0;
  player->nuke_effect_progress = 0.0;
  player->nuke_effect_progress_step = 0.0;
  player->attachment_exit_pending = 0;
  player->boost_one_tick = 0;
  player->lives = 0;
  player->game->camera_snap_requested = 1;
}
