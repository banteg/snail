/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_galaxy @ 0x408c10 */
/* selector: destroy_galaxy */

// Exact Windows `Galaxy::destroy_galaxy`: tears down the active Star Map widgets before replay launch, route handoff, or return. Android preserves `cRGalaxy::UnInit()`.
void __thiscall destroy_galaxy(Galaxy *galaxy)
{
  kill_border(&g_game_base->border_manager, galaxy->route_title_widget);
  kill_border(&g_game_base->border_manager, galaxy->route_icon_widget);
  kill_border(&g_game_base->border_manager, galaxy->exit_or_back_widget);
  kill_border(&g_game_base->border_manager, galaxy->bounds_frame_widget);
  kill_border(&g_game_base->border_manager, galaxy->selected_title_widget);
  kill_border(&g_game_base->border_manager, galaxy->selected_description_widget);
  kill_border(&g_game_base->border_manager, galaxy->selected_detail_widget);
  kill_border(&g_game_base->border_manager, galaxy->play_or_deliver_widget);
  kill_border(&g_game_base->border_manager, galaxy->replay_widget);
}
