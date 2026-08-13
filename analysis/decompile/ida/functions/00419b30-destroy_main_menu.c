/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_main_menu @ 0x419b30 */
/* selector: destroy_main_menu */

// Exact body shared by linker-folded `cRMainMenu::UnInit()` and `cRIntro::UnInit()`: both clear the global border and game-sprite scene. Windows callers pass the distinct embedded owners, while Android retains separate byte-identical authored methods. The stable `destroy_new_game_menu` alias preserves the folded Intro call surface.
void __thiscall destroy_main_menu(cRMainMenu *menu)
{
  kill_all_borders(&g_game_base->border_manager);
  kill_game_sprites(&g_sprite_manager);
}
