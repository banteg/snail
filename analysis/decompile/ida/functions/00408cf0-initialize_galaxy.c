/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_galaxy @ 0x408cf0 */
/* selector: initialize_galaxy */

// Exact void Windows `Galaxy::initialize_galaxy`: builds the Star Map, seeds its selected route from SnailMail.cfg, and wires Deliver/Play, replay, and back controls. Android and iOS preserve `cRGalaxy::Init()`.
void __thiscall initialize_galaxy(Galaxy *galaxy)
{
  int landscape_script_by_name; // eax
  SubgameRuntime *level_progress_base; // eax
  int32_t subgame_rebuild_selector; // ecx
  tColour *v5; // eax
  tColour *v6; // eax
  int32_t v7; // ecx
  float *p_highlight_target; // eax
  tColour *v9; // eax
  tColour *v10; // eax
  tColour *v11; // eax
  tColour *v12; // eax
  tColour *v13; // eax
  tColour *v14; // [esp-Ch] [ebp-28h]
  tColour *v15; // [esp-Ch] [ebp-28h]
  tColour *v16; // [esp-Ch] [ebp-28h]
  tColour *v17; // [esp-Ch] [ebp-28h]
  Color4f color; // [esp+Ch] [ebp-10h] BYREF

  hide_star_field(&g_game_base->star_manager);
  cache_music_file(g_main_menu_music_path, 0, (char *)g_blank_text);
  landscape_script_by_name = load_landscape_script_by_name(
                               (char *)&g_game_base->subgame.landscape_manager,
                               aStarmapTxt_0);
  change_backdrop(&g_game_base->backdrop, &g_game_base->subgame.landscape_manager.scripts[landscape_script_by_name], 0);
  set_border_justify_centre(&g_game_base->border_manager, 0.0);
  capture_mouse_cursor(&g_game_base->players[0].mouse_cursor);
  g_game_base->render_skip_count = 2;
  level_progress_base = galaxy->level_progress_base;
  if ( !level_progress_base->level_mode )
  {
    subgame_rebuild_selector = level_progress_base->subgame_rebuild_selector;
    if ( subgame_rebuild_selector == 3 || subgame_rebuild_selector == 2 )
    {
      galaxy->route_state = 0;
      galaxy->route_mode = 0;
      galaxy->selected_index = g_runtime_config.landscape_backdrop_variant_selector;
    }
    if ( level_progress_base->subgame_rebuild_selector == 1 )
    {
      galaxy->route_state = 1;
      galaxy->route_mode = 1;
      galaxy->selected_index = level_progress_base->level_mode_arg;
    }
  }
  if ( level_progress_base->level_mode == 4 )
  {
    galaxy->route_state = 0;
    galaxy->route_mode = 2;
    galaxy->selected_index = g_runtime_config.landscape_backdrop_variant_selector;
  }
  galaxy->route_title_widget = allocate_border(&g_game_base->border_manager);
  v5 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(galaxy->route_title_widget, 0x400000u, aIntergalacticD, 20, 15.0, 15.0, v5, 0, 0.0);
  galaxy->route_title_widget->font_scale = 0.82999998;
  galaxy->route_icon_widget = allocate_border(&g_game_base->border_manager);
  v6 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_sprite_button((int)galaxy->route_icon_widget, 541067266, 138, 1136197632, 1092616192, v6, 0.0, 4);
  galaxy->exit_or_back_widget = allocate_border(&g_game_base->border_manager);
  if ( galaxy->route_mode == 1 )
  {
    v14 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(galaxy->exit_or_back_widget, 0x20000014u, g_exit_text, 20, 20.0, 420.0, v14, 0, 0.0);
  }
  else
  {
    v15 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(galaxy->exit_or_back_widget, 0x60000014u, g_back_text, 20, 20.0, 420.0, v15, 0, 0.0);
  }
  v7 = 0;
  if ( galaxy->record_count > 0 )
  {
    p_highlight_target = &galaxy->route_slots[0].record.highlight_target;
    do
    {
      *(p_highlight_target - 1) = 0.0;
      *p_highlight_target = 0.0;
      ++v7;
      p_highlight_target += 168;
    }
    while ( v7 < galaxy->record_count );
  }
  galaxy->bounds_frame_widget = allocate_border(&g_game_base->border_manager);
  v9 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(galaxy->bounds_frame_widget, 0x20010002u, (char *)g_blank_text, 20, 30.0, 80.0, v9, 0, 0.0);
  store_color4f(&galaxy->bounds_frame_widget->hot_fill_color, 1.0, 1.0, 1.0, 1.0);
  hide_border_init(galaxy->bounds_frame_widget);
  galaxy->bounds_frame_widget->border_texture_id = 152;
  galaxy->bounds_frame_widget->authored_left = 320.0;
  galaxy->bounds_frame_widget->authored_top = 240.0;
  galaxy->bounds_frame_widget->authored_width = 200.0;
  galaxy->bounds_frame_widget->authored_height = 100.0;
  galaxy->selected_title_widget = allocate_border(&g_game_base->border_manager);
  v10 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(
    galaxy->selected_title_widget,
    0x20400002u,
    (char *)g_blank_text,
    20,
    100.0,
    80.0,
    v10,
    0,
    0.0);
  hide_border_init(galaxy->selected_title_widget);
  galaxy->selected_title_widget->font_scale = 0.89999998;
  galaxy->selected_title_widget->stack_gap = 0.0;
  galaxy->selected_detail_widget = allocate_border(&g_game_base->border_manager);
  v11 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(
    galaxy->selected_detail_widget,
    0x20400002u,
    (char *)g_blank_text,
    20,
    300.0,
    440.0,
    v11,
    0,
    0.0);
  hide_border_init(galaxy->selected_detail_widget);
  galaxy->selected_detail_widget->font_scale = 0.89999998;
  galaxy->selected_detail_widget->stack_gap = 0.0;
  galaxy->selected_description_widget = allocate_border(&g_game_base->border_manager);
  v12 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(
    galaxy->selected_description_widget,
    0x20400002u,
    (char *)g_blank_text,
    20,
    300.0,
    440.0,
    v12,
    0,
    0.0);
  hide_border_init(galaxy->selected_description_widget);
  galaxy->selected_description_widget->font_scale = 0.69999999;
  galaxy->selected_description_widget->stack_gap = 0.0;
  galaxy->play_or_deliver_widget = allocate_border(&g_game_base->border_manager);
  if ( galaxy->level_progress_base->level_mode )
  {
    v17 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(galaxy->play_or_deliver_widget, 0x60000014u, aPlay, 20, 300.0, 440.0, v17, 2, 100.0);
  }
  else
  {
    v16 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(galaxy->play_or_deliver_widget, 0x60000014u, aDeliver, 20, 300.0, 440.0, v16, 2, 100.0);
  }
  hide_border_init(galaxy->play_or_deliver_widget);
  galaxy->play_or_deliver_widget->stack_gap = 20.0;
  galaxy->replay_widget = allocate_border(&g_game_base->border_manager);
  v13 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(galaxy->replay_widget, 0x60000014u, aWatchBestTrial, 20, 300.0, 440.0, v13, 2, 0.0);
  hide_border_init(galaxy->replay_widget);
  galaxy->replay_widget->stack_gap = 10.0;
  galaxy->replay_widget->font_scale = 0.80000001;
  galaxy->replay_widget->idle_padding = 4.0;
  galaxy->replay_widget->idle_padding = 8.0;
  open_galaxy_route(galaxy, galaxy->selected_index);
}
