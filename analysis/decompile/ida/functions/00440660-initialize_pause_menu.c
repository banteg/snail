/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_pause_menu @ 0x440660 */
/* selector: initialize_pause_menu */

// Allocates and configures the Options, End Game, and Resume widgets on the embedded cRSubPause owner. Cross-port iOS and Android symbols identify the void method as cRSubPause::Init(); the Windows reconstruction is exact at 88/88 instructions.
void __thiscall initialize_pause_menu(SubPause *pause)
{
  tColour *v2; // eax
  tColour *v3; // eax
  tColour *v4; // eax
  Color4f color; // [esp+4h] [ebp-10h] BYREF

  pause->end_game_widget = allocate_border(&g_game_base->border_manager);
  v2 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(pause->end_game_widget, 0x14u, g_end_game_text, 20, 0.0, 145.0, v2, 2, 0.0);
  set_frontend_widget_shortcut_key(pause->end_game_widget, 11);
  pause->options_widget = allocate_border(&g_game_base->border_manager);
  v3 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 0.029999999);
  initialize_frontend_widget(pause->options_widget, 0x14u, g_options_text, 20, 0.0, 190.0, v3, 2, 0.0);
  set_frontend_widget_shortcut_key(pause->options_widget, 111);
  layout_frontend_widget(pause->options_widget);
  stack_widget_below(pause->options_widget, pause->end_game_widget);
  pause->resume_widget = allocate_border(&g_game_base->border_manager);
  v4 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(pause->resume_widget, 0x14u, g_resume_text, 20, 0.0, 320.0, v4, 2, 0.0);
  set_frontend_widget_shortcut_key(pause->resume_widget, 5);
  stack_widget_below(pause->resume_widget, pause->options_widget);
  capture_mouse_cursor(&g_game_base->players[0].mouse_cursor);
}
