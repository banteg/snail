/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_new_game_menu @ 0x417bc0 */
/* selector: initialize_new_game_menu */

// Exact Windows `cRIntro::Init()`: builds the New Game mode submenu with Tutorial, Postal Mode, Time Trial, Challenge Mode, Help, and Back after reloading the shared menu backdrop and shell-font scene. The root-owned 0x48-byte Intro at `data_4df904 + 0x4f2dc` retains its replay-attract controller across initialization.
void __thiscall initialize_new_game_menu(Intro *intro)
{
  int landscape_script_by_name; // eax
  tColour *v3; // eax
  tColour *v4; // eax
  tColour *v5; // eax
  tColour *v6; // eax
  tColour *v7; // eax
  tColour *v8; // eax
  Color4f color; // [esp+4h] [ebp-10h] BYREF

  hide_star_field((StarManager *)&g_game_base->unknown_044100[45628]);
  cache_music_file(g_main_menu_music_path, 0, (char *)g_blank_text);
  landscape_script_by_name = load_landscape_script_by_name(
                               (char *)&g_game_base->subgame.unknown_000044[16743356],
                               g_menu_background_script_path);
  change_backdrop(
    (int)&g_game_base->unknown_044100[43792],
    (int)&g_game_base->subgame.unknown_000044[292 * landscape_script_by_name + 16744800],
    0);
  set_border_justify_centre(&g_game_base->border_manager, 25.0);
  g_game_base->render_skip_count = 2;
  intro->tutorial_button = allocate_border(&g_game_base->border_manager);
  v3 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(intro->tutorial_button, 0x40000014u, g_tutorial_text, 20, 20.0, 80.0, v3, 2, 0.0);
  intro->postal_button = allocate_border(&g_game_base->border_manager);
  v4 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(intro->postal_button, 0x40000014u, g_postal_mode_text, 20, 20.0, 20.0, v4, 2, 0.0);
  stack_widget_below(intro->postal_button, intro->tutorial_button);
  intro->time_trial_button = allocate_border(&g_game_base->border_manager);
  v5 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(intro->time_trial_button, 0x40000014u, g_time_trial_text, 20, 20.0, 20.0, v5, 2, 0.0);
  stack_widget_below(intro->time_trial_button, intro->postal_button);
  intro->challenge_button = allocate_border(&g_game_base->border_manager);
  v6 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(intro->challenge_button, 0x14u, g_challenge_mode_text, 20, 20.0, 20.0, v6, 2, 0.0);
  stack_widget_below(intro->challenge_button, intro->time_trial_button);
  intro->help_button = allocate_border(&g_game_base->border_manager);
  v7 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(intro->help_button, 0x40000014u, g_help_text, 20, 0.0, 350.0, v7, 2, -220.0);
  intro->back_button = allocate_border(&g_game_base->border_manager);
  v8 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(intro->back_button, 0x14u, g_back_text, 20, 20.0, 350.0, v8, 2, 0.0);
  stack_widget_below(intro->back_button, intro->challenge_button);
  if ( !g_runtime_config.new_game_tutorial_started )
  {
    intro->postal_button->widget_flags |= 0x8000u;
    intro->time_trial_button->widget_flags |= 0x8000u;
    intro->challenge_button->widget_flags |= 0x8000u;
  }
}
