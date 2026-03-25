/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_help_screen @ 0x416800 */
/* selector: initialize_help_screen */

// Starts MAINMENU.OGG, loads Help.txt into the shared backdrop renderer, and allocates the single Back control. Cross-port Android and iOS symbols match this helper to `cRHelp::Init()`.
float *__thiscall sub_416800(int *this)
{
  int v2; // eax
  _DWORD *v3; // eax
  _DWORD v5[4]; // [esp+4h] [ebp-10h] BYREF

  cache_music_file(aMusicMainmenuO);
  v2 = load_landscape_script_by_name((char *)MEMORY[0x4DF904] + 17220120, aHelpTxt);
  change_backdrop((int)MEMORY[0x4DF904] + 322576, (int)MEMORY[0x4DF904] + 292 * v2 + 17221564, 0);
  set_border_justify_centre((_DWORD *)MEMORY[0x4DF904] + 723, 0);
  *this = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v3 = set_color_rgba(v5, 1065353216, 1065353216, 1065353216, 1065353216);
  return initialize_frontend_widget(*this, 1073741844, aBack, 20, 0, 420.0, (int)v3, 2, 0.0);
}

