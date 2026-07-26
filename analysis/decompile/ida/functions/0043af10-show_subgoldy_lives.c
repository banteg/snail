/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: show_subgoldy_lives @ 0x43af10 */
/* selector: show_subgoldy_lives */

// Exact void Windows `cRSubGoldy::ShowLives()`: refreshes the nine-slot Goldy life display by showing the first `visible_life_stock` widgets and hiding the rest. Android preserves the same nine-widget loop and Player-owned life count; no iOS symbol was found.
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
