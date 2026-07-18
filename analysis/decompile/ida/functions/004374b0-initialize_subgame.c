/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_subgame @ 0x4374b0 */
/* selector: initialize_subgame */

// Initializes the active gameplay subgame state, including the continuation selector at `+0x1270fc8`, per-mode HUD widgets, replay-backed startup, and the first galaxy, challenge-setup, or gameplay handoff. Cross-port Android and iOS symbols match this helper to `cRSubGame::Init()`.
void __thiscall initialize_subgame(SubgameRuntime *game)
{
  int v1; // edx
  Fringe **p_fringe_front; // eax
  int v4; // ecx
  Fringe **v5; // edi
  int32_t subgame_rebuild_selector; // eax
  int32_t landscape_script_by_name; // eax
  int32_t level_mode; // eax
  int v9; // eax
  SubSolution *postal_records; // eax
  tColour *v11; // eax
  tColour *v12; // eax
  tColour *v13; // eax
  int v14; // edi
  FrontendWidget **life_stock_widgets; // esi
  tColour *v16; // eax
  int32_t v17; // eax
  SubSolutionScoreOrTime *p_score_or_time; // edx
  char *v19; // eax
  tColour *v20; // eax
  char *v21; // eax
  GameRoot *v22; // eax
  float v23; // eax
  float y; // eax
  int32_t v25; // eax
  int v26; // edx
  float x; // [esp+0h] [ebp-40h]
  int v28; // [esp+24h] [ebp-1Ch]
  Time color; // [esp+28h] [ebp-18h] BYREF

  v1 = 3200;
  p_fringe_front = &game->runtime_cells[0][0].fringe_front;
  do
  {
    v4 = 8;
    do
    {
      v5 = p_fringe_front;
      p_fringe_front += 21;
      --v4;
      *v5 = nullptr;
      v5[1] = nullptr;
      v5[2] = nullptr;
      v5[3] = nullptr;
    }
    while ( v4 );
    --v1;
  }
  while ( v1 );
  subgame_rebuild_selector = game->subgame_rebuild_selector;
  if ( subgame_rebuild_selector == 2 || subgame_rebuild_selector == 1 )
  {
    cache_music_file(g_main_menu_music_path, 0, (char *)g_blank_text);
    landscape_script_by_name = load_landscape_script_by_name(
                                 &g_game_base->subgame.landscape_manager,
                                 g_menu_background_script_path);
    change_backdrop(
      &g_game_base->backdrop,
      &g_game_base->subgame.landscape_manager.scripts[landscape_script_by_name],
      0);
    set_border_justify_centre(&g_game_base->border_manager, 25.0);
  }
  level_mode = game->level_mode;
  if ( !level_mode )
  {
    postal_records = game->sub_high_score.postal_records;
LABEL_14:
    game->sub_high_score.active_record_bank = postal_records;
    game->active_level_score = postal_records->score;
    goto LABEL_15;
  }
  v9 = level_mode - 1;
  if ( v9 )
  {
    if ( v9 != 3 )
      goto LABEL_16;
    postal_records = game->sub_high_score.time_trial_route_records;
    goto LABEL_14;
  }
  postal_records = game->sub_high_score.survival_records;
  game->sub_high_score.active_record_bank = game->sub_high_score.survival_records;
  game->active_level_score = game->sub_high_score.survival_records[0].score;
LABEL_15:
  qmemcpy(&game->active_level_timer, &postal_records->score_or_time, sizeof(game->active_level_timer));
LABEL_16:
  if ( game->selected_level_record_persistent )
    game->rate_or_level_arg.level_arg_tail = game->selected_level_record->replay_speed_scalar.bits;
  game->subgame_pause_gate = 0;
  game->resume_requested = 0;
  game->pause_fade = 0.0;
  game->pause_fade_step = 0.033333335;
  noop_runtime_ai();
  game->subgame_state = 0;
  game->times_up.state = TIMES_UP_STATE_INACTIVE;
  game->top_score_widget = allocate_border(&g_game_base->border_manager);
  v11 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 0.029999999);
  initialize_frontend_widget(game->top_score_widget, 0x400002u, a0, 20, 400.0, 14.0, v11, 3, 300.0);
  game->top_score_widget->font_scale = 1.5;
  game->top_score_widget->texture_layer = 7;
  game->top_score_widget->text_buffer.raw[0] = 0;
  if ( !game->level_mode )
  {
    game->lives_icon_widget = allocate_border(&g_game_base->border_manager);
    v12 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_sprite_button(game->lives_icon_widget, 0x400800u, 122, 0.0, 58.0, v12, 0.0, 4);
    hide_border_init(game->lives_icon_widget);
    game->lives_icon_widget->sprite_shadow_offset = 0.0;
    game->lives_text_widget = allocate_border(&g_game_base->border_manager);
    v13 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 0.029999999);
    initialize_frontend_widget(game->lives_text_widget, 0x400002u, a0, 20, 47.0, 80.0, v13, 0, 0.0);
    hide_border_init(game->lives_text_widget);
    v14 = 0;
    v28 = 0;
    life_stock_widgets = game->life_stock_widgets;
    game->lives_text_widget->font_scale = 0.69999999;
    do
    {
      *life_stock_widgets = allocate_border(&g_game_base->border_manager);
      v16 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
      x = (double)v28 * 24.0 + 13.0;
      initialize_frontend_sprite_button(*life_stock_widgets, 0x400800u, 123, x, 430.0, v16, 0.0, 4);
      (*life_stock_widgets)->sprite_shadow_offset = 0.0;
      hide_border_init(*life_stock_widgets);
      ++v14;
      ++life_stock_widgets;
      v28 = v14;
    }
    while ( v14 < 9 );
  }
  v17 = game->level_mode;
  if ( game->sub_high_score.current_result_record.replay_mode_id == v17 )
  {
    if ( v17 == 4 )
    {
      p_score_or_time = &game->sub_high_score.current_result_record.score_or_time;
LABEL_24:
      v19 = format_time_trial_string(&game->time_trial, (Time *)p_score_or_time);
      rstrcpy_checked_ascii((char *)&game->top_score_widget->text_buffer, v19);
      goto LABEL_29;
    }
    border_add_text_number(game->top_score_widget, game->sub_high_score.current_result_record.score);
  }
  else
  {
    if ( v17 == 4 )
    {
      zero_timer_counters(&color);
      p_score_or_time = (SubSolutionScoreOrTime *)&color;
      goto LABEL_24;
    }
    border_add_text_number(game->top_score_widget, 0);
  }
