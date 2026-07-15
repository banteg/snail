/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_subgoldy_resurrect @ 0x441fd0 */
/* selector: update_subgoldy_resurrect */

// Advances Goldy's resurrect or death-resolution state machine after `initialize_subgoldy_death`: starts the fade, decrements the visible life stock on the respawn branch, and only falls through to `complete_subgame` when the final-loss path wins. Cross-port Android and iOS symbols match this helper to `cRSubGoldy::RessurectAI()`.
void __thiscall update_subgoldy_resurrect(int this)
{
  double v2; // st7
  int v3; // eax

  *(_DWORD *)(this + 1048) = 0;
  if ( !g_game_base->fade.state )
  {
    v2 = *(float *)(this + 144) + *(float *)(this + 140);
    *(float *)(this + 140) = v2;
    if ( v2 > 1.0 && !g_game_base->fade.state )
      begin_frontend_fade_out(&g_game_base->fade.state, 0);
  }
  if ( *(float *)(this + 140) > 1.0 && g_game_base->fade.state == 4 )
  {
    v3 = *(_DWORD *)(this + 1032);
    if ( *(_DWORD *)(this + 128) )
    {
      *(_DWORD *)(v3 + 19337160) = 2;
      complete_subgame(*(SubgameRuntime **)(this + 1032), 1u);
      if ( *(_BYTE *)(*(_DWORD *)(this + 1032) + 16721361) )
      {
        g_game_base->players[0].saved_frontend_state = g_game_base->players[0].frontend_state;
        g_game_base->players[0].frontend_state = 26;
      }
      else
      {
        g_game_base->players[0].saved_frontend_state = g_game_base->players[0].frontend_state;
        if ( *(_DWORD *)(*(_DWORD *)(this + 1032) + 64) || g_game_base->players[0].high_score_entry_pending )
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
      if ( !*(_DWORD *)(v3 + 64) )
        --*(_DWORD *)(this + 17216);
      g_game_base->players[0].saved_frontend_state = g_game_base->players[0].frontend_state;
      g_game_base->players[0].frontend_state = 28;
    }
  }
}
