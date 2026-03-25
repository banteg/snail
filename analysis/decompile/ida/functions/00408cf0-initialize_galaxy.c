/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_galaxy @ 0x408cf0 */
/* selector: initialize_galaxy */

// Builds the Star Map galaxy screen, seeds its selected route from SnailMail.cfg, and wires the Deliver/Play, replay, and back controls. Cross-port Android and iOS symbols match this helper to `cRGalaxy::Init()`.
int __thiscall sub_408CF0(int this)
{
  int v2; // eax
  _DWORD *v3; // eax
  int v4; // ecx
  _DWORD *v5; // eax
  _DWORD *v6; // eax
  int v7; // ecx
  _DWORD *v8; // eax
  _DWORD *v9; // eax
  _DWORD *v10; // eax
  _DWORD *v11; // eax
  _DWORD *v12; // eax
  _DWORD *v13; // eax
  _DWORD *v15; // [esp-Ch] [ebp-28h]
  _DWORD *v16; // [esp-Ch] [ebp-28h]
  _DWORD *v17; // [esp-Ch] [ebp-28h]
  _DWORD *v18; // [esp-Ch] [ebp-28h]
  _DWORD v19[4]; // [esp+Ch] [ebp-10h] BYREF

  hide_star_field((int *)MEMORY[0x4DF904] + 81103);
  cache_music_file(aMusicMainmenuO);
  v2 = load_landscape_script_by_name((char *)MEMORY[0x4DF904] + 17220120, aStarmapTxt_0);
  change_backdrop((int)MEMORY[0x4DF904] + 322576, (int)MEMORY[0x4DF904] + 292 * v2 + 17221564, 0);
  set_border_justify_centre((_DWORD *)MEMORY[0x4DF904] + 723, 0);
  capture_mouse_cursor((float *)MEMORY[0x4DF904] + 164);
  *((_DWORD *)MEMORY[0x4DF904] + 347) = 2;
  v3 = *(_DWORD **)(this + 69488);
  if ( !v3[16] )
  {
    v4 = v3[4834290];
    if ( v4 == 3 || v4 == 2 )
    {
      *(_DWORD *)(this + 8) = 0;
      *(_DWORD *)(this + 4) = 0;
      *(_DWORD *)(this + 69504) = unk_4DF9BC;
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
    *(_DWORD *)(this + 69504) = unk_4DF9BC;
  }
  *(_DWORD *)(this + 69496) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v5 = set_color_rgba(v19, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(
    *(_DWORD *)(this + 69496),
    0x400000,
    aIntergalacticD,
    20,
    1097859072,
    15.0,
    (int)v5,
    0,
    0.0);
  *(_DWORD *)(*(_DWORD *)(this + 69496) + 1776) = 1062501089;
  *(_DWORD *)(this + 69500) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v6 = set_color_rgba(v19, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_sprite_button(*(_DWORD *)(this + 69500), 541067266, 138, 1136197632, 1092616192, v6, 0.0, 4);
  *(_DWORD *)(this + 69492) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  if ( *(_DWORD *)(this + 4) == 1 )
  {
    v15 = set_color_rgba(v19, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_widget(*(_DWORD *)(this + 69492), 536870932, aExit, 20, 1101004800, 420.0, (int)v15, 0, 0.0);
  }
  else
  {
    v16 = set_color_rgba(v19, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_widget(*(_DWORD *)(this + 69492), 1610612756, aBack, 20, 1101004800, 420.0, (int)v16, 0, 0.0);
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
  *(_DWORD *)(this + 69516) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v9 = set_color_rgba(v19, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(
    *(_DWORD *)(this + 69516),
    536936450,
    MEMORY[0x4DFB08],
    20,
    1106247680,
    80.0,
    (int)v9,
    0,
    0.0);
  store_color4f((_DWORD *)(*(_DWORD *)(this + 69516) + 460), 1065353216, 1065353216, 1065353216, 1065353216);
  hide_border_init(*(_DWORD **)(this + 69516));
  *(_DWORD *)(*(_DWORD *)(this + 69516) + 72) = 152;
  *(_DWORD *)(*(_DWORD *)(this + 69516) + 76) = 1134559232;
  *(_DWORD *)(*(_DWORD *)(this + 69516) + 80) = 1131413504;
  *(_DWORD *)(*(_DWORD *)(this + 69516) + 84) = 1128792064;
  *(_DWORD *)(*(_DWORD *)(this + 69516) + 88) = 1120403456;
  *(_DWORD *)(this + 69520) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v10 = set_color_rgba(v19, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(
    *(_DWORD *)(this + 69520),
    541065218,
    MEMORY[0x4DFB08],
    20,
    1120403456,
    80.0,
    (int)v10,
    0,
    0.0);
  hide_border_init(*(_DWORD **)(this + 69520));
  *(_DWORD *)(*(_DWORD *)(this + 69520) + 1776) = 1063675494;
  *(_DWORD *)(*(_DWORD *)(this + 69520) + 620) = 0;
  *(_DWORD *)(this + 69524) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v11 = set_color_rgba(v19, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(
    *(_DWORD *)(this + 69524),
    541065218,
    MEMORY[0x4DFB08],
    20,
    1133903872,
    440.0,
    (int)v11,
    0,
    0.0);
  hide_border_init(*(_DWORD **)(this + 69524));
  *(_DWORD *)(*(_DWORD *)(this + 69524) + 1776) = 1063675494;
  *(_DWORD *)(*(_DWORD *)(this + 69524) + 620) = 0;
  *(_DWORD *)(this + 69528) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v12 = set_color_rgba(v19, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(
    *(_DWORD *)(this + 69528),
    541065218,
    MEMORY[0x4DFB08],
    20,
    1133903872,
    440.0,
    (int)v12,
    0,
    0.0);
  hide_border_init(*(_DWORD **)(this + 69528));
  *(_DWORD *)(*(_DWORD *)(this + 69528) + 1776) = 1060320051;
  *(_DWORD *)(*(_DWORD *)(this + 69528) + 620) = 0;
  *(_DWORD *)(this + 69532) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  if ( *(_DWORD *)(*(_DWORD *)(this + 69488) + 64) )
  {
    v18 = set_color_rgba(v19, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_widget(*(_DWORD *)(this + 69532), 1610612756, aPlay, 20, 1133903872, 440.0, (int)v18, 2, 100.0);
  }
  else
  {
    v17 = set_color_rgba(v19, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_widget(
      *(_DWORD *)(this + 69532),
      1610612756,
      aDeliver,
      20,
      1133903872,
      440.0,
      (int)v17,
      2,
      100.0);
  }
  hide_border_init(*(_DWORD **)(this + 69532));
  *(_DWORD *)(*(_DWORD *)(this + 69532) + 620) = 1101004800;
  *(_DWORD *)(this + 69536) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v13 = set_color_rgba(v19, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(
    *(_DWORD *)(this + 69536),
    1610612756,
    aWatchBestTrial,
    20,
    1133903872,
    440.0,
    (int)v13,
    2,
    0.0);
  hide_border_init(*(_DWORD **)(this + 69536));
  *(_DWORD *)(*(_DWORD *)(this + 69536) + 620) = 1092616192;
  *(_DWORD *)(*(_DWORD *)(this + 69536) + 1776) = 1061997773;
  *(_DWORD *)(*(_DWORD *)(this + 69536) + 532) = 1082130432;
  *(_DWORD *)(*(_DWORD *)(this + 69536) + 532) = 1090519040;
  return open_galaxy_route(this, *(float *)(this + 69504));
}

