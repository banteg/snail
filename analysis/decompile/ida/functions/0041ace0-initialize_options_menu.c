/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_options_menu @ 0x41ace0 */
/* selector: initialize_options_menu */

// Constructs the Options screen widgets, seeds them from SnailMail.cfg, and links the fullscreen, sounds, music, and back controls. Cross-port Android and iOS symbols match this helper to `cROptions::Init()`.
void __thiscall initialize_options_menu(Options *options)
{
  tColour *v2; // eax
  tColour *v3; // eax
  tColour *v4; // eax
  tColour *v5; // eax
  Color4f color; // [esp+4h] [ebp-10h] BYREF

  hide_all_borders((int *)&g_game_base->border_manager);
  g_game_base->unknown_000521[71] = 1;
  options->fullscreen_widget = allocate_border(&g_game_base->border_manager);
  v2 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(options->fullscreen_widget, 0x14u, (char *)g_blank_text, 20, 90.0, 75.0, v2, 2, 0.0);
  options->fullscreen_widget->layout_anchor_y = options->fullscreen_widget->layout_anchor_y + 8.0;
  options->sound_volume_widget = allocate_border(&g_game_base->border_manager);
  v3 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(options->sound_volume_widget, 0x900004u, g_sounds_volume_text, 20, 90.0, 400.0, v3, 2, 0.0);
  stack_widget_below(options->sound_volume_widget, options->fullscreen_widget);
  options->sound_volume_widget->slider_position_target = g_runtime_config.sample_volume;
  options->sound_volume_widget->slider_position_current = g_runtime_config.sample_volume;
  (*(void (__thiscall **)(FrontendWidget *))options->sound_volume_widget->list_kind)(options->sound_volume_widget);
  options->music_volume_widget = allocate_border(&g_game_base->border_manager);
  v4 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(options->music_volume_widget, 0x100004u, g_music_volume_text, 20, 90.0, 400.0, v4, 2, 0.0);
  stack_widget_below(options->music_volume_widget, options->sound_volume_widget);
  options->music_volume_widget->slider_position_target = g_runtime_config.stream_volume;
  options->music_volume_widget->slider_position_current = g_runtime_config.stream_volume;
  (*(void (__thiscall **)(FrontendWidget *))options->music_volume_widget->list_kind)(options->music_volume_widget);
  options->back_widget = allocate_border(&g_game_base->border_manager);
  v5 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(options->back_widget, 0x14u, g_back_text, 20, 90.0, 400.0, v5, 2, 0.0);
  stack_widget_below(options->back_widget, options->music_volume_widget);
  options->previous_sample_volume = g_runtime_config.sample_volume;
}
