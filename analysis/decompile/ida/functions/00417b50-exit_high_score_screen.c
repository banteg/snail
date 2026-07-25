/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: exit_high_score_screen @ 0x417b50 */
/* selector: exit_high_score_screen */

// Exact void `cRHighScore::Exit()`: leaves the high-score screen, restores front-end state `2` for postal or `10` for challenge, and seeds rebuild selector `2` on both paths. Both Windows callers discard the incidental root pointer left in EAX.
void __thiscall exit_high_score_screen(HighScore *high_score)
{
  GameRoot *v1; // eax

  v1 = g_game_base;
  if ( !g_game_base->subgame.level_mode )
  {
    g_game_base->players[0].frontend_state = 2;
    g_game_base->subgame.subgame_rebuild_selector = 2;
    g_game_base->players[0].redispatch_requested = 1;
    v1 = g_game_base;
  }
  if ( v1->subgame.level_mode == 1 )
  {
    v1->players[0].frontend_state = 10;
    g_game_base->subgame.subgame_rebuild_selector = 2;
    g_game_base->players[0].redispatch_requested = 1;
  }
}
