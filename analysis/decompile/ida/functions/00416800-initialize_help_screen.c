/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_help_screen @ 0x416800 */
/* selector: initialize_help_screen */

// Starts MAINMENU.OGG, loads Help.txt into the shared backdrop renderer, and allocates the single Back control. Cross-port Android and iOS symbols match this helper to `cRHelp::Init()`.
void __thiscall initialize_help_screen(FrontendWidget **this)
{
  int landscape_script_by_name; // eax
  tColour *v3; // eax
  Color4f color; // [esp+4h] [ebp-10h] BYREF

  cache_music_file(g_main_menu_music_path, 0, (char *)g_blank_text);
  landscape_script_by_name = load_landscape_script_by_name(
                               (char *)&g_game_base->subgame.unknown_000044[16743356],
                               g_help_script_path);
  change_backdrop(
    (int)&g_game_base->unknown_044100[43792],
    (int)&g_game_base->subgame.unknown_000044[292 * landscape_script_by_name + 16744800],
    0);
  set_border_justify_centre(&g_game_base->border_manager, 0.0);
  *this = allocate_border(&g_game_base->border_manager);
  v3 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(*this, 0x40000014u, g_back_text, 20, 0.0, 420.0, v3, 2, 0.0);
}
