/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_galaxy @ 0x408cf0 */
/* selector: initialize_galaxy */

// Exact void Windows `Galaxy::initialize_galaxy`: builds the Star Map, seeds its selected route from SnailMail.cfg, and wires Deliver/Play, replay, and back controls. Android and iOS preserve `cRGalaxy::Init()`.
int __thiscall initialize_galaxy(int this)
{
  int landscape_script_by_name; // eax
  _DWORD *v3; // eax
  int v4; // ecx
  tColour *v5; // eax
  tColour *v6; // eax
  int v7; // ecx
  _DWORD *v8; // eax
  tColour *v9; // eax
  tColour *v10; // eax
  tColour *v11; // eax
  tColour *v12; // eax
  tColour *v13; // eax
  tColour *v15; // [esp-Ch] [ebp-28h]
  tColour *v16; // [esp-Ch] [ebp-28h]
  tColour *v17; // [esp-Ch] [ebp-28h]
  tColour *v18; // [esp-Ch] [ebp-28h]
  Color4f color; // [esp+Ch] [ebp-10h] BYREF

  hide_star_field((StarManager *)&g_game_base->unknown_044100[45628]);
  cache_music_file(g_main_menu_music_path, 0, (char *)g_blank_text);
  landscape_script_by_name = load_landscape_script_by_name(
                               (char *)&g_game_base->subgame.unknown_000044[16743356],
                               aStarmapTxt_0);
  change_backdrop(
    (int)&g_game_base->unknown_044100[43792],
    (int)&g_game_base->subgame.unknown_000044[292 * landscape_script_by_name + 16744800],
    0);
  set_border_justify_centre(&g_game_base->border_manager, 0.0);
  capture_mouse_cursor(&g_game_base->players[0].mouse_cursor);
  g_game_base->render_skip_count = 2;
  v3 = *(_DWORD **)(this + 69488);
  if ( !v3[16] )
  {
    v4 = v3[4834290];
    if ( v4 == 3 || v4 == 2 )
    {
      *(_DWORD *)(this + 8) = 0;
      *(_DWORD *)(this + 4) = 0;
      *(_DWORD *)(this + 69504) = g_runtime_config.landscape_backdrop_variant_selector;
    }
    if ( v3[4834290] == 1 )
    {
      *(_DWORD *)(this + 8) = 1;
      *(_DWORD *)(this + 4) = 1;
      *(_DWORD *)(this + 69504) = v3[17];
    }
  }
  if ( v3[16] == 4 )
  {
    *(_DWORD *)(this + 8) = 0;
    *(_DWORD *)(this + 4) = 2;
    *(_DWORD *)(this + 69504) = g_runtime_config.landscape_backdrop_variant_selector;
  }
  *(_DWORD *)(this + 69496) = allocate_border(&g_game_base->border_manager);
  v5 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(*(FrontendWidget **)(this + 69496), 0x400000u, aIntergalacticD, 20, 15.0, 15.0, v5, 0, 0.0);
  *(_DWORD *)(*(_DWORD *)(this + 69496) + 1776) = 1062501089;
  *(_DWORD *)(this + 69500) = allocate_border(&g_game_base->border_manager);
  v6 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_sprite_button(*(_DWORD *)(this + 69500), 541067266, 138, 1136197632, 1092616192, v6, 0.0, 4);
  *(_DWORD *)(this + 69492) = allocate_border(&g_game_base->border_manager);
  if ( *(_DWORD *)(this + 4) == 1 )
  {
    v15 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(
      *(FrontendWidget **)(this + 69492),
      0x20000014u,
      g_exit_text,
      20,
      20.0,
      420.0,
      v15,
      0,
      0.0);
  }
  else
  {
    v16 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(
      *(FrontendWidget **)(this + 69492),
      0x60000014u,
      g_back_text,
      20,
      20.0,
      420.0,
      v16,
      0,
      0.0);
  }
  v7 = 0;
  if ( *(int *)(this + 12) > 0 )
  {
    v8 = (_DWORD *)(this + 44);
    do
    {
      *(v8 - 1) = 0;
      *v8 = 0;
      ++v7;
      v8 += 168;
    }
    while ( v7 < *(_DWORD *)(this + 12) );
  }
  *(_DWORD *)(this + 69516) = allocate_border(&g_game_base->border_manager);
  v9 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(
    *(FrontendWidget **)(this + 69516),
    0x20010002u,
    (char *)g_blank_text,
    20,
    30.0,
    80.0,
    v9,
    0,
    0.0);
  store_color4f((tColour *)(*(_DWORD *)(this + 69516) + 460), 1.0, 1.0, 1.0, 1.0);
  hide_border_init(*(FrontendWidget **)(this + 69516));
  *(_DWORD *)(*(_DWORD *)(this + 69516) + 72) = 152;
  *(_DWORD *)(*(_DWORD *)(this + 69516) + 76) = 1134559232;
  *(_DWORD *)(*(_DWORD *)(this + 69516) + 80) = 1131413504;
  *(_DWORD *)(*(_DWORD *)(this + 69516) + 84) = 1128792064;
  *(_DWORD *)(*(_DWORD *)(this + 69516) + 88) = 1120403456;
  *(_DWORD *)(this + 69520) = allocate_border(&g_game_base->border_manager);
  v10 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(
    *(FrontendWidget **)(this + 69520),
    0x20400002u,
    (char *)g_blank_text,
    20,
    100.0,
    80.0,
    v10,
    0,
    0.0);
  hide_border_init(*(FrontendWidget **)(this + 69520));
  *(_DWORD *)(*(_DWORD *)(this + 69520) + 1776) = 1063675494;
  *(_DWORD *)(*(_DWORD *)(this + 69520) + 620) = 0;
  *(_DWORD *)(this + 69524) = allocate_border(&g_game_base->border_manager);
  v11 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(
    *(FrontendWidget **)(this + 69524),
    0x20400002u,
    (char *)g_blank_text,
    20,
    300.0,
    440.0,
    v11,
    0,
    0.0);
  hide_border_init(*(FrontendWidget **)(this + 69524));
  *(_DWORD *)(*(_DWORD *)(this + 69524) + 1776) = 1063675494;
  *(_DWORD *)(*(_DWORD *)(this + 69524) + 620) = 0;
  *(_DWORD *)(this + 69528) = allocate_border(&g_game_base->border_manager);
  v12 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(
    *(FrontendWidget **)(this + 69528),
    0x20400002u,
    (char *)g_blank_text,
    20,
    300.0,
    440.0,
    v12,
    0,
    0.0);
  hide_border_init(*(FrontendWidget **)(this + 69528));
  *(_DWORD *)(*(_DWORD *)(this + 69528) + 1776) = 1060320051;
  *(_DWORD *)(*(_DWORD *)(this + 69528) + 620) = 0;
  *(_DWORD *)(this + 69532) = allocate_border(&g_game_base->border_manager);
  if ( *(_DWORD *)(*(_DWORD *)(this + 69488) + 64) )
  {
    v18 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(*(FrontendWidget **)(this + 69532), 0x60000014u, aPlay, 20, 300.0, 440.0, v18, 2, 100.0);
  }
  else
  {
    v17 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(
      *(FrontendWidget **)(this + 69532),
      0x60000014u,
      aDeliver,
      20,
      300.0,
      440.0,
      v17,
      2,
      100.0);
  }
  hide_border_init(*(FrontendWidget **)(this + 69532));
  *(_DWORD *)(*(_DWORD *)(this + 69532) + 620) = 1101004800;
  *(_DWORD *)(this + 69536) = allocate_border(&g_game_base->border_manager);
  v13 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(
    *(FrontendWidget **)(this + 69536),
    0x60000014u,
    aWatchBestTrial,
    20,
    300.0,
    440.0,
    v13,
    2,
    0.0);
  hide_border_init(*(FrontendWidget **)(this + 69536));
  *(_DWORD *)(*(_DWORD *)(this + 69536) + 620) = 1092616192;
  *(_DWORD *)(*(_DWORD *)(this + 69536) + 1776) = 1061997773;
  *(_DWORD *)(*(_DWORD *)(this + 69536) + 532) = 1082130432;
  *(_DWORD *)(*(_DWORD *)(this + 69536) + 532) = 1090519040;
  return open_galaxy_route(this, *(float *)(this + 69504));
}
