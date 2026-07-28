/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_subgoldy_resurrect @ 0x441fd0 */
/* selector: update_subgoldy_resurrect */

// Void `Player` member that advances Goldy's resurrect or death-resolution state machine after `initialize_subgoldy_death`: starts the fade, decrements the visible life stock on the respawn branch, and only falls through to `complete_subgame` when the final-loss path wins. Its sole `update_subgoldy` caller loads the receiver into ECX and consumes no result. Cross-port Android and iOS symbols match this helper to `cRSubGoldy::RessurectAI()`.
void __thiscall update_subgoldy_resurrect(Player *player)
{
  double v2; // st7
  cRSubGame *game; // eax

  player->velocity.z = 0.0;
  if ( g_game_base->fade.state == 0 )
  {
    v2 = player->resurrect_progress_step + player->resurrect_progress;
    player->resurrect_progress = v2;
    if ( v2 > 1.0 && g_game_base->fade.state == 0 )
      begin_frontend_fade_out(&g_game_base->fade, nullptr);
  }
  if ( player->resurrect_progress > 1.0 && g_game_base->fade.state == 4 )
  {
    game = player->game;
    if ( player->resurrect_final_loss != 0 )
    {
      game->subgame_rebuild_selector = 2;
      complete_subgame(player->game, 1u);
      if ( player->game->selected_level_record_persistent != 0 )
      {
        g_game_base->players[0].saved_frontend_state = g_game_base->players[0].frontend_state;
        g_game_base->players[0].frontend_state = 26;
      }
      else
      {
        g_game_base->players[0].saved_frontend_state = g_game_base->players[0].frontend_state;
        if ( player->game->level_mode != 0 || g_game_base->players[0].high_score_entry_pending != 0 )
        {
          g_game_base->players[0].frontend_state = 27;
        }
        else
        {
          g_game_base->players[0].frontend_state = 26;
          g_game_base->players[0].saved_frontend_state = 2;
        }
      }
    }
    else
    {
      if ( game->level_mode == 0 )
        --player->visible_life_stock;
      g_game_base->players[0].saved_frontend_state = g_game_base->players[0].frontend_state;
      g_game_base->players[0].frontend_state = 28;
    }
  }
}
