/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: unhide_gameplay_scores @ 0x445f40 */
/* selector: unhide_gameplay_scores */

// Exact void Windows `cRSubGame::UnHideScores()`: unhides the two gameplay score widgets owned by SubgameRuntime. Android preserves the same two calls; no iOS symbol was found.
void __thiscall unhide_gameplay_scores(SubgameRuntime *game)
{
  unhide_border_init(game->bottom_score_widget);
  unhide_border_init(game->top_score_widget);
}
