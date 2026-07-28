/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: hide_gameplay_scores @ 0x445f10 */
/* selector: hide_gameplay_scores */

// Exact void Windows `cRSubGame::HideScores()`: null-checks and hides the two gameplay score widgets owned by cRSubGame. Android and iOS preserve the same two-widget method and guard order.
void __thiscall hide_gameplay_scores(cRSubGame *game)
{
  FrontendWidget *bottom_score_widget; // ecx
  FrontendWidget *top_score_widget; // ecx

  bottom_score_widget = game->bottom_score_widget;
  if ( bottom_score_widget != nullptr )
    hide_border_init(bottom_score_widget);
  top_score_widget = game->top_score_widget;
  if ( top_score_widget != nullptr )
    hide_border_init(top_score_widget);
}
