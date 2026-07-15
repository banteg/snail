/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_main_menu @ 0x419b30 */
/* selector: destroy_main_menu */

// Exact body shared by linker-folded `MainMenu::destroy_main_menu` and `Intro::destroy_new_game_menu`: both clear the global border and game-sprite scene. Windows callers pass the distinct embedded owners, while Android retains separate byte-identical `cRMainMenu::UnInit()` and `cRIntro::UnInit()` methods.
void __thiscall destroy_main_menu(MainMenu *menu)
{
  kill_all_borders(&g_game_base->border_manager);
  kill_game_sprites();
}
