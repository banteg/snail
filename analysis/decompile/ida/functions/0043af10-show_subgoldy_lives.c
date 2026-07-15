/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: show_subgoldy_lives @ 0x43af10 */
/* selector: show_subgoldy_lives */

// Void `Player` member that refreshes the nine-slot Goldy life display by showing the first `current_lives` widgets and hiding the rest. Windows `update_subgoldy` discards its incidental terminal widget-flag value and only calls it for gameplay mode 0, matching the mode-gated `cRSubGoldy::ShowLives()` helper in the Android and iOS ports.
void __thiscall show_subgoldy_lives(Player *player)
{
  int32_t v2; // edi
  int i; // esi

  v2 = 0;
  for ( i = 3521432; i < 3521468; i += 4 )
  {
    if ( v2 >= player->visible_life_stock )
      hide_border_init(*(FrontendWidget **)(&player->game->scan_reset + i));
    else
      unhide_border_init(*(FrontendWidget **)(&player->game->scan_reset + i));
    ++v2;
  }
}
