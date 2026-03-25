/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_main_menu @ 0x419b50 */
/* selector: initialize_main_menu */

// Starts MAINMENU.OGG, loads Menubg.txt into the shared backdrop renderer, seeds the front-end state to menu mode, and allocates the New Game, High Scores, Options, Credits, and Exit widgets. Cross-port Android and iOS symbols match this helper to `cRMainMenu::Init()`.
float *__thiscall sub_419B50(int *this)
{
  int v2; // eax
  _DWORD *v3; // eax
  _DWORD *v4; // eax
  _DWORD *v5; // eax
  _DWORD *v6; // eax
  _DWORD *v7; // eax
  _DWORD *v8; // eax
  _DWORD v10[4]; // [esp+4h] [ebp-10h] BYREF

  hide_star_field((int *)MEMORY[0x4DF904] + 81103);
  cache_music_file(aMusicMainmenuO);
  v2 = load_landscape_script_by_name((char *)MEMORY[0x4DF904] + 17220120, aMenubgTxt);
  change_backdrop((int)MEMORY[0x4DF904] + 322576, (int)MEMORY[0x4DF904] + 292 * v2 + 17221564, 0);
  set_border_justify_centre((_DWORD *)MEMORY[0x4DF904] + 723, 1103626240);
  *((_DWORD *)MEMORY[0x4DF904] + 347) = 2;
  *this = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v3 = set_color_rgba(v10, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(*this, 20, aNewGame, 20, 1101004800, 90.0, (int)v3, 2, 0.0);
  *(this + 1) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v4 = set_color_rgba(v10, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(*(this + 1), 20, aHighScores, 20, 1101004800, 20.0, (int)v4, 2, 0.0);
  stack_widget_below(*(this + 1), *this);
  *(this + 2) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v5 = set_color_rgba(v10, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(*(this + 2), 20, aOptions, 20, 1101004800, 20.0, (int)v5, 2, 0.0);
  stack_widget_below(*(this + 2), *(this + 1));
  *(this + 2) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v6 = set_color_rgba(v10, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(*(this + 2), 20, aOptions, 20, 1101004800, 20.0, (int)v6, 2, 0.0);
  stack_widget_below(*(this + 2), *(this + 1));
  *(this + 3) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v7 = set_color_rgba(v10, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(*(this + 3), 1073741844, aCredits, 20, 1101004800, 20.0, (int)v7, 2, 0.0);
  stack_widget_below(*(this + 3), *(this + 2));
  *(this + 5) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v8 = set_color_rgba(v10, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(*(this + 5), 20, aExit, 20, 1101004800, 390.0, (int)v8, 2, 0.0);
  return stack_widget_below(*(this + 5), *(this + 3));
}

