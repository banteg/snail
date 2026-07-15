/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_challenge_setup_screen @ 0x416370 */
/* selector: update_challenge_setup_screen */

// Implements result-bearing `cRGUI::AI()`: runs postal, challenge, and time-trial level selection, including navigation, difficulty/speed changes, replay launch, Play, and Back handoffs. `update_subgame` consumes its semantic 0/1/3 result, so this member remains `int`.
int __thiscall update_challenge_setup_screen(GUI *gui)
{
  int32_t level_mode; // eax
  int v3; // eax
  FrontendWidget *next_level_button; // ecx
  FrontendWidgetFlag widget_flags; // eax
  char *v6; // eax
  FrontendWidget *previous_level_button; // ecx
  FrontendWidgetFlag v8; // eax
  char *v9; // eax
  FrontendWidget *v10; // eax
  FrontendWidgetFlag v11; // edi
  unsigned int v12; // edi
  FrontendWidget *v13; // eax
  FrontendWidget *replay_button; // ecx
  FrontendWidget *back_button; // ecx
  FrontendWidgetFlag v16; // eax
  FrontendWidget *play_button; // ecx
  FrontendWidgetFlag v18; // eax
  FrontendWidget *v19; // ecx
  FrontendWidgetFlag v20; // eax
  FrontendWidget *v22; // ecx
  FrontendWidgetFlag v23; // eax
  FrontendWidget *v24; // ecx
  FrontendWidgetFlag v25; // eax
  FrontendWidget *v26; // ecx
  FrontendWidgetFlag v27; // eax
  FrontendWidget *v28; // eax
  FrontendWidgetFlag v29; // edi
  unsigned int v30; // edi
  FrontendWidget *v31; // eax

  hide_gameplay_scores(&gui->game->scan_reset);
  level_mode = gui->game->level_mode;
  if ( level_mode )
  {
    v3 = level_mode - 1;
    if ( v3 )
    {
      if ( v3 == 3 )
      {
        next_level_button = gui->next_level_button;
        widget_flags = next_level_button->widget_flags;
        if ( (widget_flags & 0x20) != 0 )
        {
          LOBYTE(widget_flags) = widget_flags & 0xDF;
          next_level_button->widget_flags = widget_flags;
          load_frontend_level_by_mode_and_index(
            &gui->game->level_definition,
            gui->game->level_mode,
            ++gui->game->level_mode_arg);
          rstrcpy_checked_ascii(
            (char *)&gui->level_name_widget->text_buffer,
            gui->game->level_definition.level_display_name);
          layout_frontend_widget(gui->level_name_widget);
          v6 = format_time_trial_string(
                 &gui->game->time_trial,
                 (Time *)&gui->game->sub_high_score.time_trial_route_records[gui->game->level_mode_arg].score_or_time);
          rstrcpy_checked_ascii((char *)&gui->game->bottom_score_widget->text_buffer, v6);
        }
        previous_level_button = gui->previous_level_button;
        v8 = previous_level_button->widget_flags;
        if ( (v8 & 0x20) != 0 )
        {
          LOBYTE(v8) = v8 & 0xDF;
          previous_level_button->widget_flags = v8;
          load_frontend_level_by_mode_and_index(
            &gui->game->level_definition,
            gui->game->level_mode,
            --gui->game->level_mode_arg);
          rstrcpy_checked_ascii(
            (char *)&gui->level_name_widget->text_buffer,
            gui->game->level_definition.level_display_name);
          layout_frontend_widget(gui->level_name_widget);
          v9 = format_time_trial_string(
                 &gui->game->time_trial,
                 (Time *)&gui->game->sub_high_score.time_trial_route_records[gui->game->level_mode_arg].score_or_time);
          rstrcpy_checked_ascii((char *)&gui->game->bottom_score_widget->text_buffer, v9);
        }
        v10 = gui->previous_level_button;
        v11 = v10->widget_flags;
        if ( gui->game->level_mode_arg )
          v12 = v11 & 0xFFFF7FFF;
        else
          v12 = v11 | 0x8000;
        v10->widget_flags = v12;
        v13 = gui->next_level_button;
        if ( gui->game->level_mode_arg == g_runtime_config.highest_galaxy_route_index )
          v13->widget_flags |= 0x8000u;
        else
          v13->widget_flags &= ~0x8000u;
        replay_button = gui->replay_button;
        if ( gui->game->sub_high_score.time_trial_route_records[gui->game->level_mode_arg].active == 1 )
        {
          unhide_border_init(replay_button);
          stack_widget_below(gui->back_button, gui->replay_button);
        }
        else
        {
          hide_border_init(replay_button);
          stack_widget_below(gui->back_button, gui->play_button);
        }
        back_button = gui->back_button;
        v16 = back_button->widget_flags;
        if ( (v16 & 0x20) != 0 )
          goto LABEL_38;
        play_button = gui->play_button;
        v18 = play_button->widget_flags;
        if ( (v18 & 0x20) != 0 )
          goto LABEL_40;
        v19 = gui->replay_button;
        v20 = v19->widget_flags;
        if ( (v20 & 0x20) != 0 )
        {
          LOBYTE(v20) = v20 & 0xDF;
          v19->widget_flags = v20;
          destroy_challenge_setup_screen(gui);
          gui->game->selected_level_record_active = 1;
          gui->game->selected_level_record = &gui->game->sub_high_score.time_trial_route_records[gui->game->level_mode_arg];
          return 1;
        }
      }
    }
    else
    {
      back_button = gui->back_button;
      v16 = back_button->widget_flags;
      if ( (v16 & 0x20) != 0 )
      {
LABEL_38:
        LOBYTE(v16) = v16 & 0xDF;
        back_button->widget_flags = v16;
        destroy_challenge_setup_screen(gui);
        return 3;
      }
      play_button = gui->play_button;
      v18 = play_button->widget_flags;
      if ( (v18 & 0x20) != 0 )
        goto LABEL_40;
      g_runtime_config.completion_bonus_x_source = (__int64)(gui->speed_slider->slider_position_target * 100.0 + 0.1);
      g_runtime_config.completion_bonus_y_source = (__int64)(gui->difficulty_slider->slider_position_target * 100.0 + 0.1);
      v22 = gui->replay_button;
      v23 = v22->widget_flags;
      if ( (v23 & 0x20) != 0 )
      {
        LOBYTE(v23) = v23 & 0xDF;
        v22->widget_flags = v23;
        destroy_challenge_setup_screen(gui);
        gui->game->selected_level_record_active = 1;
        gui->game->selected_level_record = &gui->game->sub_high_score.survival_pending_record;
        return 1;
      }
    }
  }
  else
  {
    v24 = gui->next_level_button;
    v25 = v24->widget_flags;
    if ( (v25 & 0x20) != 0 )
    {
      LOBYTE(v25) = v25 & 0xDF;
      v24->widget_flags = v25;
      load_frontend_level_by_mode_and_index(
        &gui->game->level_definition,
        gui->game->level_mode,
        ++gui->game->level_mode_arg);
      rstrcpy_checked_ascii(
        (char *)&gui->level_name_widget->text_buffer,
        gui->game->level_definition.level_display_name);
      layout_frontend_widget(gui->level_name_widget);
    }
    v26 = gui->previous_level_button;
    v27 = v26->widget_flags;
    if ( (v27 & 0x20) != 0 )
    {
      LOBYTE(v27) = v27 & 0xDF;
      v26->widget_flags = v27;
      load_frontend_level_by_mode_and_index(
        &gui->game->level_definition,
        gui->game->level_mode,
        --gui->game->level_mode_arg);
      rstrcpy_checked_ascii(
        (char *)&gui->level_name_widget->text_buffer,
        gui->game->level_definition.level_display_name);
      layout_frontend_widget(gui->level_name_widget);
    }
    v28 = gui->previous_level_button;
    v29 = v28->widget_flags;
    if ( gui->game->level_mode_arg )
      v30 = v29 & 0xFFFF7FFF;
    else
      v30 = v29 | 0x8000;
    v28->widget_flags = v30;
    v31 = gui->next_level_button;
    if ( gui->game->level_mode_arg == g_runtime_config.highest_galaxy_route_index )
      v31->widget_flags |= 0x8000u;
    else
      v31->widget_flags &= ~0x8000u;
    back_button = gui->back_button;
    v16 = back_button->widget_flags;
    if ( (v16 & 0x20) != 0 )
      goto LABEL_38;
    play_button = gui->play_button;
    v18 = play_button->widget_flags;
    if ( (v18 & 0x20) != 0 )
    {
LABEL_40:
      LOBYTE(v18) = v18 & 0xDF;
      play_button->widget_flags = v18;
      destroy_challenge_setup_screen(gui);
      return 1;
    }
  }
  return 0;
}
