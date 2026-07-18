/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_subgame_level @ 0x437eb0 */
/* selector: build_subgame_level */

// Windows implementation of authored `cRSubGame::StartLevel(int)`. It performs the outer level-file load and manager resets, invokes `GenerateLevel(int)` for the runtime track rebuild, then sets up mode-specific HUD state, backdrop and landscape selection, player state, music, and the first gameplay object lists.
void __thiscall build_subgame_level(SubgameRuntime *game, int32_t level_index)
{
  int32_t level_mode; // eax
  double challenge_difficulty_value; // st7
  int32_t v5; // eax
  int32_t landscape_script_by_name; // eax
  BannerPool *p_banners; // eax
  BodBase *p_track_body_list_head; // edi
  struct BodNode *list_next; // ecx
  uint32_t list_flags; // edx
  double first_block_row_count; // st7
  Banner *v12; // eax
  struct BodNode *v13; // ecx
  uint32_t v14; // eax
  double completion_row_start; // st7
  Player *p_player; // edi
  Weapon *p_jetpack_channel; // eax
  BodNode **active_first_ref_jetpack; // ecx
  BodNode *active_first_jetpack; // edx
  BodNode *active_new_first_jetpack; // edx
  Weapon *weapon_channels; // ecx
  BodNode **active_first_ref_weapon_0; // eax
  BodNode *active_first_weapon_0; // edx
  BodNode *active_new_first_weapon_0; // edx
  Weapon *v25; // ecx
  BodNode **active_first_ref_weapon_1; // eax
  BodNode *active_first_weapon_1; // edx
  BodNode *active_new_first_weapon_1; // edx
  Weapon *v29; // ecx
  BodNode **active_first_ref_weapon_2; // eax
  BodNode *active_first_weapon_2; // edx
  BodNode *active_new_first_weapon_2; // edx
  Invincible *p_invincible_shell; // ecx
  BodNode **active_first_ref_invincible_shell; // eax
  BodNode *active_first_invincible_shell; // edx
  BodNode *active_new_first_invincible_shell; // edx
  uint32_t v37; // ecx
  Snail *p_presentation; // ecx
  BodNode **active_first_ref_presentation; // eax
  BodNode *active_first_presentation; // edx
  BodNode *active_new_first_presentation; // edx
  BodNode **active_first_ref_player; // eax
  BodNode *active_first_player; // ecx
  BodNode *active_new_first_player; // ecx
  BarrierActor *p_barrier; // eax
  struct BodNode *v46; // ecx
  int32_t v47; // eax
  float v48; // [esp+0h] [ebp-14h]

  unhide_star_field(&g_game_base->star_manager);
  if ( game->level_mode == 7 )
    hide_gameplay_scores((FrontendWidget **)game);
  else
    unhide_gameplay_scores(game);
  switch ( (unsigned int)(__int64)((double)next_math_random_value() * 0.00012207031) )
  {
    case 0u:
      cache_music_file(aMusic1Ogg, 0, (char *)g_blank_text);
      break;
    case 1u:
      cache_music_file(aMusic2Ogg, 0, (char *)g_blank_text);
      break;
    case 2u:
    case 4u:
      cache_music_file(aMusic3Ogg, 0, (char *)g_blank_text);
      break;
    case 3u:
      cache_music_file(aMusic4Ogg, 0, (char *)g_blank_text);
      break;
    default:
      break;
  }
  game->next_slug_voice_trigger_z = 50.0;
  game->slug_voice_trigger_spacing_z = 100.0;
  initialize_enemy_manager(&game->enemy_manager.count);
  initialize_damage_gauge(&game->player.damage_gauge);
  noop_runtime_ai();
  initialize_sub_lazer_pool(&game->sub_lazers);
  initialize_salt_hazard_pool(&game->salt_hazards);
  reset_voice_manager(&g_voice_manager);
  load_frontend_level_by_mode_and_index(&game->level_definition, game->level_mode, level_index);
  if ( game->selected_level_record_active || game->selected_level_record_persistent )
  {
    game->rate_or_level_arg.level_arg_tail = game->selected_level_record->replay_speed_scalar.bits;
    game->level_mode = game->selected_level_record->replay_mode_id;
    game->completion_bonus_y_source = game->selected_level_record->challenge_difficulty_value;
    game->completion_bonus_x_source = game->selected_level_record->challenge_speed_value;
    challenge_difficulty_value = (double)game->selected_level_record->challenge_difficulty_value;
    goto LABEL_24;
  }
  level_mode = game->level_mode;
  switch ( level_mode )
  {
    case 3:
      game->rate_or_level_arg.level_arg_tail = LODWORD(g_runtime_config.default_challenge_speed_slider);
      break;
    case 0:
    case 4:
    case 7:
      if ( game->level_definition.selected_speed.bits == -1082130432 )
        game->rate_or_level_arg.base_rate = calc_slider_to_rate(0.0);
      else
        game->rate_or_level_arg.base_rate = game->level_definition.selected_speed.value * 0.0099999998 * 0.90000004
                                          + 0.2;
      break;
    case 1:
      v48 = (double)g_runtime_config.completion_bonus_x_source * 0.0099999998;
      game->rate_or_level_arg.base_rate = calc_slider_to_rate(v48);
      challenge_difficulty_value = (double)g_runtime_config.completion_bonus_y_source;
LABEL_24:
      game->challenge_difficulty_scalar = challenge_difficulty_value * 0.0099999998;
      break;
    case 2:
      game->rate_or_level_arg.base_rate = calc_slider_to_rate(g_runtime_config.default_challenge_speed_slider);
      break;
  }
  if ( game->selected_level_record_active || game->selected_level_record_persistent )
  {
    LODWORD(game->garbage_frequency) = game->selected_level_record->garbage_frequency.bits;
    LODWORD(game->salt_frequency) = game->selected_level_record->salt_frequency.bits;
  }
  else
  {
    v5 = game->level_mode;
    if ( v5 == 2 || v5 == 3 || !v5 || v5 == 4 || v5 == 7 )
    {
      game->garbage_frequency = game->level_definition.garbage_frequency * 0.0099999998;
      game->salt_frequency = game->level_definition.salt_frequency * 0.0099999998;
    }
    else if ( v5 == 1 )
    {
      game->garbage_frequency = (double)g_runtime_config.completion_bonus_y_source * 0.0099999998 * 0.80000001;
      game->salt_frequency = (double)g_runtime_config.completion_bonus_y_source * 0.0099999998 * 0.80000001;
    }
  }
  initialize_track_parcel_slots(&game->parcel_manager);
  if ( g_game_base->intro.hide_for_replay_latch == 1 )
  {
    hide_border_init(game->top_score_widget);
    hide_border_init(game->bottom_score_widget);
  }
  rebuild_track_runtime_from_segments(game, level_index);
  if ( game->level_definition.track_texture_set == 5 )
  {
    switch ( (unsigned int)(__int64)random_float_below(4.0) )
    {
      case 0u:
        landscape_script_by_name = load_landscape_script_by_name(
                                     &g_game_base->subgame.landscape_manager,
                                     aSpaceblueswhor);
        break;
      case 1u:
        landscape_script_by_name = load_landscape_script_by_name(
                                     &g_game_base->subgame.landscape_manager,
                                     aSpacegreenwarp);
        break;
      case 2u:
        landscape_script_by_name = load_landscape_script_by_name(
                                     &g_game_base->subgame.landscape_manager,
                                     aSpacepurpleTxt);
        break;
      case 3u:
        landscape_script_by_name = load_landscape_script_by_name(&g_game_base->subgame.landscape_manager, aSpaceredTxt);
        break;
      default:
        landscape_script_by_name = level_index;
        break;
    }
    activate_landscape_entry(&game->landscape_manager, landscape_script_by_name);
    g_game_base->backdrop.pending_flip = random_float_below(1.0) > 0.5;
  }
  else
  {
    activate_landscape_entry(&game->landscape_manager, game->level_definition.landscape_script_index);
  }
  p_banners = &game->banners;
  p_track_body_list_head = &game->track_body_list_head;
  if ( (game->banners.slots[0].bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    game->banners.slots[0].bod.bod.list_prev = &p_track_body_list_head->bod;
    game->banners.slots[0].bod.bod.list_next = game->track_body_list_head.bod.list_next;
    game->track_body_list_head.bod.list_next = (struct BodNode *)p_banners;
    list_next = game->banners.slots[0].bod.bod.list_next;
    if ( list_next )
      list_next->list_prev = (struct BodNode *)p_banners;
    game->banners.slots[0].bod.bod.list_flags |= 0x200u;
  }
  game->banners.slots[0].bod.position.z = 0.0;
  game->banners.slots[0].bod.position.y = 0.0;
  game->banners.slots[0].bod.position.x = 0.0;
  list_flags = game->banners.slots[0].bod.bod.list_flags;
  first_block_row_count = (double)game->first_block_row_count;
  game->banners.slots[0].owner_player = &game->player;
  game->banners.slots[0].bod.position.z = first_block_row_count;
  v12 = &game->banners.slots[1];
  game->banners.slots[0].bod.bod.list_flags = list_flags & 0xFFFFFFDF;
  game->banners.slots[0].bod.color.a = 0.99900001;
  if ( (game->banners.slots[1].bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    game->banners.slots[1].bod.bod.list_prev = &p_track_body_list_head->bod;
    game->banners.slots[1].bod.bod.list_next = game->track_body_list_head.bod.list_next;
    game->track_body_list_head.bod.list_next = &v12->bod.bod;
    v13 = game->banners.slots[1].bod.bod.list_next;
    if ( v13 )
      v13->list_prev = &v12->bod.bod;
    game->banners.slots[1].bod.bod.list_flags |= 0x200u;
  }
  game->banners.slots[1].bod.position.z = 0.0;
  game->banners.slots[1].bod.position.y = 0.0;
  game->banners.slots[1].bod.position.x = 0.0;
  v14 = game->banners.slots[1].bod.bod.list_flags;
  completion_row_start = (double)game->completion_row_start;
  p_player = &game->player;
  LOBYTE(v14) = v14 & 0xDF;
  game->banners.slots[1].owner_player = &game->player;
  game->banners.slots[1].bod.bod.list_flags = v14;
  game->banners.slots[1].bod.position.z = completion_row_start;
  game->banners.slots[1].bod.color.a = 0.99900001;
  game->track_state_latch = 0;
  game->replay_update_cursor = 0;
  game->times_up.state = TIMES_UP_STATE_INACTIVE;
  game->subgame_state = 2;
  g_game_base->render_skip_count = 1;
  release_mouse_cursor(&g_game_base->players[0].mouse_cursor);
  game->player.movement_mode_selector = 1;
  game->player.steering_mode_selector = 0;
  initialize_subgoldy(&game->player, 1);
  p_jetpack_channel = &game->player.presentation.jetpack_channel;
  if ( (game->player.presentation.jetpack_channel.body.bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    active_first_ref_jetpack = &g_game_base->active_bod_list.first;
    active_first_jetpack = g_game_base->active_bod_list.first;
    if ( active_first_jetpack )
    {
      active_first_jetpack->list_prev = &p_jetpack_channel->body.bod.bod;
      (*active_first_ref_jetpack)->list_prev->list_next = *active_first_ref_jetpack;
      active_new_first_jetpack = (*active_first_ref_jetpack)->list_prev;
      *active_first_ref_jetpack = active_new_first_jetpack;
      active_new_first_jetpack->list_prev = nullptr;
    }
    else
    {
      *active_first_ref_jetpack = &p_jetpack_channel->body.bod.bod;
      game->player.presentation.jetpack_channel.body.bod.bod.list_prev = nullptr;
      (*active_first_ref_jetpack)->list_next = nullptr;
    }
    game->player.presentation.jetpack_channel.body.bod.bod.list_flags |= 0x200u;
  }
  weapon_channels = game->player.presentation.weapon_channels;
  if ( (game->player.presentation.weapon_channels[0].body.bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    active_first_ref_weapon_0 = &g_game_base->active_bod_list.first;
    active_first_weapon_0 = g_game_base->active_bod_list.first;
    if ( active_first_weapon_0 )
    {
      active_first_weapon_0->list_prev = &weapon_channels->body.bod.bod;
      (*active_first_ref_weapon_0)->list_prev->list_next = *active_first_ref_weapon_0;
      active_new_first_weapon_0 = (*active_first_ref_weapon_0)->list_prev;
      *active_first_ref_weapon_0 = active_new_first_weapon_0;
      active_new_first_weapon_0->list_prev = nullptr;
    }
    else
    {
      *active_first_ref_weapon_0 = &weapon_channels->body.bod.bod;
      game->player.presentation.weapon_channels[0].body.bod.bod.list_prev = nullptr;
      (*active_first_ref_weapon_0)->list_next = nullptr;
    }
    game->player.presentation.weapon_channels[0].body.bod.bod.list_flags |= 0x200u;
  }
  v25 = &game->player.presentation.weapon_channels[1];
  if ( (game->player.presentation.weapon_channels[1].body.bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    active_first_ref_weapon_1 = &g_game_base->active_bod_list.first;
    active_first_weapon_1 = g_game_base->active_bod_list.first;
    if ( active_first_weapon_1 )
    {
      active_first_weapon_1->list_prev = &v25->body.bod.bod;
      (*active_first_ref_weapon_1)->list_prev->list_next = *active_first_ref_weapon_1;
      active_new_first_weapon_1 = (*active_first_ref_weapon_1)->list_prev;
      *active_first_ref_weapon_1 = active_new_first_weapon_1;
      active_new_first_weapon_1->list_prev = nullptr;
    }
    else
    {
      *active_first_ref_weapon_1 = &v25->body.bod.bod;
      game->player.presentation.weapon_channels[1].body.bod.bod.list_prev = nullptr;
      (*active_first_ref_weapon_1)->list_next = nullptr;
    }
    game->player.presentation.weapon_channels[1].body.bod.bod.list_flags |= 0x200u;
  }
  v29 = &game->player.presentation.weapon_channels[2];
  if ( (game->player.presentation.weapon_channels[2].body.bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    active_first_ref_weapon_2 = &g_game_base->active_bod_list.first;
    active_first_weapon_2 = g_game_base->active_bod_list.first;
    if ( active_first_weapon_2 )
    {
      active_first_weapon_2->list_prev = &v29->body.bod.bod;
      (*active_first_ref_weapon_2)->list_prev->list_next = *active_first_ref_weapon_2;
      active_new_first_weapon_2 = (*active_first_ref_weapon_2)->list_prev;
      *active_first_ref_weapon_2 = active_new_first_weapon_2;
      active_new_first_weapon_2->list_prev = nullptr;
    }
    else
    {
      *active_first_ref_weapon_2 = &v29->body.bod.bod;
      game->player.presentation.weapon_channels[2].body.bod.bod.list_prev = nullptr;
      (*active_first_ref_weapon_2)->list_next = nullptr;
    }
    game->player.presentation.weapon_channels[2].body.bod.bod.list_flags |= 0x200u;
  }
  p_invincible_shell = &game->player.presentation.invincible_shell;
  if ( (game->player.presentation.invincible_shell.body.bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    active_first_ref_invincible_shell = &g_game_base->active_bod_list.first;
    active_first_invincible_shell = g_game_base->active_bod_list.first;
    if ( active_first_invincible_shell )
    {
      active_first_invincible_shell->list_prev = &p_invincible_shell->body.bod.bod;
      (*active_first_ref_invincible_shell)->list_prev->list_next = *active_first_ref_invincible_shell;
      active_new_first_invincible_shell = (*active_first_ref_invincible_shell)->list_prev;
      *active_first_ref_invincible_shell = active_new_first_invincible_shell;
      active_new_first_invincible_shell->list_prev = nullptr;
    }
    else
    {
      *active_first_ref_invincible_shell = &p_invincible_shell->body.bod.bod;
      game->player.presentation.invincible_shell.body.bod.bod.list_prev = nullptr;
      (*active_first_ref_invincible_shell)->list_next = nullptr;
    }
    game->player.presentation.invincible_shell.body.bod.bod.list_flags |= 0x200u;
  }
  v37 = game->player.presentation.invincible_shell.body.bod.bod.list_flags;
  LOBYTE(v37) = v37 | 0x80;
  game->player.presentation.invincible_shell.body.bod.bod.list_flags = v37;
  p_presentation = &game->player.presentation;
  if ( (game->player.presentation.body.bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    active_first_ref_presentation = &g_game_base->active_bod_list.first;
    active_first_presentation = g_game_base->active_bod_list.first;
    if ( active_first_presentation )
    {
      active_first_presentation->list_prev = &p_presentation->body.bod.bod;
      (*active_first_ref_presentation)->list_prev->list_next = *active_first_ref_presentation;
      active_new_first_presentation = (*active_first_ref_presentation)->list_prev;
      *active_first_ref_presentation = active_new_first_presentation;
      active_new_first_presentation->list_prev = nullptr;
    }
    else
    {
      *active_first_ref_presentation = &p_presentation->body.bod.bod;
      game->player.presentation.body.bod.bod.list_prev = nullptr;
      (*active_first_ref_presentation)->list_next = nullptr;
    }
    game->player.presentation.body.bod.bod.list_flags |= 0x200u;
  }
  if ( (game->player.body.bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    active_first_ref_player = &g_game_base->active_bod_list.first;
    active_first_player = g_game_base->active_bod_list.first;
    if ( active_first_player )
    {
      active_first_player->list_prev = &p_player->body.bod.bod;
      (*active_first_ref_player)->list_prev->list_next = *active_first_ref_player;
      active_new_first_player = (*active_first_ref_player)->list_prev;
      *active_first_ref_player = active_new_first_player;
      active_new_first_player->list_prev = nullptr;
    }
    else
    {
      *active_first_ref_player = &p_player->body.bod.bod;
      game->player.body.bod.bod.list_prev = nullptr;
      (*active_first_ref_player)->list_next = nullptr;
    }
    game->player.body.bod.bod.list_flags |= 0x200u;
  }
  initialize_slug_voice_manager(&game->slug_voice_manager);
  p_barrier = &game->barrier;
  if ( (game->barrier.bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    game->barrier.bod.bod.list_prev = &game->barrier_sub_lazer_list_head.bod;
    game->barrier.bod.bod.list_next = game->barrier_sub_lazer_list_head.bod.list_next;
    game->barrier_sub_lazer_list_head.bod.list_next = &p_barrier->bod.bod;
    v46 = game->barrier.bod.bod.list_next;
    if ( v46 )
      v46->list_prev = &p_barrier->bod.bod;
    game->barrier.bod.bod.list_flags |= 0x200u;
  }
  v47 = game->level_mode;
  game->barrier.owner_player = p_player;
  if ( !v47 )
  {
    sprintf((char *const)&game->lives_text_widget->text_buffer, "0/%i", game->level_definition.parcel_count);
    unhide_border_init(game->lives_icon_widget);
    unhide_border_init(game->lives_text_widget);
  }
  set_input_controller_pointer_authored_xy(0, 320.0, 240.0);
  set_input_controller_pointer_authored_xy(1, 320.0, 240.0);
  game->player.track_z_offset = 320.0;
  game->player.track_z_anchor = 320.0;
  game->scan_reset = 1;
  calc_subgame_rate(game);
}
