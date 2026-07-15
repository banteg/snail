/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_thanks_for_playing_screen @ 0x433fd0 */
/* selector: initialize_thanks_for_playing_screen */

// Initializes the post-run Thanks For Playing owner, including the Splash backdrop, INTROTEXT.OGG, and the first shell-font message widget before state 30 begins updating it.
float *__thiscall initialize_thanks_for_playing_screen(int *this)
{
  int landscape_script_by_name; // eax
  tColour *v3; // eax
  float *result; // eax
  Color4f color; // [esp+4h] [ebp-10h] BYREF

  hide_star_field((StarManager *)&g_game_base->unknown_044100[45628]);
  cache_music_file(aMusicIntrotext, 0, (char *)g_blank_text);
  landscape_script_by_name = load_landscape_script_by_name(
                               (char *)&g_game_base->subgame.unknown_000044[16743356],
                               aSplashTxt);
  change_backdrop(
    (int)&g_game_base->unknown_044100[43792],
    (int)&g_game_base->subgame.unknown_000044[292 * landscape_script_by_name + 16744800],
    0);
  set_border_justify_centre(&g_game_base->border_manager, 0.0);
  *(this + 1) = (int)allocate_border(&g_game_base->border_manager);
  v3 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget((FrontendWidget *)*(this + 1), 0x20400002u, aThanksForPlayi, 20, 0.0, 435.0, v3, 2, 0.0);
  *(_DWORD *)(*(this + 1) + 1776) = 1067030938;
  *(this + 3) = 0;
  *(this + 4) = 998803593;
  *(this + 2) = 0;
  return result;
}
