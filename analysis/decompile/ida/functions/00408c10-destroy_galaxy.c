/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_galaxy @ 0x408c10 */
/* selector: destroy_galaxy */

// Exact Windows `Galaxy::destroy_galaxy`: tears down the active Star Map widgets before replay launch, route handoff, or return. Android preserves `cRGalaxy::UnInit()`.
void __thiscall destroy_galaxy(Galaxy *galaxy)
{
  kill_border(&galaxy->route_title_widget->list_kind);
  kill_border(&galaxy->route_icon_widget->list_kind);
  kill_border(&galaxy->exit_or_back_widget->list_kind);
  kill_border(&galaxy->bounds_frame_widget->list_kind);
  kill_border(&galaxy->selected_title_widget->list_kind);
  kill_border(&galaxy->selected_description_widget->list_kind);
  kill_border(&galaxy->selected_detail_widget->list_kind);
  kill_border(&galaxy->play_or_deliver_widget->list_kind);
  kill_border(&galaxy->replay_widget->list_kind);
}
