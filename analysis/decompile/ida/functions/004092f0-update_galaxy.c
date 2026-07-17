/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_galaxy @ 0x4092f0 */
/* selector: update_galaxy */

// Runs the embedded `Galaxy` Star Map state machine, including route selection, replay launch, Deliver/Play handoff, and the route/icon render pass. Android and iOS split the same ownership between `cRGalaxy::AI()` and `cRGalaxy::Render()`; their trivial `AIControl()` exposes the result state that Windows returns directly.
int32_t __thiscall update_galaxy(Galaxy *galaxy)
{
  int32_t v2; // edi
  GalaxyRouteSlot *route_slots; // ebx
  FrontendWidget *bounds_frame_widget; // edx
  float *v5; // ecx
  double v6; // st7
  int32_t i; // ebp
  float *v8; // edi
  double map_x; // st7
  int32_t v10; // ebp
  float *p_map_x; // edi
  int v12; // edi
  float *v13; // ebp
  int32_t v14; // ebp
  int32_t v15; // ebx
  GameInput *game_input; // eax
  float authored_x; // ecx
  float authored_y; // edx
  int32_t route_state; // eax
  FrontendWidget *v20; // ecx
  int32_t v21; // eax
  float *p_highlight_target; // ecx
  int32_t selected_index; // ecx
  float map_z; // edx
  double v25; // st7
  float *v26; // edi
  double v27; // st7
  double v28; // st7
  FrontendWidget *exit_or_back_widget; // ecx
  FrontendWidgetFlag widget_flags; // eax
  int32_t v32; // edx
  FrontendWidget *play_or_deliver_widget; // ecx
  FrontendWidgetFlag v34; // eax
  SubgameRuntime *level_progress_base; // esi
  FrontendWidget *replay_widget; // ecx
  FrontendWidgetFlag v37; // eax
  int32_t hover_state; // eax
  float x; // [esp+0h] [ebp-7Ch]
  float xa; // [esp+0h] [ebp-7Ch]
  float xb; // [esp+0h] [ebp-7Ch]
  float y; // [esp+4h] [ebp-78h]
  float ya; // [esp+4h] [ebp-78h]
  float yb; // [esp+4h] [ebp-78h]
  tColour *p_color; // [esp+14h] [ebp-68h]
  float v46; // [esp+18h] [ebp-64h]
  float v47; // [esp+20h] [ebp-5Ch]
  float v48; // [esp+44h] [ebp-38h]
  float v49; // [esp+48h] [ebp-34h]
  Vec3 vector; // [esp+50h] [ebp-2Ch] BYREF
  Color4f v51; // [esp+5Ch] [ebp-20h] BYREF
  Color4f color; // [esp+6Ch] [ebp-10h] BYREF

  noop_this_constructor(&color);
  hide_gameplay_scores((FrontendWidget **)galaxy->level_progress_base);
  v2 = 0;
  if ( g_runtime_config.highest_galaxy_route_index >= 0 )
  {
    route_slots = galaxy->route_slots;
    do
    {
      update_galaxy_route_record(route_slots);
      ++v2;
      ++route_slots;
    }
    while ( v2 <= g_runtime_config.highest_galaxy_route_index );
  }
  if ( galaxy->route_state == 1 && (galaxy->bounds_frame_widget->widget_flags & 0x1000) == 0 )
  {
    store_color4f((tColour *)&color, 1.0, 1.0, 1.0, 0.99900001);
    bounds_frame_widget = galaxy->bounds_frame_widget;
    v5 = (float *)(&galaxy->active + 672 * galaxy->selected_index);
    if ( bounds_frame_widget->authored_left <= (double)v5[7] )
    {
      v47 = bounds_frame_widget->authored_width + bounds_frame_widget->authored_left + 6.0;
      v6 = v5[7] - 16.0;
    }
    else
    {
      v47 = bounds_frame_widget->authored_left - 6.0;
      v6 = v5[7] + 16.0;
    }
    v46 = v6;
    draw_galaxy_line(galaxy, 153, v46, v5[8], v47, v5[8], 4.0, (tColour *)&color);
  }
  for ( i = 1; i <= g_runtime_config.highest_galaxy_route_index; ++i )
  {
    v8 = (float *)(&galaxy->active + 672 * i);
    color.r = 1.0;
    color.g = 1.0;
    color.b = 1.0;
    color.a = 0.99000001;
    if ( i )
    {
      if ( galaxy->route_mode == 1 && i > galaxy->selected_index )
        goto LABEL_17;
      p_color = (tColour *)&color;
      y = v8[8] - 16.0;
      map_x = v8[7];
    }
    else
    {
      p_color = set_color_rgba((tColour *)&v51, 1.0, 0.0, 0.0, 0.99000001);
      y = galaxy->route_slots[0].record.map_y - 16.0;
      map_x = galaxy->route_slots[0].record.map_x;
    }
    x = map_x - 16.0;
    queue_axis_aligned_textured_quad_uv(151, x, y, 32.0, 32.0, 0x1000000u, p_color, 0.0, 0.0, 1.0, 1.0, 15, 0.0);
LABEL_17:
    if ( v8[10] > 0.0 )
    {
      color.a = v8[10];
      ya = v8[8] - 32.0;
      xa = v8[7] - 32.0;
      queue_axis_aligned_textured_quad_uv(
        150,
        xa,
        ya,
        64.0,
        64.0,
        0x1000000u,
        (tColour *)&color,
        0.0,
        0.0,
        1.0,
        1.0,
        15,
        0.0);
    }
  }
  set_color_white((tColour *)&color);
  color.a = 0.2;
  v10 = 1;
  if ( g_runtime_config.highest_galaxy_route_index > 1 )
  {
    p_map_x = &galaxy->route_slots[2].record.map_x;
    do
    {
      if ( v10 >= galaxy->selected_index )
      {
        if ( galaxy->route_mode != 1 )
        {
          color.a = 0.2;
          draw_galaxy_line(
            galaxy,
            154,
            *(p_map_x - 168),
            *(p_map_x - 167),
            *p_map_x,
            p_map_x[1],
            4.0,
            (tColour *)&color);
        }
      }
      else
      {
        color.a = 0.80000001;
        draw_galaxy_line(galaxy, 154, *(p_map_x - 168), *(p_map_x - 167), *p_map_x, p_map_x[1], 4.0, (tColour *)&color);
      }
      ++v10;
      p_map_x += 168;
    }
    while ( v10 < g_runtime_config.highest_galaxy_route_index );
  }
  set_color_white((tColour *)&color);
  v12 = 0;
  v13 = &galaxy->route_names[0].map_x;
  do
  {
    yb = v13[1] - 128.0;
    xb = *v13 - 128.0;
    queue_axis_aligned_textured_quad_uv(
      v12 + 139,
      xb,
      yb,
      256.0,
      256.0,
      0x1000000u,
      (tColour *)&color,
      0.0,
      0.0,
      1.0,
      1.0,
      15,
      0.0);
    ++v12;
    v13 += 40;
  }
  while ( v12 < 10 );
  v14 = 1;
  v15 = -1;
  game_input = g_game_base->players[0].game_input;
  authored_x = game_input->input.authored_x;
  authored_y = game_input->input.authored_y;
  route_state = galaxy->route_state;
  v48 = authored_x;
  v49 = authored_y;
  galaxy->hover_state = 0;
  if ( route_state == 1 )
  {
    v20 = galaxy->bounds_frame_widget;
    if ( v20->authored_left - v20->current_padding < v48
      && v20->authored_width + v20->current_padding + v20->authored_left > v48
      && v20->authored_top - v20->current_padding < authored_y
      && v20->authored_height + v20->authored_top + v20->current_padding > authored_y )
    {
      galaxy->hover_state = 1;
      v21 = 1;
      if ( g_runtime_config.highest_galaxy_route_index >= 1 )
      {
        p_highlight_target = &galaxy->route_slots[1].record.highlight_target;
        do
        {
          if ( v21 == galaxy->selected_index )
            *p_highlight_target = 1.0;
          else
            *p_highlight_target = 0.0;
          ++v21;
          p_highlight_target += 168;
        }
        while ( v21 <= g_runtime_config.highest_galaxy_route_index );
      }
    }
  }
  if ( galaxy->route_mode == 1 )
  {
    galaxy->route_slots[galaxy->selected_index].record.highlight_target = 1.0;
  }
  else if ( !galaxy->hover_state )
  {
    if ( galaxy->route_state == 1 )
    {
      selected_index = galaxy->selected_index;
      map_z = galaxy->route_slots[selected_index].record.map_z;
      v51.r = galaxy->route_slots[selected_index].record.map_x - v48;
      v25 = galaxy->route_slots[selected_index].record.map_y - v49;
      v51.b = map_z;
      vector.x = v51.r;
      vector.z = map_z;
      v51.g = v25;
      vector.y = v51.g;
      if ( normalize_vector(&vector) < 17.0 && !galaxy->hover_state )
      {
        v15 = galaxy->selected_index;
        galaxy->hover_state = 2;
        galaxy->route_slots[v15].record.highlight_target = 1.0;
      }
    }
    if ( g_runtime_config.highest_galaxy_route_index >= 1 )
    {
      v26 = &galaxy->route_slots[1].record.highlight_target;
      do
      {
        v27 = *(v26 - 4) - v48;
        v51.b = *(v26 - 2);
        v51.r = v27;
        v28 = *(v26 - 3) - v49;
        vector.z = v51.b;
        vector.x = v51.r;
        v51.g = v28;
        vector.y = v51.g;
        if ( normalize_vector(&vector) >= 17.0 || galaxy->hover_state )
        {
          if ( galaxy->route_state == 1 && v14 == galaxy->selected_index )
            *v26 = 1.0;
          else
            *v26 = 0.0;
        }
        else
        {
          galaxy->hover_state = 2;
          v15 = v14;
          *v26 = 1.0;
        }
        ++v14;
        v26 += 168;
      }
      while ( v14 <= g_runtime_config.highest_galaxy_route_index );
    }
  }
  if ( g_game_base->border_manager.delayed_widget_active )
    return 0;
  exit_or_back_widget = galaxy->exit_or_back_widget;
  widget_flags = exit_or_back_widget->widget_flags;
  if ( (widget_flags & 0x20) == 0 )
  {
    v32 = galaxy->route_state;
    if ( v32 == 1 )
    {
      play_or_deliver_widget = galaxy->play_or_deliver_widget;
      v34 = play_or_deliver_widget->widget_flags;
      if ( (v34 & 0x20) != 0 )
      {
        LOBYTE(v34) = v34 & 0xDF;
        play_or_deliver_widget->widget_flags = v34;
        destroy_galaxy(galaxy);
        galaxy->level_progress_base->level_mode_arg = galaxy->selected_index;
        load_frontend_level_by_mode_and_index(
          &galaxy->level_progress_base->level_definition,
          galaxy->level_progress_base->level_mode,
          galaxy->level_progress_base->level_mode_arg);
        level_progress_base = galaxy->level_progress_base;
        if ( !level_progress_base->level_mode && level_progress_base->subgame_rebuild_selector == 1 )
          return 2;
        return 1;
      }
    }
    replay_widget = galaxy->replay_widget;
    v37 = replay_widget->widget_flags;
    if ( (v37 & 0x20) != 0 )
    {
      LOBYTE(v37) = v37 & 0xDF;
      replay_widget->widget_flags = v37;
      destroy_galaxy(galaxy);
      galaxy->level_progress_base->level_mode_arg = galaxy->selected_index;
      load_frontend_level_by_mode_and_index(
        &galaxy->level_progress_base->level_definition,
        galaxy->level_progress_base->level_mode,
        galaxy->level_progress_base->level_mode_arg);
      galaxy->level_progress_base->selected_level_record_active = 1;
      galaxy->level_progress_base->selected_level_record = &galaxy->level_progress_base->sub_high_score.time_trial_route_records[galaxy->selected_index];
      return 1;
    }
    if ( !g_game_base->fade.state && galaxy->route_mode != 1 )
    {
      hover_state = galaxy->hover_state;
      if ( hover_state != 1 )
      {
        if ( hover_state != 2 || (g_game_base->players[0].game_input->input.pressed_buttons & 0x4000) == 0 )
        {
          if ( hover_state
            || (g_game_base->players[0].game_input->input.pressed_buttons & 0x4000) == 0
            || v32 != 1
            || g_runtime_config.highest_galaxy_route_index <= 1 )
          {
            return 0;
          }
          close_galaxy_route(galaxy);
          goto LABEL_85;
        }
        if ( v15 != galaxy->selected_index )
        {
          if ( v32 == 1 )
          {
            close_galaxy_route(galaxy);
            open_galaxy_route(galaxy, v15);
LABEL_85:
            play_sound_effect(8);
            return 0;
          }
          if ( !v32 )
          {
            open_galaxy_route(galaxy, v15);
            goto LABEL_85;
          }
        }
      }
    }
    return 0;
  }
  LOBYTE(widget_flags) = widget_flags & 0xDF;
  exit_or_back_widget->widget_flags = widget_flags;
  if ( galaxy->route_mode == 1 )
  {
    g_game_base->exit_controller.previous_frontend_state = g_game_base->players[0].frontend_state;
    g_game_base->exit_controller.state = 11;
    g_game_base->players[0].frontend_state = 8;
    return 0;
  }
  else
  {
    destroy_galaxy(galaxy);
    return 3;
  }
}
