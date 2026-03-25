/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_main_menu @ 0x419b30 */
/* selector: destroy_main_menu */

// Clears the active menu shell-font scene and tears down the current main-menu widget set before control leaves the front-end. Cross-port Android and iOS symbols match the owning flow to `cRMainMenu::UnInit()`.
void sub_419B30()
{
  kill_all_borders((int *)MEMORY[0x4DF904] + 723);
  kill_game_sprites();
}

