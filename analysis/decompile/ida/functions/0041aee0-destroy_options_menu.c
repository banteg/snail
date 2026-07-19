/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_options_menu @ 0x41aee0 */
/* selector: destroy_options_menu */

// Exact void cROptions::UnInit(): tears down the Options widgets and writes SnailMail.cfg. Its sole Windows caller discards the save_config_file pointer left in EAX.
void __thiscall destroy_options_menu(Options *options)
{
  unhide_all_borders(&g_game_base->border_manager);
  kill_border(&g_game_base->border_manager, options->back_widget);
  kill_border(&g_game_base->border_manager, options->music_volume_widget);
  kill_border(&g_game_base->border_manager, options->sound_volume_widget);
  kill_border(&g_game_base->border_manager, options->fullscreen_widget);
  save_config_file(aSnailmailCfg, &g_runtime_config, 196);
}
