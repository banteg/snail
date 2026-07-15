/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_challenge_setup_screen @ 0x415f50 */
/* selector: initialize_challenge_setup_screen */

// Void `cRGUI::Init()`: builds the mode-specific postal, challenge, or time-trial level-selection controls. Mode 1 adds Select Difficulty, Select Speed, Play, Watch Replay, and Back widgets. The sole Windows caller discards EAX; the honest void transcription is 167/167 instructions at 96.41%.
void __thiscall initialize_challenge_setup_screen(GUI *gui)
{
  tColour *v2; // eax
  tColour *v3; // eax
  tColour *v4; // eax
  tColour *v5; // eax
  tColour *v6; // eax
  float anchor_x; // [esp+4h] [ebp-54h]
  Color4f color; // [esp+8h] [ebp-50h] BYREF
  Color4f v9; // [esp+18h] [ebp-40h] BYREF
  Color4f v10; // [esp+28h] [ebp-30h] BYREF
  Color4f v11; // [esp+38h] [ebp-20h] BYREF
  Color4f v12; // [esp+48h] [ebp-10h] BYREF

  capture_mouse_cursor(&g_game_base->players[0].mouse_cursor);
  load_frontend_level_by_mode_and_index(&gui->game->level_definition, gui->game->level_mode, gui->game->level_mode_arg);
  if ( gui->game->level_mode == 1 )
  {
    gui->difficulty_slider = allocate_border(&g_game_base->border_manager);
    v2 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(gui->difficulty_slider, 0x100004u, aSelectDifficul, 20, 20.0, 80.0, v2, 2, 0.0);
    gui->difficulty_slider->slider_position_target = (double)g_runtime_config.completion_bonus_y_source * 0.0099999998;
    gui->difficulty_slider->slider_position_current = gui->difficulty_slider->slider_position_target;
    (*(void (__thiscall **)(FrontendWidget *))gui->difficulty_slider->list_kind)(gui->difficulty_slider);
    gui->speed_slider = allocate_border(&g_game_base->border_manager);
    v3 = set_color_rgba((tColour *)&v9, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(gui->speed_slider, 0x100004u, aSelectSpeed, 20, 20.0, 145.0, v3, 2, 0.0);
    gui->speed_slider->slider_position_target = (double)g_runtime_config.completion_bonus_x_source * 0.0099999998;
    gui->speed_slider->slider_position_current = gui->speed_slider->slider_position_target;
    stack_widget_below(gui->speed_slider, gui->difficulty_slider);
    (*(void (__thiscall **)(FrontendWidget *))gui->speed_slider->list_kind)(gui->speed_slider);
    anchor_x = 0.0;
    if ( gui->game->sub_high_score.survival_pending_record.active == 1 )
      anchor_x = 100.0;
    gui->play_button = allocate_border(&g_game_base->border_manager);
    v4 = set_color_rgba((tColour *)&v10, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(gui->play_button, 0x40000016u, aPlay, 20, 20.0, 250.0, v4, 2, anchor_x);
    stack_widget_below(gui->play_button, gui->speed_slider);
    gui->replay_button = allocate_border(&g_game_base->border_manager);
    v5 = set_color_rgba((tColour *)&v11, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(gui->replay_button, 0x40000016u, aWatchReplay, 20, 20.0, 70.0, v5, 2, -100.0);
    stack_widget_below(gui->replay_button, gui->speed_slider);
    if ( gui->game->sub_high_score.survival_pending_record.active != 1 )
      hide_border_init(gui->replay_button);
    gui->back_button = allocate_border(&g_game_base->border_manager);
    v6 = set_color_rgba((tColour *)&v12, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(gui->back_button, 0x16u, g_back_text, 20, 20.0, 20.0, v6, 2, 0.0);
    stack_widget_below(gui->back_button, gui->replay_button);
  }
}