LABEL_29:
  game->bottom_score_widget = allocate_border(&g_game_base->border_manager);
  v20 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 0.029999999);
  initialize_frontend_widget(game->bottom_score_widget, 0x400002u, a0, 20, 40.0, 14.0, v20, 3, -71.0);
  game->bottom_score_widget->font_scale = 1.5;
  game->bottom_score_widget->texture_layer = 7;
  game->bottom_score_widget->text_buffer.raw[0] = 0;
  switch ( game->level_mode )
  {
    case 0:
    case 1:
      border_add_text_number(game->bottom_score_widget, game->active_level_score);
      break;
    case 2:
    case 3:
      hide_border_init(game->bottom_score_widget);
      hide_border_init(game->top_score_widget);
      break;
    case 4:
      v21 = format_time_trial_string(&game->time_trial, &game->active_level_timer);
      rstrcpy_checked_ascii((char *)&game->bottom_score_widget->text_buffer, v21);
      break;
    default:
      break;
  }
  v22 = g_game_base;
  if ( g_game_base->intro.hide_for_replay_latch || game->level_mode == 7 )
  {
    hide_border_init(game->bottom_score_widget);
    hide_border_init(game->top_score_widget);
    v22 = g_game_base;
  }
  if ( !v22->players[0].high_score_entry_pending )
  {
    v22->players[0].high_score_entry_pending = 0;
    g_game_base->players[0].selected_high_score_rank = 0;
    load_builtin_segment_definitions(&game->level_definition_scratch, (SubSegmentRaw **)&g_builtin_segment_definitions);
    set_matrix_identity(&game->player.body.transform);
    game->player.movement_mode_selector = 0;
    game->player.game = game;
    v23 = game->player.body.transform.position.x;
    game->player.attachment_exit_pending = 0;
    game->player.cached_camera_target_world.x = v23;
    game->player.boost_one_tick = 0;
    y = game->player.body.transform.position.y;
    game->player.lives = 0;
    game->player.cached_camera_target_world.y = y;
    game->player.cached_camera_target_world.z = game->player.body.transform.position.z;
    game->player.body.bod.bod.list_flags &= ~0x20u;
    initialize_warning(&game->player.warning);
    v25 = game->subgame_rebuild_selector;
    if ( v25 && v25 != 3 )
    {
      if ( !game->selected_level_record_persistent )
      {
        switch ( game->level_mode )
        {
          case 0:
            if ( v25 == 1 )
            {
              v26 = game->level_mode_arg + 1;
              game->level_mode_arg = v26;
              if ( v26 > g_runtime_config.highest_galaxy_route_index )
              {
                g_runtime_config.highest_galaxy_route_index = v26;
                save_config_file(aSnailmailCfg, &g_runtime_config, 196);
              }
              g_runtime_config.landscape_backdrop_variant_selector = game->level_mode_arg;
            }
            goto LABEL_45;
          case 1:
            initialize_challenge_setup_screen(&game->gui);
            reset_subgame(game);
            break;
          case 4:
LABEL_45:
            initialize_galaxy(&game->galaxy);
            reset_subgame(game);
            break;
          case 7:
            game->subgame_state = 0;
            reset_subgame(game);
            break;
          default:
            report_errorf(aUnknownGameMod);
            reset_subgame(game);
            break;
        }
        return;
      }
      game->rate_or_level_arg.level_arg_tail = game->selected_level_record->replay_speed_scalar.bits;
    }
    reset_subgame(game);
  }
}
