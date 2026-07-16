/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_galaxy @ 0x4092f0 */
/* selector: update_galaxy */

// Runs the embedded `Galaxy` Star Map state machine, including route selection, replay launch, Deliver/Play handoff, and the route/icon render pass. Android and iOS split the same ownership between `cRGalaxy::AI()` and `cRGalaxy::Render()`; their trivial `AIControl()` exposes the result state that Windows returns directly.
int __thiscall update_galaxy(FrontendWidget ***this)
{
  int32_t v2; // edi
  float *v3; // ebx
  int v4; // edx
  FrontendWidget ***v5; // ecx
  double v6; // st7
  int32_t i; // ebp
  float *v8; // edi
  double v9; // st7
  int32_t v10; // ebp
  float *v11; // edi
  int v12; // edi
  float *v13; // ebp
  int32_t v14; // ebp
  float v15; // ebx
  GameInput *game_input; // eax
  float authored_x; // ecx
  float authored_y; // edx
  int v19; // eax
  float *v20; // ecx
  int32_t v21; // eax
  FrontendWidget ***v22; // ecx
  int v23; // ecx
  float v24; // edx
  double v25; // st7
  FrontendWidget ***v26; // edi
  double v27; // st7
  double v28; // st7
  int v29; // ecx
  int v30; // eax
  int v32; // edx
  int v33; // ecx
  int v34; // eax
  int v35; // esi
  int v36; // ecx
  int v37; // eax
  int v38; // eax
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
  hide_gameplay_scores(*(this + 17372));
  v2 = 0;
  if ( g_runtime_config.highest_galaxy_route_index >= 0 )
  {
    v3 = (float *)(this + 4);
    do
    {
      update_galaxy_route_record(v3);
      ++v2;
      v3 += 168;
    }
    while ( v2 <= g_runtime_config.highest_galaxy_route_index );
  }
  if ( *(this + 2) == (FrontendWidget **)1 && (((unsigned __int16)(*(this + 17379))[104] >> 8) & 0x10) == 0 )
  {
    store_color4f((tColour *)&color, 1.0, 1.0, 1.0, 0.99900001);
    v4 = (int)*(this + 17379);
    v5 = this + 168 * (_DWORD)*(this + 17376);
    if ( *(float *)(v4 + 76) <= (double)*((float *)v5 + 7) )
    {
      v47 = *(float *)(v4 + 84) + *(float *)(v4 + 76) + 6.0;
      v6 = *((float *)v5 + 7) - 16.0;
    }
    else
    {
      v47 = *(float *)(v4 + 76) - 6.0;
      v6 = *((float *)v5 + 7) + 16.0;
    }
    v46 = v6;
    draw_galaxy_line(153, v46, *((float *)v5 + 8), v47, *((float *)v5 + 8), 4.0, (tColour *)&color);
  }
  for ( i = 1; i <= g_runtime_config.highest_galaxy_route_index; ++i )
  {
    v8 = (float *)(this + 168 * i);
    color.r = 1.0;
    color.g = 1.0;
    color.b = 1.0;
    color.a = 0.99000001;
    if ( i )
    {
      if ( *(this + 1) == (FrontendWidget **)1 && i > (int)*(this + 17376) )
        goto LABEL_17;
      p_color = (tColour *)&color;
      y = v8[8] - 16.0;
      v9 = v8[7];
    }
    else
    {
      p_color = set_color_rgba((tColour *)&v51, 1.0, 0.0, 0.0, 0.99000001);
      y = *((float *)this + 8) - 16.0;
      v9 = *((float *)this + 7);
    }
    x = v9 - 16.0;
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
    v11 = (float *)(this + 343);
    do
    {
      if ( v10 >= (int)*(this + 17376) )
      {
        if ( *(this + 1) != (FrontendWidget **)1 )
        {
          color.a = 0.2;
          draw_galaxy_line(154, *(v11 - 168), *(v11 - 167), *v11, v11[1], 4.0, (tColour *)&color);
        }
      }
      else
      {
        color.a = 0.80000001;
        draw_galaxy_line(154, *(v11 - 168), *(v11 - 167), *v11, v11[1], 4.0, (tColour *)&color);
      }
      ++v10;
      v11 += 168;
    }
    while ( v10 < g_runtime_config.highest_galaxy_route_index );
  }
  set_color_white((tColour *)&color);
  v12 = 0;
  v13 = (float *)(this + 17009);
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
  v15 = NAN;
  game_input = g_game_base->players[0].game_input;
  authored_x = game_input->input.authored_x;
  authored_y = game_input->input.authored_y;
  v19 = (int)*(this + 2);
  v48 = authored_x;
  v49 = authored_y;
  *(this + 17377) = nullptr;
  if ( v19 == 1 )
  {
    v20 = (float *)*(this + 17379);
    if ( v20[19] - v20[136] < v48
      && v20[21] + v20[136] + v20[19] > v48
      && v20[20] - v20[136] < authored_y
      && v20[22] + v20[20] + v20[136] > authored_y )
    {
      *(this + 17377) = (FrontendWidget **)1;
      v21 = 1;
      if ( g_runtime_config.highest_galaxy_route_index >= 1 )
      {
        v22 = this + 179;
        do
        {
          if ( (FrontendWidget **)v21 == *(this + 17376) )
            *v22 = (FrontendWidget **)1065353216;
          else
            *v22 = nullptr;
          ++v21;
          v22 += 168;
        }
        while ( v21 <= g_runtime_config.highest_galaxy_route_index );
      }
    }
  }
  if ( *(this + 1) == (FrontendWidget **)1 )
  {
    *(this + 168 * (_DWORD)*(this + 17376) + 11) = (FrontendWidget **)1065353216;
  }
  else if ( !*(this + 17377) )
  {
    if ( *(this + 2) == (FrontendWidget **)1 )
    {
      v23 = 672 * (_DWORD)*(this + 17376);
      v24 = *(float *)((char *)this + v23 + 36);
      v51.r = *(float *)((char *)this + v23 + 28) - v48;
      v25 = *(float *)((char *)this + v23 + 32) - v49;
      v51.b = v24;
      vector.x = v51.r;
      vector.z = v24;
      v51.g = v25;
      vector.y = v51.g;
      if ( normalize_vector(&vector) < 17.0 && !*(this + 17377) )
      {
        v15 = *((float *)this + 17376);
        *(this + 17377) = (FrontendWidget **)2;
        *(this + 168 * LODWORD(v15) + 11) = (FrontendWidget **)1065353216;
      }
    }
    if ( g_runtime_config.highest_galaxy_route_index >= 1 )
    {
      v26 = this + 179;
      do
      {
        v27 = *((float *)v26 - 4) - v48;
        LODWORD(v51.b) = *(v26 - 2);
        v51.r = v27;
        v28 = *((float *)v26 - 3) - v49;
        vector.z = v51.b;
        vector.x = v51.r;
        v51.g = v28;
        vector.y = v51.g;
        if ( normalize_vector(&vector) >= 17.0 || *(this + 17377) )
        {
          if ( *(this + 2) == (FrontendWidget **)1 && (FrontendWidget **)v14 == *(this + 17376) )
            *v26 = (FrontendWidget **)1065353216;
          else
            *v26 = nullptr;
        }
        else
        {
          *(this + 17377) = (FrontendWidget **)2;
          v15 = *(float *)&v14;
          *v26 = (FrontendWidget **)1065353216;
        }
        ++v14;
        v26 += 168;
      }
      while ( v14 <= g_runtime_config.highest_galaxy_route_index );
    }
  }
  if ( g_game_base->border_manager.delayed_widget_active )
    return 0;
  v29 = (int)*(this + 17373);
  v30 = *(_DWORD *)(v29 + 416);
  if ( (v30 & 0x20) == 0 )
  {
    v32 = (int)*(this + 2);
    if ( v32 == 1 )
    {
      v33 = (int)*(this + 17383);
      v34 = *(_DWORD *)(v33 + 416);
      if ( (v34 & 0x20) != 0 )
      {
        LOBYTE(v34) = v34 & 0xDF;
        *(_DWORD *)(v33 + 416) = v34;
        destroy_galaxy(this);
        (*(this + 17372))[17] = (FrontendWidget *)*(this + 17376);
        load_frontend_level_by_mode_and_index(
          (SubTracks *)(*(this + 17372) + 10781),
          (int)(*(this + 17372))[16],
          (int)(*(this + 17372))[17]);
        v35 = (int)*(this + 17372);
        if ( !*(_DWORD *)(v35 + 64) && *(_DWORD *)(v35 + 19337160) == 1 )
          return 2;
        return 1;
      }
    }
    v36 = (int)*(this + 17384);
    v37 = *(_DWORD *)(v36 + 416);
    if ( (v37 & 0x20) != 0 )
    {
      LOBYTE(v37) = v37 & 0xDF;
      *(_DWORD *)(v36 + 416) = v37;
      destroy_galaxy(this);
      (*(this + 17372))[17] = (FrontendWidget *)*(this + 17376);
      load_frontend_level_by_mode_and_index(
        (SubTracks *)(*(this + 17372) + 10781),
        (int)(*(this + 17372))[16],
        (int)(*(this + 17372))[17]);
      *((_BYTE *)*(this + 17372) + 16721360) = 1;
      (*(this + 17372))[4180341] = (FrontendWidget *)&(*(this + 17372))[32432 * (_DWORD)*(this + 17376) + 2429012];
      return 1;
    }
    if ( !g_game_base->fade.state && *(this + 1) != (FrontendWidget **)1 )
    {
      v38 = (int)*(this + 17377);
      if ( v38 != 1 )
      {
        if ( v38 != 2 || (g_game_base->players[0].game_input->input.pressed_buttons & 0x4000) == 0 )
        {
          if ( v38
            || (g_game_base->players[0].game_input->input.pressed_buttons & 0x4000) == 0
            || v32 != 1
            || g_runtime_config.highest_galaxy_route_index <= 1 )
          {
            return 0;
          }
          close_galaxy_route((int)this);
          goto LABEL_85;
        }
        if ( (FrontendWidget **)LODWORD(v15) != *(this + 17376) )
        {
          if ( v32 == 1 )
          {
            close_galaxy_route((int)this);
            open_galaxy_route((int)this, v15);
LABEL_85:
            play_sound_effect(8);
            return 0;
          }
          if ( !v32 )
          {
            open_galaxy_route((int)this, v15);
            goto LABEL_85;
          }
        }
      }
    }
    return 0;
  }
  LOBYTE(v30) = v30 & 0xDF;
  *(_DWORD *)(v29 + 416) = v30;
  if ( *(this + 1) == (FrontendWidget **)1 )
  {
    g_game_base->exit_controller.previous_frontend_state = g_game_base->players[0].frontend_state;
    g_game_base->exit_controller.state = 11;
    g_game_base->players[0].frontend_state = 8;
    return 0;
  }
  else
  {
    destroy_galaxy(this);
    return 3;
  }
}
