/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: close_galaxy_route @ 0x409bf0 */
/* selector: close_galaxy_route */

// Exact Windows `Galaxy::close_galaxy_route`: closes the active Star Map route card and clears its replay/play controls. Android and iOS preserve `cRGalaxy::BoxOff()`.
void __thiscall close_galaxy_route(Galaxy *galaxy)
{
  FrontendWidget *bounds_frame_widget; // ecx

  bounds_frame_widget = galaxy->bounds_frame_widget;
  galaxy->route_state = 0;
  galaxy->selected_index = -1;
  hide_border_init(bounds_frame_widget);
  hide_border_init(galaxy->selected_title_widget);
  hide_border_init(galaxy->selected_detail_widget);
  hide_border_init(galaxy->selected_description_widget);
  hide_border_init(galaxy->play_or_deliver_widget);
  hide_border_init(galaxy->replay_widget);
}
