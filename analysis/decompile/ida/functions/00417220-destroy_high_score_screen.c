/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_high_score_screen @ 0x417220 */
/* selector: destroy_high_score_screen */

// Exact void `cRHighScore::UnInit()`: tears down the active high-score widgets, preserves the selected bank index, and resets the shell-font scene. Android lifecycle branches and six Windows callers establish that the former zero result was incidental.
void __thiscall destroy_high_score_screen(cRHighScore *high_score)
{
  g_runtime_config.high_score_selected_bank = high_score->selected_bank;
  kill_all_borders(&g_game_base->border_manager);
  g_game_base->players[0].high_score_entry_pending = 0;
  g_game_base->players[0].selected_high_score_rank = 0;
}
