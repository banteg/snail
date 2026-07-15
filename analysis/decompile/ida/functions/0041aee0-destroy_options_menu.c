/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_options_menu @ 0x41aee0 */
/* selector: destroy_options_menu */

// Exact void cROptions::UnInit(): tears down the Options widgets and writes SnailMail.cfg. Its sole Windows caller discards the save_config_file pointer left in EAX.
void __thiscall destroy_options_menu(Options *options)
{
  unhide_all_borders((int *)&g_game_base->border_manager);
  kill_border(&options->back_widget->list_kind);
  kill_border(&options->music_volume_widget->list_kind);
  kill_border(&options->sound_volume_widget->list_kind);
  kill_border(&options->fullscreen_widget->list_kind);
  save_config_file(aSnailmailCfg, (CompletionResultScreen *)&g_runtime_config, (FrontendWidget *)0xC4);
}
