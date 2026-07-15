/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_main_menu @ 0x419b50 */
/* selector: initialize_main_menu */

// Starts MAINMENU.OGG, loads Menubg.txt into the shared backdrop renderer, seeds the front-end state to menu mode, and allocates the New Game, High Scores, Options, Credits, and Exit widgets. Cross-port Android and iOS symbols match this helper to `cRMainMenu::Init()`.
void __thiscall initialize_main_menu(MainMenu *menu)
{
  int landscape_script_by_name; // eax
  tColour *v3; // eax
  tColour *v4; // eax
  tColour *v5; // eax
  tColour *v6; // eax
  tColour *v7; // eax
  tColour *v8; // eax
  Color4f color; // [esp+4h] [ebp-10h] BYREF

  hide_star_field(&g_game_base->star_manager);
  cache_music_file(g_main_menu_music_path, 0, (char *)g_blank_text);
  landscape_script_by_name = load_landscape_script_by_name(
                               (char *)&g_game_base->subgame.landscape_manager,
                               g_menu_background_script_path);
  change_backdrop(&g_game_base->backdrop, &g_game_base->subgame.landscape_manager.scripts[landscape_script_by_name], 0);
  set_border_justify_centre(&g_game_base->border_manager, 25.0);
  g_game_base->render_skip_count = 2;
  menu->new_game_widget = allocate_border(&g_game_base->border_manager);
  v3 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(menu->new_game_widget, 0x14u, g_new_game_text, 20, 20.0, 90.0, v3, 2, 0.0);
  menu->high_scores_widget = allocate_border(&g_game_base->border_manager);
  v4 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(menu->high_scores_widget, 0x14u, g_high_scores_text, 20, 20.0, 20.0, v4, 2, 0.0);
  stack_widget_below(menu->high_scores_widget, menu->new_game_widget);
  menu->options_widget = allocate_border(&g_game_base->border_manager);
  v5 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(menu->options_widget, 0x14u, g_options_text, 20, 20.0, 20.0, v5, 2, 0.0);
  stack_widget_below(menu->options_widget, menu->high_scores_widget);
  menu->options_widget = allocate_border(&g_game_base->border_manager);
  v6 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(menu->options_widget, 0x14u, g_options_text, 20, 20.0, 20.0, v6, 2, 0.0);
  stack_widget_below(menu->options_widget, menu->high_scores_widget);
  menu->credits_widget = allocate_border(&g_game_base->border_manager);
  v7 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(menu->credits_widget, 0x40000014u, g_credits_text, 20, 20.0, 20.0, v7, 2, 0.0);
  stack_widget_below(menu->credits_widget, menu->options_widget);
  menu->exit_widget = allocate_border(&g_game_base->border_manager);
  v8 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(menu->exit_widget, 0x14u, g_exit_text, 20, 20.0, 390.0, v8, 2, 0.0);
  stack_widget_below(menu->exit_widget, menu->credits_widget);
}
