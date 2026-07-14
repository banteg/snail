/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_subgame_level @ 0x437eb0 */
/* selector: build_subgame_level */

// Windows implementation of authored `cRSubGame::StartLevel(int)`. It performs the outer level-file load and manager resets, invokes `GenerateLevel(int)` for the runtime track rebuild, then sets up mode-specific HUD state, backdrop and landscape selection, player state, music, and the first gameplay object lists.
void __thiscall build_subgame_level(SubgameRuntime *game, int32_t level_index)
{
  int32_t level_mode; // eax
  double challenge_difficulty_value; // st7
  int32_t v5; // eax
  int landscape_script_by_name; // eax
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
  PresentationAnimationChannel *p_jetpack_channel; // eax
  char *v18; // ecx
  int v19; // edx
  int v20; // edx
  PresentationAnimationChannel *weapon_channels; // ecx
  char *v22; // eax
  int v23; // edx
  int v24; // edx
  PresentationAnimationChannel *v25; // ecx
  char *v26; // eax
  int v27; // edx
  int v28; // edx
  PresentationAnimationChannel *v29; // ecx
  char *v30; // eax
  int v31; // edx
  int v32; // edx
  Invincible *p_invincible_shell; // ecx
  char *v34; // eax
  int v35; // edx
  int v36; // edx
  uint32_t v37; // ecx
  Snail *p_presentation; // ecx
  char *v39; // eax
  int v40; // edx
  int v41; // edx
  char *v42; // eax
  int v43; // ecx
  int v44; // ecx
  BarrierActor *p_barrier; // eax
  struct BodNode *v46; // ecx
  int32_t v47; // eax
  float v48; // [esp+0h] [ebp-14h]

  unhide_star_field((StarManager *)((char *)g_game_base + 324412));
  if ( game->level_mode == 7 )
    hide_gameplay_scores(game);
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
  initialize_damage_gauge(&game->player.damage_gauge.state);
  noop_runtime_ai();
  initialize_sub_lazer_pool(&game->sub_lazers);
  initialize_salt_hazard_pool(&game->salt_hazards);
  reset_voice_manager(g_voice_manager);
  load_frontend_level_by_mode_and_index((LevelDefinitionLoader *)&game->level_definition, game->level_mode, level_index);
  if ( game->selected_level_record_active || game->selected_level_record_persistent )
  {
    *(float *)&game->_pad_20[16] = game->selected_level_record->replay_speed_scalar;
    game->level_mode = game->selected_level_record->replay_mode_id;
    *(_DWORD *)&game->_pad_20[12] = game->selected_level_record->challenge_difficulty_value;
    *(_DWORD *)&game->_pad_20[8] = game->selected_level_record->challenge_speed_value;
    challenge_difficulty_value = (double)game->selected_level_record->challenge_difficulty_value;
    goto LABEL_24;
  }
  level_mode = game->level_mode;
  switch ( level_mode )
  {
    case 3:
      *(float *)&game->_pad_20[16] = g_config_default_challenge_speed_slider;
      break;
    case 0:
    case 4:
    case 7:
      if ( game->level_definition.selected_speed_bits == -1082130432 )
        *(float *)&game->_pad_20[16] = calc_slider_to_rate(0.0);
      else
        *(float *)&game->_pad_20[16] = game->level_definition.selected_speed * 0.0099999998 * 0.90000004 + 0.2;
      break;
    case 1:
      v48 = (double)g_completion_bonus_x_source * 0.0099999998;
      *(float *)&game->_pad_20[16] = calc_slider_to_rate(v48);
      challenge_difficulty_value = (double)g_completion_bonus_y_source;
LABEL_24:
      game->challenge_difficulty_scalar = challenge_difficulty_value * 0.0099999998;
      break;
    case 2:
      *(float *)&game->_pad_20[16] = calc_slider_to_rate(g_config_default_challenge_speed_slider);
      break;
  }
  if ( game->selected_level_record_active || game->selected_level_record_persistent )
  {
    game->garbage_frequency = game->selected_level_record->garbage_frequency;
    game->salt_frequency = game->selected_level_record->salt_frequency;
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
      game->garbage_frequency = (double)g_completion_bonus_y_source * 0.0099999998 * 0.80000001;
      game->salt_frequency = (double)g_completion_bonus_y_source * 0.0099999998 * 0.80000001;
    }
  }
  initialize_track_parcel_slots(&game->parcel_manager);
  if ( *((_BYTE *)g_game_base + 324320) == 1 )
  {
    hide_border_init(&game->top_score_widget->list_kind);
    hide_border_init(&game->bottom_score_widget->list_kind);
  }
  rebuild_track_runtime_from_segments(game, level_index);
  if ( game->level_definition.track_texture_set == 5 )
  {
    switch ( (unsigned int)(__int64)random_float_below(4.0) )
    {
      case 0u:
        landscape_script_by_name = load_landscape_script_by_name((char *)g_game_base + 17220120, aSpaceblueswhor);
        break;
      case 1u:
        landscape_script_by_name = load_landscape_script_by_name((char *)g_game_base + 17220120, aSpacegreenwarp);
        break;
      case 2u:
        landscape_script_by_name = load_landscape_script_by_name((char *)g_game_base + 17220120, aSpacepurpleTxt);
        break;
      case 3u:
        landscape_script_by_name = load_landscape_script_by_name((char *)g_game_base + 17220120, aSpaceredTxt);
        break;
      default:
        landscape_script_by_name = level_index;
        break;
    }
    activate_landscape_entry((char *)&game->landscape_manager, landscape_script_by_name);
    *((_BYTE *)g_game_base + 322660) = random_float_below(1.0) > 0.5;
  }
  else
  {
    activate_landscape_entry((char *)&game->landscape_manager, game->level_definition.landscape_script_index);
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
  game->times_up.state = 0;
  game->subgame_state = 2;
  *((_DWORD *)g_game_base + 347) = 1;
  release_mouse_cursor((MouseCursorState *)((char *)g_game_base + 656));
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
    v18 = (char *)g_game_base + 1452;
    v19 = *((_DWORD *)g_game_base + 363);
    if ( v19 )
    {
      *(_DWORD *)(v19 + 8) = p_jetpack_channel;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v18 + 8) + 12) = *(_DWORD *)v18;
      v20 = *(_DWORD *)(*(_DWORD *)v18 + 8);
      *(_DWORD *)v18 = v20;
      *(_DWORD *)(v20 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v18 = p_jetpack_channel;
      game->player.presentation.jetpack_channel.body.bod.bod.list_prev = nullptr;
      *(_DWORD *)(*(_DWORD *)v18 + 12) = 0;
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
    v22 = (char *)g_game_base + 1452;
    v23 = *((_DWORD *)g_game_base + 363);
    if ( v23 )
    {
      *(_DWORD *)(v23 + 8) = weapon_channels;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v22 + 8) + 12) = *(_DWORD *)v22;
      v24 = *(_DWORD *)(*(_DWORD *)v22 + 8);
      *(_DWORD *)v22 = v24;
      *(_DWORD *)(v24 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v22 = weapon_channels;
      game->player.presentation.weapon_channels[0].body.bod.bod.list_prev = nullptr;
      *(_DWORD *)(*(_DWORD *)v22 + 12) = 0;
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
    v26 = (char *)g_game_base + 1452;
    v27 = *((_DWORD *)g_game_base + 363);
    if ( v27 )
    {
      *(_DWORD *)(v27 + 8) = v25;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v26 + 8) + 12) = *(_DWORD *)v26;
      v28 = *(_DWORD *)(*(_DWORD *)v26 + 8);
      *(_DWORD *)v26 = v28;
      *(_DWORD *)(v28 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v26 = v25;
      game->player.presentation.weapon_channels[1].body.bod.bod.list_prev = nullptr;
      *(_DWORD *)(*(_DWORD *)v26 + 12) = 0;
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
    v30 = (char *)g_game_base + 1452;
    v31 = *((_DWORD *)g_game_base + 363);
    if ( v31 )
    {
      *(_DWORD *)(v31 + 8) = v29;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v30 + 8) + 12) = *(_DWORD *)v30;
      v32 = *(_DWORD *)(*(_DWORD *)v30 + 8);
      *(_DWORD *)v30 = v32;
      *(_DWORD *)(v32 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v30 = v29;
      game->player.presentation.weapon_channels[2].body.bod.bod.list_prev = nullptr;
      *(_DWORD *)(*(_DWORD *)v30 + 12) = 0;
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
    v34 = (char *)g_game_base + 1452;
    v35 = *((_DWORD *)g_game_base + 363);
    if ( v35 )
    {
      *(_DWORD *)(v35 + 8) = p_invincible_shell;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v34 + 8) + 12) = *(_DWORD *)v34;
      v36 = *(_DWORD *)(*(_DWORD *)v34 + 8);
      *(_DWORD *)v34 = v36;
      *(_DWORD *)(v36 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v34 = p_invincible_shell;
      game->player.presentation.invincible_shell.body.bod.bod.list_prev = nullptr;
      *(_DWORD *)(*(_DWORD *)v34 + 12) = 0;
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
    v39 = (char *)g_game_base + 1452;
    v40 = *((_DWORD *)g_game_base + 363);
    if ( v40 )
    {
      *(_DWORD *)(v40 + 8) = p_presentation;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v39 + 8) + 12) = *(_DWORD *)v39;
      v41 = *(_DWORD *)(*(_DWORD *)v39 + 8);
      *(_DWORD *)v39 = v41;
      *(_DWORD *)(v41 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v39 = p_presentation;
      game->player.presentation.body.bod.bod.list_prev = nullptr;
      *(_DWORD *)(*(_DWORD *)v39 + 12) = 0;
    }
    game->player.presentation.body.bod.bod.list_flags |= 0x200u;
  }
  if ( (game->player.body.bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v42 = (char *)g_game_base + 1452;
    v43 = *((_DWORD *)g_game_base + 363);
    if ( v43 )
    {
      *(_DWORD *)(v43 + 8) = p_player;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v42 + 8) + 12) = *(_DWORD *)v42;
      v44 = *(_DWORD *)(*(_DWORD *)v42 + 8);
      *(_DWORD *)v42 = v44;
      *(_DWORD *)(v44 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v42 = p_player;
      game->player.body.bod.bod.list_prev = nullptr;
      *(_DWORD *)(*(_DWORD *)v42 + 12) = 0;
    }
    game->player.body.bod.bod.list_flags |= 0x200u;
  }
  initialize_slug_voice_manager(&game->slug_voice_manager.active);
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
    unhide_border_init(&game->lives_icon_widget->list_kind);
    unhide_border_init(&game->lives_text_widget->list_kind);
  }
  set_input_controller_pointer_authored_xy(0, 320.0, 240.0);
  set_input_controller_pointer_authored_xy(1, 320.0, 240.0);
  game->player.track_z_offset = 320.0;
  game->player.track_z_anchor = 320.0;
  game->_pad_00[0] = 1;
  calc_subgame_rate(game);
}

