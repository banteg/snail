/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_new_game_menu @ 0x417bc0 */
/* selector: initialize_new_game_menu */

// Builds the New Game submenu, including Tutorial, Postal Mode, Time Trial, Challenge Mode, Help, and Back, after reloading the shared menu backdrop and shell-font scene. The menu-local replay-attract controller at `data_4df904 + 0x4f2dc` survives this init; direct button handlers later use frontend state `10`, with Postal Mode also seeding the ordinary rebuild selector `+0x12e55e0 = 2`.
char __thiscall sub_417BC0(int *this)
{
  int v2; // eax
  _DWORD *v3; // eax
  _DWORD *v4; // eax
  _DWORD *v5; // eax
  _DWORD *v6; // eax
  _DWORD *v7; // eax
  _DWORD *v8; // eax
  int v9; // eax
  _DWORD v11[4]; // [esp+4h] [ebp-10h] BYREF

  hide_star_field((int *)MEMORY[0x4DF904] + 81103);
  cache_music_file(aMusicMainmenuO);
  v2 = load_landscape_script_by_name((char *)MEMORY[0x4DF904] + 17220120, aMenubgTxt);
  change_backdrop((int)MEMORY[0x4DF904] + 322576, (int)MEMORY[0x4DF904] + 292 * v2 + 17221564, 0);
  set_border_justify_centre((_DWORD *)MEMORY[0x4DF904] + 723, 1103626240);
  *((_DWORD *)MEMORY[0x4DF904] + 347) = 2;
  *(this + 15) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v3 = set_color_rgba(v11, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(*(this + 15), 1073741844, aTutorial, 20, 1101004800, 80.0, (int)v3, 2, 0.0);
  *(this + 12) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v4 = set_color_rgba(v11, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(*(this + 12), 1073741844, aPostalMode, 20, 1101004800, 20.0, (int)v4, 2, 0.0);
  stack_widget_below(*(this + 12), *(this + 15));
  *(this + 13) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v5 = set_color_rgba(v11, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(*(this + 13), 1073741844, aTimeTrial, 20, 1101004800, 20.0, (int)v5, 2, 0.0);
  stack_widget_below(*(this + 13), *(this + 12));
  *(this + 14) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v6 = set_color_rgba(v11, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(*(this + 14), 20, aChallengeMode, 20, 1101004800, 20.0, (int)v6, 2, 0.0);
  stack_widget_below(*(this + 14), *(this + 13));
  *(this + 16) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v7 = set_color_rgba(v11, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(*(this + 16), 1073741844, aHelp, 20, 0, 350.0, (int)v7, 2, -220.0);
  *(this + 17) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v8 = set_color_rgba(v11, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(*(this + 17), 20, aBack, 20, 1101004800, 350.0, (int)v8, 2, 0.0);
  stack_widget_below(*(this + 17), *(this + 14));
  LOBYTE(v9) = unk_4DF9D8;
  if ( !unk_4DF9D8 )
  {
    *(_DWORD *)(*(this + 12) + 416) |= 0x8000u;
    v9 = *(this + 13);
    *(_DWORD *)(v9 + 416) |= 0x8000u;
    *(_DWORD *)(*(this + 14) + 416) |= 0x8000u;
  }
  return v9;
}

