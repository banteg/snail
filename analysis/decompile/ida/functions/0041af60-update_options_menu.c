/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_options_menu @ 0x41af60 */
/* selector: update_options_menu */

// Runs the Options-screen state machine, including fullscreen toggles, slider updates, audio-volume refresh, save, and return to the owning front-end state. Cross-port Android and iOS symbols match this helper to `cROptions::AI()`.
void __thiscall update_options_menu(Options *options)
{
  FrontendWidget *fullscreen_widget; // ecx
  FrontendWidgetFlag widget_flags; // eax
  FrontendWidget *sound_volume_widget; // ecx
  FrontendWidgetFlag v5; // eax
  FrontendWidget *back_widget; // ecx
  FrontendWidgetFlag v7; // eax

  g_runtime_config.stream_volume = options->music_volume_widget->slider_position_target;
  g_runtime_config.sample_volume = options->sound_volume_widget->slider_position_target;
  if ( g_runtime_config.fullscreen_enabled )
    rstrcpy_checked_ascii((char *)&options->fullscreen_widget->text_buffer, g_fullscreen_on_text);
  else
    rstrcpy_checked_ascii((char *)&options->fullscreen_widget->text_buffer, g_fullscreen_off_text);
  fullscreen_widget = options->fullscreen_widget;
  widget_flags = fullscreen_widget->widget_flags;
  if ( (widget_flags & 0x20) != 0 )
  {
    LOBYTE(widget_flags) = widget_flags & 0xDF;
    fullscreen_widget->widget_flags = widget_flags;
    if ( g_runtime_config.fullscreen_enabled )
    {
      set_fullscreen_mode(0);
      g_runtime_config.fullscreen_enabled = 0;
    }
    else
    {
      set_fullscreen_mode(1);
      g_runtime_config.fullscreen_enabled = 1;
    }
  }
  sound_volume_widget = options->sound_volume_widget;
  v5 = sound_volume_widget->widget_flags;
  if ( (v5 & 0x20) != 0 )
  {
    LOBYTE(v5) = v5 & 0xDF;
    sound_volume_widget->widget_flags = v5;
  }
  back_widget = options->back_widget;
  v7 = back_widget->widget_flags;
  if ( (v7 & 0x20) != 0 )
  {
    LOBYTE(v7) = v7 & 0xDF;
    back_widget->widget_flags = v7;
    destroy_options_menu(options);
    g_game_base->unknown_000521[71] = 0;
    g_game_base->players[0].frontend_state = options->previous_frontend_state;
  }
  apply_audio_config_volumes(options);
  if ( options->previous_sample_volume != g_runtime_config.sample_volume )
  {
    play_sound_effect(8);
    options->previous_sample_volume = g_runtime_config.sample_volume;
  }
}
