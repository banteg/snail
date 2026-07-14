/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_default_runtime_config @ 0x406c20 */
/* selector: initialize_default_runtime_config */

// Seeds the 0xc4-byte SnailMail.cfg blob with default sound volume, music volume, fullscreen, progression, and tuning values before any file overlay is loaded.
void __cdecl initialize_default_runtime_config()
{
  g_runtime_config.fullscreen_enabled = 1;
  g_runtime_config.render_flags = RUNTIME_RENDER_32_BIT_COLOR|RUNTIME_RENDER_FONT_WAVE|RUNTIME_RENDER_TRACK_FRINGE|RUNTIME_RENDER_PARTICLE_EFFECTS|RUNTIME_RENDER_STAR_FIELD|0xCA;
  g_runtime_config.load_valid_flag = 1;
  g_runtime_config.validation_tail[0] = 0;
  g_runtime_config.display_mode_index = 1;
  g_runtime_config.stream_volume = 0.60000002;
  g_runtime_config.sample_volume = 0.60000002;
  g_runtime_config.reserved_18 = 0;
  g_runtime_config.reserved_14 = 0;
  g_runtime_config.reserved_0c = 0;
  g_runtime_config.reserved_10 = 0;
  g_runtime_config.steering_sensitivity[0] = 0.75;
  g_runtime_config.steering_sensitivity[1] = 0.75;
  g_runtime_config.completion_bonus_x_source = 40;
  g_runtime_config.completion_bonus_y_source = 40;
  g_runtime_config.default_challenge_speed_slider = 0.30000001;
  g_runtime_config.reserved_4c = 0;
  g_runtime_config.reserved_4d = 0;
  g_runtime_config.high_score_selected_bank = 0;
  g_runtime_config.reserved_50 = 0;
  g_runtime_config.reserved_54 = 0;
  g_runtime_config.reserved_58 = 0;
  g_runtime_config.reserved_5c = 0;
  g_runtime_config.last_entered_player_name[0] = 0;
  g_runtime_config.highest_galaxy_route_index = 1;
  g_runtime_config.landscape_backdrop_variant_selector = 1;
  g_runtime_config.last_loading_budget = 1;
  g_runtime_config.reserved_b0 = 10.0;
  g_runtime_config.reserved_b4 = 2.5;
  g_runtime_config.reserved_b8 = -1.5;
  g_runtime_config.reserved_bc = -1.0;
  g_runtime_config.new_game_tutorial_started = 0;
}
