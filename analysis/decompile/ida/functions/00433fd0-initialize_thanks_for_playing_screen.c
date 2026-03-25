/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_thanks_for_playing_screen @ 0x433fd0 */
/* selector: initialize_thanks_for_playing_screen */

// Initializes the post-run Thanks For Playing owner, including the Splash backdrop, INTROTEXT.OGG, and the first shell-font message widget before state 30 begins updating it.
float *__thiscall sub_433FD0(int *this)
{
  int v2; // eax
  _DWORD *v3; // eax
  float *result; // eax
  _DWORD v5[4]; // [esp+4h] [ebp-10h] BYREF

  hide_star_field((int *)MEMORY[0x4DF904] + 81103);
  cache_music_file(aMusicIntrotext);
  v2 = load_landscape_script_by_name((char *)MEMORY[0x4DF904] + 17220120, aSplashTxt);
  change_backdrop((int)MEMORY[0x4DF904] + 322576, (int)MEMORY[0x4DF904] + 292 * v2 + 17221564, 0);
  set_border_justify_centre((_DWORD *)MEMORY[0x4DF904] + 723, 0);
  *(this + 1) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v3 = set_color_rgba(v5, 1065353216, 1065353216, 1065353216, 1065353216);
  result = initialize_frontend_widget(*(this + 1), 541065218, aThanksForPlayi, 20, 0, 435.0, (int)v3, 2, 0.0);
  *(_DWORD *)(*(this + 1) + 1776) = 1067030938;
  *(this + 3) = 0;
  *(this + 4) = 998803593;
  *(this + 2) = 0;
  return result;
}

