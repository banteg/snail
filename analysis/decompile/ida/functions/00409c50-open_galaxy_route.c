/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: open_galaxy_route @ 0x409c50 */
/* selector: open_galaxy_route */

// Exact void Windows `Galaxy::open_galaxy_route`: opens a selected Star Map route card, loads its preview label and widget stack, and toggles replay controls. Android and iOS preserve this member as `cRGalaxy::BoxOn(int)`.
void __thiscall open_galaxy_route(Galaxy *galaxy, int32_t selected_level_index)
{
  int32_t v2; // eax
  FrontendWidget *selected_title_widget; // ecx
  double v5; // st7
  FrontendWidget *v6; // [esp-4h] [ebp-14h]
  float v7; // [esp+4h] [ebp-Ch] BYREF
  float v8; // [esp+8h] [ebp-8h] BYREF
  float v9; // [esp+Ch] [ebp-4h] BYREF

  v2 = selected_level_index;
  selected_title_widget = galaxy->selected_title_widget;
  galaxy->route_state = 1;
  galaxy->selected_index = v2;
  unhide_border_init(selected_title_widget);
  rstrcpy_checked_ascii(
    (char *)&galaxy->selected_title_widget->text_buffer,
    galaxy->route_names[galaxy->route_slots[galaxy->selected_index].record.route_name_index].name);
  galaxy->selected_title_widget->layout_anchor_x = galaxy->route_slots[galaxy->selected_index].record.map_x + 60.0;
  galaxy->selected_title_widget->layout_anchor_y = galaxy->route_slots[galaxy->selected_index].record.map_y - 130.0;
  do
  {
    layout_frontend_widget(galaxy->selected_title_widget);
    unhide_border_init(galaxy->selected_detail_widget);
    rstrcpy_checked_ascii(
      (char *)&galaxy->selected_detail_widget->text_buffer,
      galaxy->route_slots[galaxy->selected_index].record.detail_text);
    stack_widget_below(galaxy->selected_detail_widget, galaxy->selected_title_widget);
    unhide_border_init(galaxy->selected_description_widget);
    rstrcpy_checked_ascii(
      (char *)&galaxy->selected_description_widget->text_buffer,
      galaxy->route_slots[galaxy->selected_index].record.description_text);
    stack_widget_below(galaxy->selected_description_widget, galaxy->selected_detail_widget);
    unhide_border_init(galaxy->play_or_deliver_widget);
    galaxy->play_or_deliver_widget->anchor_x = galaxy->selected_title_widget->layout_width * 0.5
                                             + galaxy->selected_title_widget->layout_left
                                             - 320.0;
    stack_widget_below(galaxy->play_or_deliver_widget, galaxy->selected_description_widget);
    if ( galaxy->level_progress_base->sub_high_score.time_trial_route_records[galaxy->selected_index].active == 1
      && galaxy->route_mode == 2 )
    {
      unhide_border_init(galaxy->replay_widget);
      galaxy->replay_widget->anchor_x = galaxy->selected_title_widget->layout_width * 0.5
                                      + galaxy->selected_title_widget->layout_left
                                      - 320.0;
      stack_widget_below(galaxy->replay_widget, galaxy->selected_description_widget);
      stack_widget_below(galaxy->play_or_deliver_widget, galaxy->replay_widget);
    }
    else
    {
      hide_border_init(galaxy->replay_widget);
    }
    unhide_border_init(galaxy->bounds_frame_widget);
    v6 = galaxy->selected_title_widget;
    v8 = 1000.0;
    *(float *)&selected_level_index = -1000.0;
    v9 = 1000.0;
    v7 = -1000.0;
    galaxy_border_bound(galaxy, &v8, (float *)&selected_level_index, &v9, &v7, v6);
    galaxy_border_bound(galaxy, &v8, (float *)&selected_level_index, &v9, &v7, galaxy->selected_detail_widget);
    galaxy_border_bound(galaxy, &v8, (float *)&selected_level_index, &v9, &v7, galaxy->selected_description_widget);
    galaxy_border_bound(galaxy, &v8, (float *)&selected_level_index, &v9, &v7, galaxy->play_or_deliver_widget);
    v7 = v7 + 8.0;
    v8 = v8 - 8.0;
    v5 = *(float *)&selected_level_index + 8.0;
    *(float *)&selected_level_index = v5;
    if ( v5 > 630.0 )
      galaxy->selected_title_widget->layout_anchor_x = galaxy->route_slots[galaxy->selected_index].record.map_x
                                                     - (*(float *)&selected_level_index
                                                      - v8)
                                                     - 40.0;
    if ( v9 < 50.0 )
      galaxy->selected_title_widget->layout_anchor_y = 50.0;
    if ( v7 > 450.0 )
      galaxy->selected_title_widget->layout_anchor_y = 450.0 - (v7 - v9);
  }
  while ( *(float *)&selected_level_index > 631.0 || v9 < 49.0 || v7 > 451.0 );
  galaxy->bounds_frame_widget->authored_width = *(float *)&selected_level_index - v8;
  galaxy->bounds_frame_widget->authored_height = v7 - v9;
  galaxy->bounds_frame_widget->authored_left = v8;
  galaxy->bounds_frame_widget->authored_top = v9;
  galaxy->play_or_deliver_widget->anchor_x = galaxy->bounds_frame_widget->authored_width * 0.5
                                           + galaxy->bounds_frame_widget->authored_left
                                           - 320.0;
  galaxy->replay_widget->anchor_x = galaxy->bounds_frame_widget->authored_width * 0.5
                                  + galaxy->bounds_frame_widget->authored_left
                                  - 320.0;
}
