/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_high_score_screen @ 0x417220 */
/* selector: destroy_high_score_screen */

// Exact void `cRHighScore::UnInit()`: tears down the active high-score widgets, preserves the selected bank index, and resets the shell-font scene. Android lifecycle branches and six Windows callers establish that the former zero result was incidental.
void __thiscall destroy_high_score_screen(HighScore *high_score)
{
  g_high_score_selected_bank = high_score->selected_bank;
  kill_all_borders((int *)g_game_base + 723);
  *((_BYTE *)g_game_base + 781) = 0;
  *((_DWORD *)g_game_base + 196) = 0;
}

