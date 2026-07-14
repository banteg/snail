/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: exit_high_score_screen @ 0x417b50 */
/* selector: exit_high_score_screen */

// Exact void `cRHighScore::Exit()`: leaves the high-score screen, restores front-end state `2` for postal or `10` for challenge, and seeds rebuild selector `2` on both paths. Both Windows callers discard the incidental root pointer left in EAX.
void __thiscall exit_high_score_screen(HighScore *high_score)
{
  _DWORD *v1; // eax

  v1 = g_game_base;
  if ( !*((_DWORD *)g_game_base + 119190) )
  {
    *((_DWORD *)g_game_base + 110) = 2;
    *((_DWORD *)g_game_base + 4953464) = 2;
    *((_BYTE *)g_game_base + 780) = 1;
    v1 = g_game_base;
  }
  if ( v1[119190] == 1 )
  {
    v1[110] = 10;
    *((_DWORD *)g_game_base + 4953464) = 2;
    *((_BYTE *)g_game_base + 780) = 1;
  }
}

